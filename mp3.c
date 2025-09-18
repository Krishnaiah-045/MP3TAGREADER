#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include "header.h"


void showLoading(const char *message)
{
    printf(YELLOW "⏳ %s" RESET, message);
    fflush(stdout);
    for(int i = 0; i < 3; i++)
    {
        usleep(300000); 
        printf(".");
        fflush(stdout);
    }
    printf("\n");
}

void viewmp3(char arr[][5], int n, int m, char *file)
{
    FILE *fp = fopen(file, "rb");
    if(!fp)
    {
        printf(RED "❌ Error: Could not open file %s\n" RESET, file);
        return;
    }

    showLoading("Fetching MP3 tag information");

    char header[10];
    fread(header, 1, 10, fp);
    if(strncmp(header, "ID3", 3) != 0)
    {
        printf(RED "❌ Error: No ID3 tag found in file.\n" RESET);
        fclose(fp);
        return;
    }

    printf(CYAN BOLD "\n================ MP3 TAG INFORMATION ================\n" RESET);

    char frame_id[5];
    while(fread(frame_id, 1, 4, fp) == 4)
    {
        frame_id[4] = '\0';

        int size = 0;
        fread(&size, 4, 1, fp);
        size = __builtin_bswap32(size);

        unsigned short flags;
        fread(&flags, 2, 1, fp);

        if(size <= 0) break;

        char *data = (char*)malloc(size + 1);
        fread(data, 1, size, fp);
        data[size] = '\0';

        if(strcmp(frame_id, "TIT2") == 0) 
            printf("🎵 " GREEN "Title     : %s\n" RESET, data + 1);
        if(strcmp(frame_id, "TPE1") == 0)
            printf("👤 " GREEN "Artist    : %s\n" RESET, data + 1);
        if(strcmp(frame_id, "TALB") == 0) 
            printf("💿 " GREEN "Album     : %s\n" RESET, data + 1);
        if(strcmp(frame_id, "TYER") == 0) 
            printf("📅 " GREEN "Year      : %s\n" RESET, data + 1);
        if(strcmp(frame_id, "TCOM") == 0) 
            printf("✍️  " GREEN "Composer  : %s\n" RESET, data + 1);
        if(strcmp(frame_id, "TCON") == 0) 
            printf("🎶 " GREEN "Genre     : %s\n" RESET, data + 1);

        free(data);
    }

    printf(CYAN "=====================================================\n\n" RESET);
    fclose(fp);
}

void editmp3(char *filename, char *tag, char *newdata)
{
    FILE *fp = fopen(filename, "rb+");
    if(!fp)
    {
        printf(RED "❌ [ERROR] Could not open file: %s\n" RESET, filename);
        return;
    }

    showLoading("Updating the tag data");

    char header[10];
    fread(header, 1, 10, fp);
    if(strncmp(header, "ID3", 3) != 0)
    {
        printf(RED "❌ [ERROR] No ID3 tag found in this MP3.\n" RESET);
        fclose(fp);
        return;
    }

    while(1)
    {
        long pos = ftell(fp);
        char frameHeader[10];
        if(fread(frameHeader, 1, 10, fp) < 10) break;

        char frameID[5] = {0};
        memcpy(frameID, frameHeader, 4);

        int size = (frameHeader[4] << 24) |
                   (frameHeader[5] << 16) |
                   (frameHeader[6] << 8)  |
                   (frameHeader[7]);

        if(size <= 0) break;

        if(strcmp(frameID, tag) == 0)
        {
            char *data = (char*)malloc(size);
            fread(data, 1, size, fp);

            if((int)strlen(newdata) > size - 1)  
            {
                printf(RED "❌ [ERROR] New data is too large for tag %s.\n" RESET, tag);
                free(data);
                fclose(fp);
                return;
            }

            fseek(fp, pos + 10, SEEK_SET);
            fputc(0, fp);
            fwrite(newdata, 1, strlen(newdata), fp);

            int remaining = size - 1 - strlen(newdata);
            for(int i = 0; i < remaining; i++) fputc(0, fp);

            printf(GREEN "✔️  [OK] Tag updated successfully!\n" RESET);
            printf(CYAN "   🔖 Field : %s\n" RESET, tag);
            printf(CYAN "   ✨ Value : %s\n" RESET, newdata);
            printf(YELLOW "ℹ️  Tip: Run with -v to verify updated tags.\n" RESET);

            free(data);
            fclose(fp);
            return;
        }

        fseek(fp, size, SEEK_CUR);
    }

    printf(RED "❌ [ERROR] Tag %s not found in file.\n" RESET, tag);
    fclose(fp);
}
