#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxim 0x10001
#define fuyi 0x10000
#define one 0xFFFF
#define ROUNDS 8

uint16_t Km[7][10];
uint16_t IKm[7][10];

enum TYPE
{
	ENCRYPT,
	DECRYPT
};

void char2word(uint16_t *w, const uint8_t *p)
{
	*w = (uint16_t)p[1] << 8 | (uint16_t)p[0];
}

void word2char(uint8_t *p, const uint16_t *w)
{
	p[1] = (uint8_t)((*w >> 8) & 0xFF);
	p[0] = (uint8_t)(*w & 0xFF);
}

/* multiplication using the Low-High algorithm */
uint16_t mul(uint16_t a, uint16_t b)
{
	long int p;
	long unsigned q;
	if (a == 0)
		p = maxim - b;
	else if (b == 0)
		p = maxim - a;
	else
	{
		q = (unsigned long)a * (unsigned long)b;
		p = (q & one) - (q >> 16);
		if (p <= 0)
			p = p + maxim;
	}
	return p & one;
}

/* compute inverse of xin by Euclidean gcd alg. */
uint16_t inv(uint16_t xin)
{
	long n1, n2, q, r, b1, b2, t;
	if (xin == 0)
		b2 = 0;
	else
	{
		n1 = maxim;
		n2 = xin;
		b2 = 1;
		b1 = 0;
		do
		{
			r = (n1 % n2);
			q = (n1 - r) / n2;
			if (r == 0)
			{
				if (b2 < 0)
					b2 = maxim + b2;
			}
			else
			{
				n1 = n2;
				n2 = r;
				t = b2;
				b2 = b1 - q * b2;
				b1 = t;
			}
		} while (r != 0);
	}
	return b2;
}

/* generate subkeys */
void generate_keys(uint16_t master_key[9])
{
	uint16_t S[54];
	int i, j, r;
	for (i = 1; i < 9; i++)
		S[i - 1] = master_key[i];
	/* shifts */
	for (i = 8; i < 54; i++)
	{
		if ((i + 2) % 8 == 0) /* for S[14],S[22],... */
			S[i] = ((S[i - 7] << 9) ^ (S[i - 14] >> 7)) & one;
		else if ((i + 1) % 8 == 0) /* for S[15],S[23],... */
			S[i] = ((S[i - 15] << 9) ^ (S[i - 14] >> 7)) & one;
		else
			S[i] = ((S[i - 7] << 9) ^ (S[i - 6] >> 7)) & one;
	}

	// get subkeys
	for (r = 1; r <= ROUNDS + 1; r++)
		for (j = 1; j < 7; j++)
			Km[j][r] = S[6 * (r - 1) + j - 1];

	// calculate reverse key
	for (j = 1; j <= ROUNDS + 1; j++)
	{
		IKm[1][ROUNDS - j + 2] = inv(Km[1][j]);
		IKm[4][ROUNDS - j + 2] = inv(Km[4][j]);

		if (j == 1 || j == ROUNDS + 1)
		{
			IKm[2][ROUNDS - j + 2] = (fuyi - Km[2][j]) & one;
			IKm[3][ROUNDS - j + 2] = (fuyi - Km[3][j]) & one;
		}
		else
		{
			IKm[2][ROUNDS - j + 2] = (fuyi - Km[3][j]) & one;
			IKm[3][ROUNDS - j + 2] = (fuyi - Km[2][j]) & one;
		}
	}

	for (j = 1; j <= ROUNDS + 1; j++)
	{
		IKm[5][ROUNDS + 1 - j] = Km[5][j];
		IKm[6][ROUNDS + 1 - j] = Km[6][j];
	}
}

/* encrypt algorithm */
void idea_cipher(uint16_t IN[5], uint16_t OUT[5], enum TYPE type)
{
	uint16_t x1, x2, x3, x4, kk, t1, t2;
	uint16_t tmp;
	uint16_t(*tkey)[10];
	if (type == ENCRYPT)
		tkey = Km;
	else if (type == DECRYPT)
		tkey = IKm;

	x1 = IN[1];
	x2 = IN[2];
	x3 = IN[3];
	x4 = IN[4];
	for (int i = 1; i <= 8; i++) /* the round function */
	{
		/* the group operation on 64-bits block */
		x1 = mul(x1, tkey[1][i]);
		x4 = mul(x4, tkey[4][i]);
		x2 = (x2 + tkey[2][i]) & one;
		x3 = (x3 + tkey[3][i]) & one;
		/* the function of the MA structure */
		kk = mul(tkey[5][i], (x1 ^ x3));
		t1 = mul(tkey[6][i], (kk + (x2 ^ x4)) & one);
		t2 = (kk + t1) & one;
		/* the involutary permutation PI */
		x1 = x1 ^ t1;
		x4 = x4 ^ t2;
		tmp = x2 ^ t2;
		x2 = x3 ^ t1;
		x3 = tmp;

		// printf("\n\t%1u-th rnd %6u\t%6u\t%6u\t%6u", r, x1, x2, x3, x4);
	}

	/* the output transformation */
	OUT[1] = mul(x1, tkey[1][ROUNDS + 1]);
	OUT[4] = mul(x4, tkey[4][ROUNDS + 1]);
	OUT[2] = (x3 + tkey[2][ROUNDS + 1]) & one;
	OUT[3] = (x2 + tkey[3][ROUNDS + 1]) & one;
}

int main()
{
	uint16_t master_key[9] = {0, 0x1234, 0xdead, 0xbeef, 0x6666, 0x1234, 0xdead, 0xbeef, 0x6666};

	generate_keys(master_key); /* generate encryption subkeys Z[i][r] */
	// printf("\nencryption keys\t  Z1\t  Z2\t  Z3\t  Z4\t  Z5\t  Z6");
	// for (int j = 1; j <= 9; j++)
	// {
	// 	printf("\n %3d-th round", j);
	// 	if (j == 9)
	// 		for (int i = 1; i <= 4; i++)
	// 			printf("\t%6d", Km[i][j]);
	// 	else
	// 		for (int i = 1; i <= 6; i++)
	// 			printf("\t%6d", Km[i][j]);
	// }

	// printf("\n\ndecryption keys\t  DK1\t  DK2\t  DK3\t  DK4\t  DK5\t  DK6");
	// for (int j = 1; j <= 9; j++)
	// {
	// 	printf("\n %3d-th round", j);
	// 	if (j == 9)
	// 		for (int i = 1; i <= 4; i++)
	// 			printf("\t%6d", IKm[i][j]);
	// 	else
	// 		for (int i = 1; i <= 6; i++)
	// 			printf("\t%6d", IKm[i][j]);
	// }

	uint16_t XX[5] = {0, 0x1234, 0xdead, 0xbeef, 0x6666};
	char *data = "#qianfei";
	for (int i = 0; i < 4; i++)
		char2word((XX + 1) + i, data + 2 * i);
	uint16_t TT[5], YY[5];
	printf("%d %d\n", sizeof(unsigned), sizeof(uint16_t));
	printf("\n\n plaintext  X\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n",
		   XX[1], XX[2], XX[3], XX[4]);

	idea_cipher(XX, YY, ENCRYPT); /* encipher XX to YY with key Z */

	printf("\n\n ciphertext Y\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n",
		   YY[1], YY[2], YY[3], YY[4]);
	printf("%d\n", sizeof(YY));
	unsigned char ciphertext[20];
	for (int i = 0; i < 4; i++)
	{
		word2char(ciphertext + 2 * i, (YY + 1) + i);
		printf("0x%02x 0x%02x ", ciphertext[2 * i], ciphertext[2 * i + 1]);
	}
	printf("\n");

	idea_cipher(YY, TT, DECRYPT); /* decipher YY to TT with key DK */

	printf("\n\n result     T\t0x%04x\t0x%04x\t0x%04x\t0x%04x\n",
		   TT[1], TT[2], TT[3], TT[4]);
	unsigned char plaintext[9];
	for (int i = 0; i < 4; i++)
	{
		word2char(plaintext + 2 * i, TT + 1 + i);
		printf("0x%02x 0x%02x ", plaintext[2 * i], plaintext[2 * i + 1]);
	}
	printf("\n");

	printf("%s\n", plaintext);
}
