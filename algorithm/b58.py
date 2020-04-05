#!/usr/bin/env python
import libnum

b58table = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
table_len = len(b58table)

def div_mod(n, l):
    return n / l, n % l

def encipher(plaintext):
    long_val = libnum.s2n(plaintext)
    ciphertext = ''
    while long_val >= len(b58table):
        div, mod = div_mod(long_val, table_len)
        ciphertext = b58table[mod] + ciphertext
        long_val = div
    ciphertext = b58table[long_val] + ciphertext
    pad = 0
    for c in plaintext:
        if c == '\x00':
            pad += 1
        else:
            break
    ciphertext = b58table[0] * pad + ciphertext
    return ciphertext

def decipher(ciphertext):
    long_val = 0
    for c in ciphertext:
        long_val *= table_len
        long_val += b58table.find(c)
    plaintext = libnum.n2s(long_val)
    pad = 0
    for c in ciphertext:
        if c == b58table[0]:
            pad += 1
        else:
            break
    plaintext = '\x00' * pad + plaintext
    return plaintext

if __name__ == '__main__':
    print encipher('This is base58...')
    print decipher('o1JLFGZZCsrNwaxhxKT3vu3')

