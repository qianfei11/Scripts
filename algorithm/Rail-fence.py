#!/usr/bin/env python
import sys

__author__ = 'assassinq'

def welcome():
    print ' ,ggggggggggg,                                                                                        '
    print 'dP"""88""""""Y8,                    ,dPYb,           ,dPYb,                                           '
    print 'Yb,  88      `8b                    IP\'`Yb           IP\'`Yb                                           '
    print ' `"  88      ,8P               gg   I8  8I           I8  8I                                           '
    print '     88aaaad8P"                ""   I8  8\'           I8  8\'                                           '
    print '     88""""Yb,      ,gggg,gg   gg   I8 dP  aaaaaaaa  I8 dP    ,ggg,    ,ggg,,ggg,     ,gggg,   ,ggg,  '
    print '     88     "8b    dP"  "Y8I   88   I8dP   """"""""  I8dP    i8" "8i  ,8" "8P" "8,   dP"  "Yb i8" "8i '
    print '     88      `8i  i8\'    ,8I   88   I8P              I8P     I8, ,8I  I8   8I   8I  i8\'       I8, ,8I '
    print '     88       Yb,,d8,   ,d8b,_,88,_,d8b,_           ,d8b,_   `YbadP\' ,dP   8I   Yb,,d8,_    _ `YbadP\' '
    print '     88        Y8P"Y8888P"`Y88P""Y88P\'"Y88          PI8"8888888P"Y8888P\'   8I   `Y8P""Y8888PP888P"Y888'
    print '                                                     I8 `8,                                           '
    print '                                                     I8  `8,                                          '
    print '                                                     I8   8I                                          '
    print '                                                     I8   8I                                          '
    print '                                                     I8, ,8\'                                          '
    print '                                                      "Y8P\'                                           '

def encipher(plaintext, key):
    remain = len(plaintext) % key
    if remain != 0:
        pad = (key - remain) * '@'
        plaintext += pad
    assert len(plaintext) % key == 0
    key_ = len(plaintext) / key
    ciphertext = ''
    for i in range(key):
        for j in range(key_):
            ciphertext += plaintext[key * j + i]
    ciphertext = ciphertext.replace('@', '')
    return ciphertext

def decipher(ciphertext, key):
    remain = len(ciphertext) % key
    if remain != 0:
        pad = (key - remain) * '@'
        ciphertext += pad
    assert len(ciphertext) % key == 0
    key_ = len(ciphertext) / key
    plaintext = ''
    for i in range(key_):
        for j in range(key):
            plaintext += ciphertext[i + key_ * j]
    plaintext = plaintext.replace('@', '')
    return plaintext

if __name__ == '__main__':
    welcome()
    if len(sys.argv) != 5:
        print 'Usage:', sys.argv[0], '[encode] [key] [round] [plaintext]'
        print '      ', sys.argv[0], '[decode] [key] [round] [ciphertext]'
        exit()
    if sys.argv[1] == 'encode':
        try:
            key = int(sys.argv[2])
        except Exception:
            print '[!] key is not a number...'
            exit()
        try:
            r = int(sys.argv[3])
        except Exception:
            print '[!] round is not a number...'
            exit()
        plaintext = sys.argv[4].replace(' ', '')
        for i in range(r):
            ciphertext = encipher(plaintext, key)
            plaintext = ciphertext
        print '[*] ciphertext =', ciphertext
    elif sys.argv[1] == 'decode':
        try:
            key = int(sys.argv[2])
        except Exception:
            print '[!] key is not a number...'
            exit()
        try:
            r = int(sys.argv[3])
        except Exception:
            print '[!] round is not a number...'
            exit()
        ciphertext = sys.argv[4].replace(' ', '')
        for i in range(r):
            plaintext = decipher(ciphertext, key)
            ciphertext = plaintext
        print '[*] plaintext =', plaintext
    else:
        print '[!] Option Error...'

