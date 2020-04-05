#!/usr/bin/env python
#-*- encoding=utf-8 -*-
# === Author: assassinq
# === Date: 2019-09-25
import random
import gmpy2
import time
import libnum

# 生成大素数
def get_prime(rs):
    p = gmpy2.mpz_urandomb(rs, 1024)
    while not gmpy2.is_prime(p):
        p = p + 1
    return p

# 产生密钥
def keygen():
    rs = gmpy2.random_state(int(time.time()))
    p = get_prime(rs)
    g = random.randrange(0, p)
    x = random.randrange(2, p - 1)
    y = gmpy2.powmod(g, x, p)
    pk = [y, g, p]
    sk = x
    return pk, sk

# 加密函数
def encode(plain, pk):
    y = pk[0]
    g = pk[1]
    p = pk[2]
    r = random.randrange(2, p - 1)
    c = gmpy2.powmod(g, r, p)
    y_r = gmpy2.powmod(y, r, p)
    m = libnum.s2n(plain)
    cdot = gmpy2.mul(y_r, m) % p
    cipher = [c, cdot]
    return cipher

# 解密函数
def decode(cipher, pk, sk):
    y = pk[0]
    g = pk[1]
    p = pk[2]
    x = sk
    c = cipher[0]
    cdot = cipher[1]
    c_x = gmpy2.powmod(c, x, p)
    c_x_ = gmpy2.invert(c_x, p)
    m = gmpy2.mul(cdot, c_x_) % p
    plaintext = libnum.n2s(m)
    return plaintext

if __name__ == '__main__':
    pk, sk = keygen()
    m = raw_input('Please input your message: ')
    ciphertext = encode(m, pk)
    print 'This is ciphertext:', ciphertext
    plaintext = decode(ciphertext, pk, sk)
    print 'This is plaintext:', plaintext
