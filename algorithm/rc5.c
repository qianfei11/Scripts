/* rc5.c -- Reference implementation of RC5-32/12/16 in C.                */
/* Copyright (C) 1995 RSA Data Security, Inc.                             */
#include <stdio.h>
#include <string.h>
typedef unsigned int WORD;           /* Should be 32-bit = 4 bytes        */
#define w 32                         /* word size in bits                 */
#define r 12                         /* number of rounds                  */
#define b 16                         /* number of bytes in key            */
#define c 4                          /* number words in key               */
#define t 26                         /* size of table S = 2*(r+1) words   */
WORD S[t];                           /* expanded key table                */
WORD P = 0xb7e15163, Q = 0x9e3779b9; /* magic constants                   */
/* Rotation operators. x must be unsigned, to get logical right shift     */
#define ROTL(x, y) (((x) << (y & (w - 1))) | ((x) >> (w - (y & (w - 1)))))
#define ROTR(x, y) (((x) >> (y & (w - 1))) | ((x) << (w - (y & (w - 1)))))

void rc5_keygen(unsigned char *K) /* secret input ket K[0...b-1] */
{
    WORD i, j, k, u = w / 8, A, B, L[c];
    /* Initialize L, then S, then mix key into S */
    for (i = b - 1, L[c - 1] = 0; i != -1; i--)
    {
        L[i / u] = (L[i / u] << 8) + K[i];
    }
    for (S[0] = P, i = 1; i < t; i++)
    {
        S[i] = S[i - 1] + Q;
    }
    for (A = B = i = j = k = 0; k < 3 * t; k++, i = (i + 1) % t, j = (j + 1) % c) /* 3*t > 3*c */
    {
        A = S[i] = ROTL(S[i] + (A + B), 3);
        B = L[j] = ROTL(L[j] + (A + B), (A + B));
    }
}

void rc5_encrypt(unsigned char *plain, unsigned char *cipher) /* 2 WORD input pt/output ct */
{
    WORD pt[2], ct[2];
    for (int i = 0; i < 2; i++)
    {
        pt[i] = plain[4 * i] + (plain[4 * i + 1] << 8) + (plain[4 * i + 2] << 16) + (plain[4 * i + 3] << 24);
    }

    WORD A = pt[0] + S[0], B = pt[1] + S[1];
    for (int i = 1; i <= r; i++)
    {
        A = ROTL(A ^ B, B) + S[2 * i];
        B = ROTL(B ^ A, A) + S[2 * i + 1];
    }
    ct[0] = A;
    ct[1] = B;
    for (int i = 0; i < 2; i++)
    {
        cipher[4 * i] = ct[i] & 0xFF;
        cipher[4 * i + 1] = (ct[i] >> 8) & 0xFF;
        cipher[4 * i + 2] = (ct[i] >> 16) & 0xFF;
        cipher[4 * i + 3] = (ct[i] >> 24) & 0xFF;
    }
}

void rc5_decrypt(unsigned char *cipher, unsigned char *plain) /* 2 WORD input ct/output pt */
{
    WORD pt[2], ct[2];
    for (int i = 0; i < 2; i++)
    {
        ct[i] = cipher[4 * i] + (cipher[4 * i + 1] << 8) + (cipher[4 * i + 2] << 16) + (cipher[4 * i + 3] << 24);
    }
    WORD B = ct[1], A = ct[0];
    for (int i = r; i > 0; i--)
    {
        B = ROTR(B - S[2 * i + 1], A) ^ A;
        A = ROTR(A - S[2 * i], B) ^ B;
    }
    pt[1] = B - S[1];
    pt[0] = A - S[0];
    for (int i = 0; i < 2; i++)
    {
        plain[4 * i] = pt[i] & 0xFF;
        plain[4 * i + 1] = (pt[i] >> 8) & 0xFF;
        plain[4 * i + 2] = (pt[i] >> 16) & 0xFF;
        plain[4 * i + 3] = (pt[i] >> 24) & 0xFF;
    }
}

int main()
{
    unsigned char key[b] = "helloworlditsrc5";
    rc5_keygen(key);
    unsigned char *plain1 = "12345678";
    int length = strlen(plain);
    unsigned char cipher[length + 1];
    rc5_encrypt(plain1, cipher);
    printf("cipher: %s\n", cipher);
    unsigned char plain2[length + 1];
    rc5_decrypt(cipher, plain2);
    printf("plain: %s\n", plain2);
    return 0;
}
