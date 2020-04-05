#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

char str[] = "#!/usr/bin/env python\nfrom pwn import *\n\ncontext.log_level = 'debug'\ncontext.terminal = ['lxterminal', '-e']\n\nlocal = 1\nif local:\n\tp = process('%s')\nelse:\n\tp = remote()\n\ngdb.attach(p)\n\np.interactive()\n";

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s PROGRAM_NAME\n", argv[0]);
        exit(-1);
    }
    FILE *fp = NULL;
    fp = fopen("exp.py", "w");
    fprintf(fp, str, argv[1]);
    fclose(fp);
    if (chmod("exp.py", 0755) != 0)
    {
        perror("chmod");
        exit(-2);
    }
    printf("Exploit.py generated successfully.\n");
    exit(0);
}