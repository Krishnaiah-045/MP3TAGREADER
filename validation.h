#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "header.h"  

int vail(char *s)
{
    char *pos1 = strstr(s, ".mp3");
    if(!pos1 || pos1 == s || *(pos1 + 4) != '\0')
    {
        printf(RED "❌ [ERROR] Invalid file extension! Please provide a valid .mp3 file.\n" RESET);
        return 0;
    }

    for(int i = 0; s[i] != '\0'; i++)
    {
        if(!isalpha(s[i]) && !isalnum(s[i]) && s[i] != '.')
        {
            printf(RED "❌ [ERROR] Invalid characters detected in filename: %s\n" RESET, s);
            printf(YELLOW "ℹ️  Allowed: letters, numbers, and '.' only.\n" RESET);
            return 0;
        }
    }

    printf(GREEN "✔️  Filename validated successfully!\n" RESET);
    return 1;
}
