#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

char exp[] = "\
#!/usr/bin/env python\n\
from pwn import *\n\n\
context.log_level = 'debug'\n\
context.terminal = ['tmux', 'split', '-h']\n\n\
local = 1\n\
if local:\n\
    p = process('%s')\n\
    elf = ELF('%s')\n\
    libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')\n\
else:\n\
    pass\n\n\
gdb.attach(p)\n\n\
p.interactive()\n\n\
";

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [PROGRAM_NAME]\n", argv[0]);
        exit(-1);
    }
    char *binary = argv[1];
    FILE *fp = NULL;
    fp = fopen("exp.py", "w+");
    if (fp == NULL) {
        perror("fopen");
        exit(-2);
    }
    fprintf(fp, exp, binary, binary);
    fclose(fp);
    if (chmod("exp.py", 0755) != 0) {
        perror("chmod");
        exit(-3);
    }
    printf("[*] `exp.py` generated successfully.\n");
    exit(0);
}
