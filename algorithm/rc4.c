#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

void rc4_init(unsigned char *sbox, unsigned char *key, unsigned long len)
{
    int j = 0;
    char t[MAX] = {0};
    unsigned char tmp = 0;
    for(int i = 0; i < MAX; i++)//初始化算法
    {
        sbox[i] = i;
        t[i] = key[i % len];
    }
    for(int i = 0; i < MAX; i++)//伪随机子密码生成算法
    {
        j = (j + sbox[i] + t[i]) % MAX;
        tmp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = tmp;
    }
}

unsigned char rc4_crypto(unsigned char *sbox, unsigned char *data, unsigned long len)
{
    int i = 0, j = 0;
    unsigned char tmp = 0;
    unsigned long k = 0;
    for(k = 0; k < len; k++)
    {
        i = (i + 1) % MAX;
        j = (j + sbox[i]) % MAX;
        tmp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = tmp;
        int t = (sbox[i] + sbox[j]) % MAX;
        data[k] ^= sbox[t];
    }
}

int main()
{
    unsigned char s1[MAX] = {0}, s2[MAX] = {0};
    char key[MAX] = {0}, data[2 * MAX] = {0};
    printf("Please input the key:\n");
    scanf("%s", key);
    printf("Please input the data:\n");
    scanf("%s", data);
    unsigned long len = strlen(data);
    rc4_init(s1, (unsigned char *)key, strlen(key));
    for(int i = 0; i < MAX; i++)
        s2[i] = s1[i];
    rc4_crypto(s1, (unsigned char *)data, len);
    printf("%s\n", data);
    rc4_crypto(s2, (unsigned char *)data, len);
    printf("%s\n", data);
    return 0;
}
