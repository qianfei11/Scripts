#!/usr/bin/env python
#-*- encoding=utf-8 -*-
# === Author: assassinq
# === Date: 2019-09-21
import hashlib
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
    q = get_prime(rs)
    n = p * q
    e = 0x10001
    pk = [n, e]
    d = gmpy2.invert(e, (p - 1) * (q - 1))
    sk = d
    return pk, sk

# 加密函数
def encrypt(m, pk):
    n = pk[0]
    e = pk[1]
    m = libnum.s2n(m)
    return gmpy2.powmod(m, e, n)

# 解密函数
def decrypt(c, pk, sk):
    n = pk[0]
    d = sk
    m = gmpy2.powmod(c, d, n)
    return libnum.n2s(m)

if __name__ == '__main__':
    pk, sk = keygen()
    m = raw_input('Please input your message:')
    c = encrypt(m, pk)
    print 'This is ciphertext:', c
    res = decrypt(c, pk, sk)
    print 'This is plaintext:', res
