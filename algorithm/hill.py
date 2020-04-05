#!/usr/bin/env python
import sys
import numpy
import string
import sympy

letters = [c for c in string.ascii_uppercase]

def convert2Number(m):
    res = []
    for i in range(len(m)):
        idx = letters.index(m[i])
        res.append(idx)
    return res

def convert2String(matrix):
    res = ''
    for i in matrix:
        res += letters[i]
    return res

def isMatrix(m):
    n = sympy.sqrt(len(m))
    if n ** 2 != len(m):
        print '[!] Not a matrix...'
        exit()
    res = numpy.mat(m).reshape(n, n)
    return res

def getInverse(matrix):
    matrix_ = sympy.Matrix(matrix).inv_mod(26)
    return numpy.mat(matrix_)

def encipher(plaintext, key):
    plaintext = convert2Number(plaintext)
    n = len(key)
    l = len(plaintext)
    plaintext = numpy.mat(plaintext).reshape(n, l / n)
    print key
    print plaintext
    ciphertext = key * plaintext % 26
    print ciphertext
    ciphertext = ciphertext.reshape(1, l).tolist()[0]
    ciphertext = convert2String(ciphertext)
    return ciphertext

def decipher(ciphertext, key):
    key_ = getInverse(key)
    ciphertext = convert2Number(ciphertext)
    n = len(key)
    l = len(ciphertext)
    ciphertext = numpy.mat(ciphertext).reshape(n, l / n)
    print key_
    print ciphertext
    plaintext = key_ * ciphertext % 26
    print plaintext
    plaintext = plaintext.reshape(1, l).tolist()[0]
    plaintext = convert2String(plaintext)
    return plaintext

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print 'Usage:', sys.argv[0], '[encode] [plaintext]'
        print '      ', sys.argv[0], '[decode] [ciphertext]'
        exit()
    print '                               1 2 3'
    print 'Example: 1 2 3 4 5 6 7 8 9 ==> 4 5 6'
    print '                               7 8 9'
    keyStr = raw_input('Input the key: ')
    try:
        key = [int(n) % 26 for n in keyStr.split(' ')]
    except Exception:
        print '[!] Key input error...'
        exit()
    key = isMatrix(key)
    print 'key:'
    print key
    if sys.argv[1] == 'encode':
        plaintext = sys.argv[2].upper()
        try:
            ciphertext = encipher(plaintext, key)
            print 'ciphertext =', ciphertext
        except Exception as e:
            print '[!] Encipher Error...'
            print e
            exit()
    elif sys.argv[1] == 'decode':
        ciphertext = sys.argv[2].upper()
        try:
            plaintext = decipher(ciphertext, key)
            print 'plaintext =', plaintext
        except Exception as e:
            print '[!] Encipher Error...'
            print e
            exit()
    else:
        print '[!] Option Error...'

