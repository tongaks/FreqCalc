#include "functions.h"

int StringCount(const char* str) {
    int count = 0;
    const char* temp = str;
    while ((temp = strstr(temp, "$$")) != NULL) {
        count++;
        temp += 2; // Move past the "$$"
    }

    return count + 1; // Number of tokens is delimiters + 1
}

void TUI(char* string) {
    system("clear");
    const char* str = string; 
    int count = StringCount(str);
    int width = 72;
    char strings[count][512];

    char* token = strtok(string, "$$");
    for (int i = 0; token != NULL; i++) {
        strcpy(strings[i], token);
        token = strtok(NULL, "$$");     
    }

    printf("\n\n\t");
    for (int i = 0; i < width; i++) printf("#"); printf("\n");
    for (int i = 0; i < count; i++) {
        printf("\t#");

        int num = strlen(strings[i]);
        int totalSpace = 70 - num;
        int leftSpace = totalSpace / 2;
        int rightSpace = totalSpace - leftSpace;

        for (int d = 0; d < leftSpace; d++) printf(" ");
        printf("%s", strings[i]);
        for (int d = 0; d < rightSpace; d++) printf(" "); printf("#\n");
    } 
    printf("\t");
    for (int i = 0; i < width; i++) printf("#"); printf("\n");
    return;
}