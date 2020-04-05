/* rc6 (TM)
 * Unoptimized sample implementation of Ron Rivest's submission to the
 * AES bakeoff.
 *
 * Salvo Salasio, 19 June 1998
 *
 * Intellectual property notes:  The name of the algorithm (RC6) is
 * trademarked; any property rights to the algorithm or the trademark
 * should be discussed with discussed with the authors of the defining
 * paper "The RC6(TM) Block Cipher": Ronald L. Rivest (MIT),
 * M.J.B. Robshaw (RSA Labs), R. Sidney (RSA Labs), and Y.L. Yin (RSA Labs),
 * distributed 18 June 1998 and available from the lead author's web site.
 *
 * This sample implementation is placed in the public domain by the author,
 * Salvo Salasio.  The ROTL and ROTR definitions were cribbed from RSA Labs'
 * RC5 reference implementation.
 */

#include <stdio.h>
#include <string.h>

/* RC6 is parameterized for w-bit words, b bytes of key, and
 * r rounds.  The AES version of RC6 specifies b=16, 24, or 32;
 * w=32; and r=20.
 */

/* derived constants */
typedef unsigned int WORD;           /* Should be 32-bit = 4 bytes        */
#define w 32                         /* word size in bits                 */
#define r 20                         /* based on security estimates       */
#define bytes (w / 8)                /* bytes per word                    */
#define c ((b + bytes - 1) / bytes)  /* key in words, rounded up          */
#define R24 (2 * r + 4)              /* length of array S                 */
#define lgw 5                        /* log2(w) -- wussed out             */
WORD S[R24 - 1];                     /* Key schedule                      */
WORD P = 0xb7e15163, Q = 0x9e3779b9; /* magic constants                   */
/* Rotation operators. x must be unsigned, to get logical right shift     */
#define ROTL(x, y) (((x) << (y & (w - 1))) | ((x) >> (w - (y & (w - 1)))))
#define ROTR(x, y) (((x) >> (y & (w - 1))) | ((x) << (w - (y & (w - 1)))))

void rc6_keygen(unsigned char *K, int b) // b = strlen(key)
{
    int i, j, s, v;
    WORD L[(32 + bytes - 1) / bytes]; /* Big enough for max b */
    WORD A, B;

    L[c - 1] = 0;
    for (i = b - 1; i >= 0; i--)
        L[i / bytes] = (L[i / bytes] << 8) + K[i];

    S[0] = P;
    for (i = 1; i <= 2 * r + 3; i++)
        S[i] = S[i - 1] + Q;

    A = B = i = j = 0;
    v = R24;
    if (c > v)
        v = c;
    v *= 3;

    for (s = 1; s <= v; s++)
    {
        A = S[i] = ROTL(S[i] + A + B, 3);
        B = L[j] = ROTL(L[j] + A + B, A + B);
        i = (i + 1) % R24;
        j = (j + 1) % c;
    }
}

void rc6_encrypt(unsigned char *plain, unsigned char *cipher)
{
    WORD pt[4], ct[4];
    for (int i = 0; i < 4; i++)
    {
        pt[i] = plain[4 * i] + (plain[4 * i + 1] << 8) + (plain[4 * i + 2] << 16) + (plain[4 * i + 3] << 24);
    }

    WORD A, B, C, D, t, u, x;

    A = pt[0];
    B = pt[1];
    C = pt[2];
    D = pt[3];
    B += S[0];
    D += S[1];
    for (int i = 2; i <= 2 * r; i += 2)
    {
        t = ROTL(B * (2 * B + 1), lgw);
        u = ROTL(D * (2 * D + 1), lgw);
        A = ROTL(A ^ t, u) + S[i];
        C = ROTL(C ^ u, t) + S[i + 1];
        x = A;
        A = B;
        B = C;
        C = D;
        D = x;
    }
    A += S[2 * r + 2];
    C += S[2 * r + 3];
    ct[0] = A;
    ct[1] = B;
    ct[2] = C;
    ct[3] = D;

    for (int i = 0; i < 4; i++)
    {
        cipher[4 * i] = ct[i] & 0xFF;
        cipher[4 * i + 1] = (ct[i] >> 8) & 0xFF;
        cipher[4 * i + 2] = (ct[i] >> 16) & 0xFF;
        cipher[4 * i + 3] = (ct[i] >> 24) & 0xFF;
    }
}

void rc6_decrypt(unsigned char *cipher, unsigned char *plain)
{
    WORD pt[4], ct[4];
    for (int i = 0; i < 4; i++)
    {
        ct[i] = cipher[4 * i] + (cipher[4 * i + 1] << 8) + (cipher[4 * i + 2] << 16) + (cipher[4 * i + 3] << 24);
    }

    WORD A, B, C, D, t, u, x;

    A = ct[0];
    B = ct[1];
    C = ct[2];
    D = ct[3];
    C -= S[2 * r + 3];
    A -= S[2 * r + 2];
    for (int i = 2 * r; i >= 2; i -= 2)
    {
        x = D;
        D = C;
        C = B;
        B = A;
        A = x;
        u = ROTL(D * (2 * D + 1), lgw);
        t = ROTL(B * (2 * B + 1), lgw);
        C = ROTR(C - S[i + 1], t) ^ u;
        A = ROTR(A - S[i], u) ^ t;
    }
    D -= S[1];
    B -= S[0];
    pt[0] = A;
    pt[1] = B;
    pt[2] = C;
    pt[3] = D;

    for (int i = 0; i < 4; i++)
    {
        plain[4 * i] = pt[i] & 0xFF;
        plain[4 * i + 1] = (pt[i] >> 8) & 0xFF;
        plain[4 * i + 2] = (pt[i] >> 16) & 0xFF;
        plain[4 * i + 3] = (pt[i] >> 24) & 0xFF;
    }
}

int main()
{
    unsigned char *key = "assassinq_keeps_humble_";
    rc6_keygen(key, strlen(key));
    unsigned char *plain1 = "1234567887654321";
    int length = strlen(plain);
    unsigned char cipher[length + 1];
    rc6_encrypt(plain1, cipher);
    printf("cipher: %s\n", cipher);
    unsigned char plain2[length + 1];
    rc6_decrypt(cipher, plain2);
    printf("plain: %s\n", plain2);
    return 0;
}
