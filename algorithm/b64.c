#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAX 100

const char *base64payload = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int find_pos(char c)
{
    for(int i = 0; i < 65; i++)
        if(c == base64payload[i])
            return i;
    return -1;
}

unsigned char *base64_encode(const char *s, const int len)
{
    unsigned int sign = len % 3;
    unsigned int res_len = len % 3 ? ((len) / 3 + 1) * 4 : (len) / 3 * 4;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    for(i = 0, j = 0; i < len; i += 3, j += 4)
    {
        if(i + 2 >= len)
        {
            res[j] = (s[i] >> 2) & 0x3F;
            if(sign == 1)//因为只多出一个数据，故需要补两个'='
            {
                res[j + 1] = ((s[i] & 0x03) << 4) & 0x3F;
                res[j + 2] = 0x40;//0x40对应数字64，即为base64payload中下标为64的'='
                res[j + 3] = 0x40;
            }
            else if(sign == 2)//因为多出两个数据，故需要补一个'='
            {
                res[j + 1] = (((s[i] & 0x03) << 4) | ((s[i + 1] >> 4) & 0x0F));
                res[j + 2] = ((s[i + 1] & 0x0F) << 2) & 0x3F;
                res[j + 3] = 0x40;
                break;
            }
        }
        res[j] = (s[i] >> 2) & 0x3F;//取第一个字节的前六位，最高两位补零
        res[j + 1] = (((s[i] & 0x03) << 4) | ((s[i + 1] >> 4) & 0x0F));//取第一个字节的最后两位和第二个字节的前四位，最高两位补零
        res[j + 2] = (((s[i + 1] & 0x0F) << 2) | ((s[i + 2] >> 6) & 0x03));//取第二个字节的后四位和第三个字节的前两位，最高两位补零
        res[j + 3] = (s[i + 2] & 0x3F);//取第三个字节的最后六位，最高两位补零
    }
    for(j = 0; j < res_len; j++)
        res[j] = base64payload[res[j]];
    return res;
}

unsigned char *base64_decode(const char *s, const int len)
{
    unsigned int res_len = len / 4 * 3;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    int count = len / 4;
    for(i = 0; i < count; i++)
    {
        int s_index = i * 4;
        int res_index = i * 3;
        int buffer[4];//四个字节一组存入
        int sign = 0;
        for(j = 0; j < 4; j++)
            buffer[j] = find_pos(s[s_index + j]);
        if(i == count - 1)
            for(j = 0; j < 4; j++)
                if(buffer[j] == 0x40)//如果为'='，sign的值加一
                    sign++;
        res[res_index] = ((buffer[0] & 0x3F) << 2 | (buffer[1] & 0x30) >> 4);
        if(sign == 2)
            break;
        res[res_index + 1] = ((buffer[1] & 0x0f) << 4 | (buffer[2] & 0x3C) >> 2);
        if(sign == 1)
            break;
        res[res_index + 2] = ((buffer[2] & 0x03) << 6 | (buffer[3] & 0x3F));
    }
    return res;
}

int main()
{
    unsigned char s1[MAX];
    scanf("%s", s1);
    unsigned char *s2 = base64_encode((const char *)s1, strlen((const char *)s1));
    printf("%s\n", s2);
    unsigned char *s3 = base64_decode((const char *)s2, strlen((const char *)s2));
    printf("%s\n", s3);
    free(s2);
    free(s3);
    return 0;
}
