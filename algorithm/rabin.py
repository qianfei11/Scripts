#!/usr/bin/env python
import gmpy2
import time
import libnum

DEBUG = True

def get_prime(rs):
    p = gmpy2.mpz_urandomb(rs, 1024)
    while not gmpy2.is_prime(p):
        p = p + 1
    return p

def keygen():
    rs = gmpy2.random_state(int(time.time()))
    while True:
        p = get_prime(rs)
        if p % 4 == 3:
            break
    while True:
        q = get_prime(rs)
        if q % 4 == 3:
            break
    n = p * q
    pk = n
    sk = [p, q]
    return pk, sk

def encipher(plaintext, pk):
    m = libnum.s2n(plaintext)
    n = pk
    ciphertext = gmpy2.powmod(m, 2, n)
    return ciphertext

def decipher(ciphertext, pk, sk):
    n = pk
    [p, q] = sk
    m_p = gmpy2.powmod(ciphertext, (p + 1) / 4, p)
    m_q = gmpy2.powmod(ciphertext, (q + 1) / 4, q)
    if DEBUG:
        print '[DEBUG]', gmpy2.powmod(m_p, 2, p)
        print '[DEBUG]', gmpy2.powmod(m_q, 2, q)
        print '[DEBUG]', ciphertext
    assert gmpy2.powmod(m_p, 2, p) == ciphertext
    assert gmpy2.powmod(m_q, 2, q) == ciphertext
    y_p = gmpy2.invert(p, q)
    y_q = gmpy2.invert(q, p)
    r1 = (y_p * p * m_q + y_q * q * m_p) % n
    r2 = n - r1
    r3 = (y_p * p * m_q - y_q * q * m_p) % n
    r4 = n - r3
    plaintext = [r1, r2, r3, r4]
    plaintext = map(lambda m: libnum.n2s(m), plaintext)
    return plaintext

if __name__ == '__main__':
    plaintext = raw_input('Please input your message: ')
    pk, sk = keygen()
    if DEBUG:
        print '[DEBUG] pk:', pk
        print '[DEBUG] sk:', sk
    ciphertext = encipher(plaintext, pk)
    print 'ciphertext:', ciphertext
    plaintext = decipher(ciphertext, pk, sk)
    print 'plaintext:', plaintext

