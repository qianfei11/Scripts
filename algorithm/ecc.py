#!/usr/bin/env python
#-*- encoding=utf-8 -*-
# === Author: assassinq
# === Date: 2019-9-30
import gmpy2
import random
import time
import libnum

def get_param(x0, a, b, p):
    y0 = -1
    i = 0
    while i < p:
        #print i, p
        if i ** 2 % p == (x0 ** 3 + a * x0 + b) % p:
            y0 = i
            break
        i += 1
    if y0 == -1:
        return False
    x1 = x0
    y1 = (-y0) % p
    return x0, y0, x1, y1

def get_x_y(E):
    a = E[0]
    b = E[1]
    p = E[2]
    x_y = []
    idx = 0
    i = 0
    while i < p:
        #print i, p
        val = get_param(i, a, b, p)
        if val != False:
            x0, y0, x1, y1 = val
            x_y.append((x0, y0))
            idx += 1
            x_y.append((x1, y1))
            idx += 1
        i += 1
    return x_y

def ecc_add(G1, G2, E):
    a = E[0]
    p = E[2]
    x1 = G1[0]
    y1 = G1[1]
    x2 = G2[0]
    y2 = G2[1]
    sign = True
    if x1 == x2 and y1 == y2:
        numerator = 3 * (x1 ** 2) + a
        denominator = 2 * y1
    else:
        numerator = y2 - y1
        denominator = x2 - x1
        if numerator * denominator < 0:
            sign = False
            numerator = abs(numerator)
            denominator = abs(denominator)
    divisor = gmpy2.gcd(numerator, denominator)
    numerator /= divisor
    denominator /= divisor
    inverse_d = gmpy2.invert(denominator, p)
    lmd = numerator * inverse_d
    if sign == False:
        lmd = -lmd
    lmd = lmd % p
    x3 = (lmd ** 2 - x1 - x2) % p
    y3 = (lmd * (x1 - x3) - y1) % p
    return (x3, y3)

def get_rank(G, E):
    p = E[2]
    x0 = G[0]
    y0 = G[1]
    x1 = x0
    y1 = (-y0) % p
    tx = x0
    ty = y0
    n = 1
    while True:
        n += 1
        (px, py) = ecc_add((tx, ty), (x0, y0), E)
        if px == x1 and py == y1:
            return n + 1
        tx = px
        ty = py

def ecc_mul(k, G, E, n):
    k = k % n
    x1 = G[0]
    y1 = G[1]
    rx = x1
    ry = y1
    i = 0
    while i < k - 1:
        rx, ry = ecc_add((rx, ry), (x1, y1), E)
        i += 1
    return (rx, ry)

def keygen():
    a = 13
    b = 22
    p = 23
    #a = 0
    #b = 7
    #p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
    if (4 * (a ** 3) + 27 * (b ** 2)) % p == 0:
        print '[!] This is not a oval!'
        exit()
    E = (a, b, p)
    x_y = get_x_y(E)
    for i in xrange(len(x_y)):
        print str(i) + ': ' + str(x_y[i])
    G = x_y[4]
    #G = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798, 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)
    n = get_rank(G, E)
    #n = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
    n_B = random.randrange(0, n)
    P_B = ecc_mul(n_B, G, E, n)
    pk = [E, n, G, P_B]
    sk = n_B
    return pk, sk

def encode(plaintext, pk):
    E = pk[0]
    n = pk[1]
    G = pk[2]
    P_B = pk[3]
    m = libnum.s2n(plaintext)
    k = random.randrange(1, n)
    P1 = ecc_mul(k, G, E, n)
    P2 = ecc_mul(k, P_B, E, n)
    x_y = get_x_y(E)
    Pt = x_y[random.randrange(0, len(x_y) - 1)]
    p = E[2]
    C = (m * Pt[0] + Pt[1]) % p
    ciphertext = [P1, ecc_add(Pt, P2, E), C]
    return ciphertext

def decode(ciphertext, pk, sk):
    E = pk[0]
    n = pk[1]
    G = pk[2]
    P_B = pk[3]
    n_B = sk
    P1 = ciphertext[0]
    Pt_kP_B = ciphertext[1]
    C = ciphertext[2]
    n_B_kG = ecc_mul(n_B, P1, E, n)
    p = E[2]
    n_B_kG_ = (n_B_kG[0], (-n_B_kG[1]) % p)
    Pt = ecc_add(Pt_kP_B, n_B_kG_, E)
    xt = Pt[0]
    yt = Pt[1]
    xt_ = gmpy2.invert(xt, p)
    c_yt = gmpy2.sub(C, yt) % p
    m = gmpy2.mul(c_yt, xt_) % p
    plaintext = libnum.n2s(m)
    return plaintext

if __name__ == '__main__':
    pk, sk = keygen()
    print 'pk =', pk
    print 'sk =', sk
    m = chr(15)
    #m = raw_input('Please input your message: ')
    print 'm =', libnum.s2n(m)
    c = encode(m, pk)
    print 'ciphertext:', c
    res = decode(c, pk, sk)
    print 'plaintext:', ord(res)
