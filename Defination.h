#ifndef DEFINITION_H
#define DEFINITION_H

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// 📌 Function Prototypes

// Show MP3 tags in a user-friendly format
void viewmp3(char arr[][5], int n, int m, char *file);

// Edit a specific MP3 tag with new data
void editmp3(char *filename, char *tag, char *newdata);

// Display a loading/processing animation
void showLoading(const char *message);

#endif
