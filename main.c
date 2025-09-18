#include <stdio.h>
#include <string.h>
#include "header.h"
#include "validation.h"

int main(int argc, char *argv[])
{
    char arr[6][5] = {"TPE1", "TIT2", "TALB", "TYER", "TCON", "TCOM"};

    if(argc < 2)
    {
        printf(RED "❌ Error: Missing arguments!\n" RESET);
        printf(YELLOW "ℹ️  Usage:\n" RESET);
        printf("  %s -v <filename.mp3>\n", argv[0]);
        printf("  %s -e <filename.mp3> <option> <new_data>\n", argv[0]);
        printf("  %s -h\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "-h") == 0)
    {
        printf(CYAN BOLD "\n==================== HELP MENU ====================\n" RESET);
        printf(YELLOW "🎵 Usage:\n" RESET);
        printf("  -v <file>                View all MP3 tags\n");
        printf("  -e <file> <option> data  Edit a specific tag\n");
        printf("  -h                       Display this help menu\n");
        printf(CYAN "--------------------------------------------------\n" RESET);
        printf(YELLOW "✍️  Options for Editing:\n" RESET);
        printf("  -t   Title\n");
        printf("  -y   Year\n");
        printf("  -a   Album\n");
        printf("  -c   Composer\n");
        printf("  -A   Artist\n");
        printf("  -C   Genre\n");
        printf(CYAN "==================================================\n\n" RESET);
        return 0;
    }
    else if(strcmp(argv[1], "-v") == 0)
    {
        if(argc != 3)
        {
            printf(RED "❌ Error: Missing MP3 filename.\n" RESET);
            printf(YELLOW "ℹ️  Hint: Use %s -h for help.\n" RESET, argv[0]);
            return 1;
        }
        if(!vail(argv[2]))
        {
            return 1; // validation already prints error
        }
        printf(GREEN "🎵 MP3 File Loaded Successfully: %s\n" RESET, argv[2]);
        viewmp3(arr, 6, 5, argv[2]);
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(argc < 5)
        {
            printf(RED "❌ Error: Incorrect usage.\n" RESET);
            printf(YELLOW "ℹ️  Usage: %s -e <file.mp3> <option> <new_data>\n" RESET, argv[0]);
            return 1;
        }

        char *file = argv[2];
        char *opt = argv[3];
        char newdata[1024] = "";

        for(int i = 4; i < argc; i++)
        {
            strcat(newdata, argv[i]);
            if(i < argc - 1) strcat(newdata, " ");
        }

        if(!vail(file))
        {
            return 1; // validation already prints error
        }

        printf(GREEN "✍️  Editing MP3 File: %s\n" RESET, file);

        if(strcmp(opt, "-t") == 0)      editmp3(file, "TIT2", newdata);
        else if(strcmp(opt, "-y") == 0) editmp3(file, "TYER", newdata);
        else if(strcmp(opt, "-a") == 0) editmp3(file, "TALB", newdata);
        else if(strcmp(opt, "-c") == 0) editmp3(file, "TCOM", newdata);
        else if(strcmp(opt, "-A") == 0) editmp3(file, "TPE1", newdata);
        else if(strcmp(opt, "-C") == 0) editmp3(file, "TCON", newdata);
        else
        {
            printf(RED "❌ Error: Invalid option.\n" RESET);
            printf(YELLOW "ℹ️  Hint: Use %s -h for help.\n" RESET, argv[0]);
        }
    }
    else
    {
        printf(RED "❌ Error: Invalid command.\n" RESET);
        printf(YELLOW "ℹ️  Hint: Use %s -h for help.\n" RESET, argv[0]);
    }
    return 0;
}
