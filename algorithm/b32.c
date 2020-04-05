#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

const char *base32payload = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567=";

int find_pos(char c) {
    for(int i = 0; i < 31; i++) {
        if(c == base32payload[i]) {
            return i;
        }
    }
    return -1;
}

unsigned char *base32_encode(const char *s, const int len) {
    unsigned int sign = len % 5;
    unsigned int res_len = len % 5 ? ((len) / 5 + 1) * 8 : (len) / 5 * 8;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    for(i = 0, j = 0; i < len; i += 5, j += 8) {
        if(i + 4 >= len) {
            res[j] = (s[i] >> 3) & 0x1F;
            if(sign == 1) {
                res[j + 1] = (s[i] << 2) & 0x1C;
                res[j + 2] = 0x20;
                res[j + 3] = 0x20;
                res[j + 4] = 0x20;
                res[j + 5] = 0x20;
                res[j + 6] = 0x20;
                res[j + 7] = 0x20;
                break;
            } else if(sign == 2) {
                res[j + 1] = ((s[i] << 2) & 0x1C) | ((s[i + 1] >> 3) & 0x18);
                res[j + 2] = (s[i + 1] >> 1) & 0x1F;
                res[j + 3] = (s[i + 1] << 4) & 0x10;
                res[j + 4] = 0x20;
                res[j + 5] = 0x20;
                res[j + 6] = 0x20;
                res[j + 7] = 0x20;
                break;
            } else if(sign == 3) {
                res[j + 1] = ((s[i] << 2) & 0x1C) | ((s[i + 1] >> 3) & 0x18);
                res[j + 2] = (s[i + 1] >> 1) & 0x1F;
                res[j + 3] = ((s[i + 1] << 4) & 0x10) | ((s[i + 2] >> 4) & 0x0F);
                res[j + 4] = (s[i + 2] << 1) & 0x1E;
                res[j + 5] = 0x20;
                res[j + 6] = 0x20;
                res[j + 7] = 0x20;
                break;
            } else if(sign == 4) {
                res[j + 1] = ((s[i] << 2) & 0x1C) | ((s[i + 1] >> 3) & 0x18);
                res[j + 2] = (s[i + 1] >> 1) & 0x1F;
                res[j + 3] = ((s[i + 1] << 4) & 0x10) | ((s[i + 2] >> 4) & 0x0F);
                res[j + 4] = ((s[i + 2] << 1) & 0x1E) | ((s[i + 3] >> 3) & 0x10);
                res[j + 5] = (s[i + 3] >> 2) & 0x1F;
                res[j + 6] = (s[i + 3] << 3) & 0x18;
                res[j + 7] = 0x20;
                break;
            }
        }
        res[j] = (s[i] >> 3) & 0x1F;
        res[j + 1] = ((s[i] << 2) & 0x1C) | ((s[i + 1] >> 6) & 0x03);
        res[j + 2] = (s[i + 1] >> 1) & 0x1F;
        res[j + 3] = ((s[i + 1] << 4) & 0x10) | ((s[i + 2] >> 4) & 0x0F);
        res[j + 4] = ((s[i + 2] << 1) & 0x1E) | ((s[i + 3] >> 3) & 0x10);
        res[j + 5] = (s[i + 3] >> 2) & 0x1F;
        res[j + 6] = ((s[i + 3] << 3) & 0x18) | ((s[i + 4] >> 5) & 0x07);
        res[j + 7] = s[i + 4] & 0x1F;
    }
    for(j = 0; j < res_len; j++) {
        res[j] = base32payload[res[j]];
    }
    return res;
}

unsigned char *base32_decode(const char *s, const int len) {
    unsigned int res_len = len / 8 * 5;
    unsigned int i = 0, j = 0;
    unsigned char *res = (unsigned char *)malloc(res_len + 1);
    memset(res, 0, res_len + 1);
    int count = len / 8;
    for(i = 0; i < count; i++) {
        int s_index = i * 8;
        int res_index = i * 5;
        int buffer[8];
        int sign = 0;
        for(j = 0; j < 8; j++) {
            buffer[j] = find_pos(s[s_index + j]);
        }
        if(i == count - 1) {
            for(j = 0; j < 8; j++) {
                if(buffer[j] == 0x20) {
                    sign++;
                }
            }
        }
        res[res_index] = ((buffer[0] & 0x1F) << 3) | ((buffer[1] & 0x1C) >> 2);
        if(sign == 4) {
            break;
        }
        res[res_index + 1] = ((buffer[1] & 0x03) << 6) | ((buffer[2] & 0x1F) << 1) | ((buffer[3] & 0x10) >> 4);
        if(sign == 3) {
            break;
        }
        res[res_index + 2] = ((buffer[3] & 0x0F) << 4) | ((buffer[4] & 0x1E) >> 1);
        if(sign == 2) {
            break;
        }
        res[res_index + 3] = ((buffer[4] & 0x01) << 7) | ((buffer[5] & 0x1F) << 2) | ((buffer[6] & 0x18) >> 3);
        if(sign == 1) {
            break;
        }
        res[res_index + 4] = ((buffer[6] & 0x07) << 5) | (buffer[7] & 0x1F);
    }
    return res;
}

int main() {
    unsigned char s1[MAX];
    scanf("%s", s1);
    unsigned char *s2 = base32_encode((const char *)s1, strlen((const char *)s1));
    printf("%s\n", s2);
    unsigned char *s3 = base32_decode((const char *)s2, strlen((const char *)s2));
    printf("%s\n", s3);
    free(s2);
    free(s3);
    return 0;
}
