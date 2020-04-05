#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

const char *base16payload = "0123456789ABCDEF=";

int find_pos(char c) {
    for(int i = 0; i < 15; i++) {
        if(c == base16payload[i]) {
            return i;
        }
    }
    return -1;
}

unsigned char *base16_encode(const char *s, const int len) {
    unsigned int sign = len % 4;
    unsigned int res_len = len * 2;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    for(i = 0, j = 0; i < len; i += 4, j += 8) {
        if(i + 4 >= len) {
            res[j] = (s[i] >> 4) & 0x0F;
            if(sign == 1) {
                res[j + 1] = s[i] & 0x0F;
                res[j + 2] = 0x10;
                res[j + 3] = 0x10;
                res[j + 4] = 0x10;
                res[j + 5] = 0x10;
                res[j + 6] = 0x10;
                res[j + 7] = 0x10;
                break;
            } else if(sign == 2) {
                res[j + 1] = s[i] & 0x0F;
                res[j + 2] = (s[i + 1] >> 4) & 0x0F;
                res[j + 3] = s[i + 1] & 0x0F;
                res[j + 4] = 0x10;
                res[j + 5] = 0x10;
                res[j + 6] = 0x10;
                res[j + 7] = 0x10;
                break;
            } else if(sign == 3) {
                res[j + 1] = s[i] & 0x0F;
                res[j + 2] = (s[i + 1] >> 4) & 0x0F;
                res[j + 3] = s[i + 1] & 0x0F;
                res[j + 4] = (s[i + 2] >> 4) & 0x0F;
                res[j + 5] = s[i + 2] & 0x0F;
                res[j + 6] = 0x10;
                res[j + 7] = 0x10;
                break;
            }
        }
        res[j] = (s[i] >> 4) & 0x0F;
        res[j + 1] = s[i] & 0x0F;
        res[j + 2] = (s[i + 1] >> 4) & 0x0F;
        res[j + 3] = s[i + 1] & 0x0F;
        res[j + 4] = (s[i + 2] >> 4) & 0x0F;
        res[j + 5] = s[i + 2] & 0x0F;
        res[j + 6] = (s[i + 3] >> 4) & 0x0F;
        res[j + 7] = s[i + 3] & 0x0F;
    }
    for(j = 0; j < res_len; j++) {
        res[j] = base16payload[res[j]];
    }
    return res;
}

unsigned char *base16_decode(const char *s, const int len) {
    unsigned int res_len = len / 2;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    int count = len / 8;
    for(i = 0; i < count; i++) {
        int s_index = i * 8;
        int res_index = i * 4;
        int buffer[8];
        for(j = 0; j < 8; j++) {
            buffer[j] = find_pos(s[s_index + j]);
        }
        int sign;
        if(i == count - 1) {
            for(j = 0; j < 8; j++) {
                if(buffer[j] == 0x10) {
                    sign++;
                }
            }
        }
        res[res_index] = ((buffer[0] & 0x0F) << 4) | (buffer[1] & 0x0F);
        if(sign == 3) {
            break;
        }
        res[res_index + 1] = ((buffer[2] & 0x0F) << 4) | (buffer[3] & 0x0F);
        if(sign == 2) {
            break;
        }
        res[res_index + 2] = ((buffer[4] & 0x0F) << 4) | (buffer[5] & 0x0F);
        if(sign == 1) {
            break;
        }
        res[res_index + 3] = ((buffer[6] & 0x0F) << 4) | (buffer[7] & 0x0F);
    }
    return res;
}

int main() {
    unsigned char s1[MAX];
    scanf("%s", s1);
    unsigned char *s2 = base16_encode((const char *)s1, strlen((const char *)s1));
    printf("%s\n", s2);
    unsigned char *s3 = base16_decode((const char *)s2, strlen((const char *)s2));
    printf("%s\n", s3);
    free(s2);
    free(s3);
    return 0;
}
