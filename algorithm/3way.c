#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRT_E 0x0b0b /* round consblocknt of first encryption round */
#define STRT_D 0xb1b1 /* round consblocknt of first decryption round */
#define NMBR 11       /* number of rounds is 11                   */

uint32_t Km[3];

void mu(uint32_t *a)
{ /* inverts the order of the bits of a */
    int i;
    uint32_t b[3];

    b[0] = b[1] = b[2] = 0;
    for (i = 0; i < 32; i++)
    {
        b[0] <<= 1;
        b[1] <<= 1;
        b[2] <<= 1;
        if (a[0] & 1)
            b[2] |= 1;
        if (a[1] & 1)
            b[1] |= 1;
        if (a[2] & 1)
            b[0] |= 1;
        a[0] >>= 1;
        a[1] >>= 1;
        a[2] >>= 1;
    }

    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
}

void gamma(uint32_t *a)
{ /* the nonlinear step */
    uint32_t b[3];

    b[0] = a[0] ^ (a[1] | (~a[2]));
    b[1] = a[1] ^ (a[2] | (~a[0]));
    b[2] = a[2] ^ (a[0] | (~a[1]));

    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
}

void theta(uint32_t *a)
{ /* the linear step */
    uint32_t b[3];

    b[0] =
        a[0] ^ (a[0] >> 16) ^ (a[1] << 16) ^ (a[1] >> 16) ^ (a[2] << 16) ^
        (a[1] >> 24) ^ (a[2] << 8) ^ (a[2] >> 8) ^ (a[0] << 24) ^ (a[2] >> 16) ^ (a[0] << 16) ^ (a[2] >> 24) ^ (a[0] << 8);
    b[1] =
        a[1] ^ (a[1] >> 16) ^ (a[2] << 16) ^ (a[2] >> 16) ^ (a[0] << 16) ^
        (a[2] >> 24) ^ (a[0] << 8) ^ (a[0] >> 8) ^ (a[1] << 24) ^ (a[0] >> 16) ^ (a[1] << 16) ^ (a[0] >> 24) ^ (a[1] << 8);
    b[2] =
        a[2] ^ (a[2] >> 16) ^ (a[0] << 16) ^ (a[0] >> 16) ^ (a[1] << 16) ^
        (a[0] >> 24) ^ (a[1] << 8) ^ (a[1] >> 8) ^ (a[2] << 24) ^ (a[1] >> 16) ^ (a[2] << 16) ^ (a[1] >> 24) ^ (a[2] << 8);

    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
}

void pi_1(uint32_t *a)
{
    a[0] = (a[0] >> 10) ^ (a[0] << 22);
    a[2] = (a[2] << 1) ^ (a[2] >> 31);
}

void pi_2(uint32_t *a)
{
    a[0] = (a[0] << 1) ^ (a[0] >> 31);
    a[2] = (a[2] >> 10) ^ (a[2] << 22);
}

void rho(uint32_t *a)
{ /* the round function       */
    theta(a);
    pi_1(a);
    gamma(a);
    pi_2(a);
}

void rndcon_gen(uint32_t strt, uint32_t *rblockb)
{ /* generates the round consblocknts */
    int i;

    for (i = 0; i <= NMBR; i++)
    {
        rblockb[i] = strt;
        strt <<= 1;
        if (strt & 0x10000)
            strt ^= 0x11011;
    }
}

void generate_keys(uint32_t *key)
{
    memset(Km, 0, sizeof(Km));
    memmove(Km, key, 12);
}

void threeway_encipher(uint32_t *block)
{
    uint32_t rcon[NMBR + 1];
    uint32_t a[3], k[3];

    a[0] = block[0];
    a[1] = block[1];
    a[2] = block[2];
    k[0] = (Km[0]);
    k[1] = (Km[1]);
    k[2] = (Km[2]);

    rndcon_gen(STRT_E, rcon);
    for (int i = 0; i < NMBR; i++)
    {
        a[0] ^= k[0] ^ (rcon[i] << 16);
        a[1] ^= k[1];
        a[2] ^= k[2] ^ rcon[i];
        rho(a);
    }
    a[0] ^= k[0] ^ (rcon[NMBR] << 16);
    a[1] ^= k[1];
    a[2] ^= k[2] ^ rcon[NMBR];
    theta(a);

    block[0] = a[0];
    block[1] = a[1];
    block[2] = a[2];
}

void threeway_decipher(uint32_t *block)
{
    uint32_t ki[3];          /* the `inverse' key             */
    uint32_t rcon[NMBR + 1]; /* the `inverse' round consblocknts */
    uint32_t a[3];

    a[0] = block[0];
    a[1] = block[1];
    a[2] = block[2];
    ki[0] = Km[0];
    ki[1] = Km[1];
    ki[2] = Km[2];

    theta(ki);
    mu(ki);

    rndcon_gen(STRT_D, rcon);

    mu(a);
    for (int i = 0; i < NMBR; i++)
    {
        a[0] ^= ki[0] ^ (rcon[i] << 16);
        a[1] ^= ki[1];
        a[2] ^= ki[2] ^ rcon[i];
        rho(a);
    }
    a[0] ^= ki[0] ^ (rcon[NMBR] << 16);
    a[1] ^= ki[1];
    a[2] ^= ki[2] ^ rcon[NMBR];
    theta(a);
    mu(a);

    block[0] = a[0];
    block[1] = a[1];
    block[2] = a[2];
}

int main()
{
    char key[16] = "#qianfei1234";
    generate_keys(key);
    // for (int i = 0; i < 3; i++)
    //     printf("0x%08x\n", Km[i]);
    char dablock[16] = "#qianfei1234";
    threeway_encipher(dablock);
    for (int i = 0; i < 3; i++)
        printf("0x%08x\n", dablock[i]);
    printf("\n");
    threeway_decipher(dablock);
    printf("%s\n", dablock);
}
