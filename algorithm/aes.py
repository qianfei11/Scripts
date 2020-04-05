#!/usr/bin/env python
# -*- encoding=utf-8 -*-

ENCRYPT = 0
DECRYPT = 1
BLOCK_SIZE = 16

S = [0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
     0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16]
S_ = [0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
      0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d]

Rcon = [
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A,
    0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A,
    0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39,
]

rounds = 10 # AES-128
# rounds = 12 # AES-192
# rounds = 14 # AES-256
round_keys = [[0] * 4] * 4 * (rounds + 1)

def xtime(a):
    return (((a << 1) ^ 0x1B) & 0xFF) if (a & 0x80) else (a << 1)

def convert_string_to_matrix(string):
    assert len(string) % 4 == 0, "string length error."
    matrix = []
    l = len(string)
    for i in range(l):
        byte = ord(string[i])
        if i % 4 == 0:
            matrix.append([byte])
        else:
            matrix[i / 4].append(byte)
    return matrix

def convert_matrix_to_string(matrix):
    string = ''
    l = len(matrix)
    for i in range(l):
        for j in range(4):
            string += chr(matrix[i][j])
    return string

def generate_round_keys(master_key):
    round_keys[:4] = convert_string_to_matrix(master_key)
    # print round_keys
    for i in range(4, 4 * rounds + 4):
        temp = []
        if i % 4 == 0:
            # print round_keys[i - 4][0]
            # print round_keys[i - 1][0]
            # print Rcon[i/4]
            byte = round_keys[i - 4][0] ^ S[round_keys[i - 1][1]] ^ Rcon[i / 4]
            # print i, byte
            temp.append(byte)
            for j in range(1, 4):
                byte = round_keys[i - 4][j] ^ S[round_keys[i - 1][(j + 1) % 4]]
                # print byte
                temp.append(byte)
        else:
            for j in range(4):
                byte = round_keys[i - 4][j] ^ round_keys[i - 1][j]
                temp.append(byte)
        round_keys[i] = temp
    # print round_keys

def add_round_key(matrix, round_key):
    for i in range(4):
        for j in range(4):
            matrix[i][j] ^= round_key[i][j]
    return matrix

def sub_bytes(matrix, table):
    for i in range(4):
        for j in range(4):
            matrix[i][j] = table[matrix[i][j]]
    return matrix

def shift_single_row(matrix, line, n):
    i = 0
    while i < n:
        temp = matrix[0][line]
        for j in range(3):
            matrix[j][line] = matrix[j + 1][line]
        matrix[3][line] = temp
        i += 1
    return matrix

def shift_rows(matrix, inversed=False):
    if inversed == True:
        matrix = shift_single_row(matrix, 1, 3)
        matrix = shift_single_row(matrix, 2, 2)
        matrix = shift_single_row(matrix, 3, 1)
    else:
        matrix = shift_single_row(matrix, 1, 1)
        matrix = shift_single_row(matrix, 2, 2)
        matrix = shift_single_row(matrix, 3, 3)
    return matrix

def mix_single_column(matrix):
    t = 0
    for i in range(4):
        t ^= matrix[i]
    # print 'x =>', t
    temp = matrix[0]
    for i in range(3):
        matrix[i] ^= t ^ xtime(matrix[i] ^ matrix[i + 1])
    matrix[3] ^= t ^ xtime(matrix[3] ^ temp)
    return matrix

def mix_columns(matrix, inversed=False):
    if inversed == True:
        for i in range(4):
            u = xtime(xtime(matrix[i][0] ^ matrix[i][2]))
            v = xtime(xtime(matrix[i][1] ^ matrix[i][3]))
            matrix[i][0] ^= u
            matrix[i][1] ^= v
            matrix[i][2] ^= u
            matrix[i][3] ^= v
        matrix = mix_columns(matrix)
    else:
        for i in range(4):
            # print 'm =>', matrix[i]
            matrix[i] = mix_single_column(matrix[i])
    return matrix

def aes_cipher(block, choice):
    assert len(block) == 16, "Block\'s length must be 16."
    matrix = convert_string_to_matrix(block)
    if choice == ENCRYPT:
        matrix = add_round_key(matrix, round_keys[:4])
        i = 1
        while i < rounds:
            matrix = sub_bytes(matrix, S)
            matrix = shift_rows(matrix)
            matrix = mix_columns(matrix)
            matrix = add_round_key(matrix, round_keys[4 * i:4 * i + 4])
            i += 1
        matrix = sub_bytes(matrix, S)
        matrix = shift_rows(matrix)
        matrix = add_round_key(matrix, round_keys[40:])
    elif choice == DECRYPT:
        matrix = add_round_key(matrix, round_keys[40:])
        matrix = shift_rows(matrix, inversed=True)
        matrix = sub_bytes(matrix, S_)
        i = rounds - 1
        while i > 0:
            matrix = add_round_key(matrix, round_keys[4 * i:4 * i + 4])
            matrix = mix_columns(matrix, inversed=True)
            matrix = shift_rows(matrix, inversed=True)
            matrix = sub_bytes(matrix, S_)
            i -= 1
        matrix = add_round_key(matrix, round_keys[:4])
    return convert_matrix_to_string(matrix)

def cipher(data, key, iv, choice):
    assert len(data) % BLOCK_SIZE == 0, "Data length illegal."
    assert len(iv) == BLOCK_SIZE, "iv\'s length should be 16."
    assert len(key) == 16, "key\'s length should be 16."
    generate_round_keys(key)
    i = 0
    result = []
    while i < len(data):
        block = data[i:i + 16]
        if choice == ENCRYPT:
            block = list(map(lambda x, y: ord(x) ^ ord(y), block, iv))
            block = ''.join([chr(c) for c in block])
            block = aes_cipher(block, choice)
            iv = block
        elif choice == DECRYPT:
            temp = block[:]
            block = aes_cipher(block, choice)
            block = list(map(lambda x, y: ord(x) ^ ord(y), block, iv))
            block = ''.join([chr(c) for c in block])
            iv = temp
        result.append(block)
        i += BLOCK_SIZE
    return ''.join(result)

def encipher(data, key, iv):
    return cipher(data, key, iv, ENCRYPT).encode('base64')

def decipher(data, key, iv):
    return cipher(data.decode('base64'), key, iv, DECRYPT)

if __name__ == '__main__':
    key = '#qianfei12345678'
    iv = '0' * 16
    ciphertext = encipher('#qianfei12345678', key, iv)
    print ciphertext
    plaintext = decipher(ciphertext, key, iv)
    print plaintext
