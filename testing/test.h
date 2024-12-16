#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int POP_SIZE = 0;
int* DATA_SET;

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
    int count = StringCount(string);
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
}

int InputValidation() {
    char INPUT_BUFFER[100];

    printf("\t[+] Enter here: ");
    fgets(INPUT_BUFFER, 100, stdin);

    for (int i = 0; i < strlen(INPUT_BUFFER); i++) {
        if (isalpha(INPUT_BUFFER[i])) return -1;
    } return atoi(INPUT_BUFFER);
}

int MainMenu() {
    char text[] = "Frequency Distribution Calculator$$Made by Denina & zantoa$$(1) New table$$(2) Open table$$(3) Exit"; 
    TUI(text);
    return InputValidation();
}

int AskLoadPrevData() {
    char text[] = "Previvous data count: 50$$[!] Load previous data?$$(1) Yes (2) No"; 
    TUI(text);
    int res = InputValidation();
}

void GetPopSize() {
    char text[] = "Enter the population size"; 
    TUI(text);
    POP_SIZE = InputValidation();
    DATA_SET = (int*) malloc(POP_SIZE * sizeof(int));
    memset(DATA_SET, 0, sizeof(DATA_SET));
}

void GetData() {
    for (int i = 0; i < POP_SIZE; i++) {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "Data #%i", i + 1);

        TUI(buffer);
        printf("\t\t"); // note: pag 12 new line print na sa new line para malinis
        for (int d = 0; d < POP_SIZE; d++) {
            if (d % 12 == 0) printf("\n\t\t");
            printf("[%i] ", DATA_SET[d]);
        } printf("\n\n");

        DATA_SET[i] = InputValidation();
    }
}

void DisplayData() {
    char text[] = "Here's the Frequency Distribution table$$Do you want to save the computation?$$(1) Yes (2) No";
    TUI(text);

    int UPPER_LIMITS[] = {56, 45, 56, 67, 67};
    int LOWER_LIMITS[] = {56, 35, 16, 27, 1};
    float UPPER_BOUNDARIES[] = {56.3, 45.5, 56.6, 67.3, 67.4};
    float LOWER_BOUNDARIES[] = {56.5, 45.5, 56.3, 67.5, 67.5};
    int FREQUENCIES[] = {4, 5, 7, 2, 8};
    int COMMULATIVE_FREQUENCIES[] = {4, 5, 7, 2, 8};
    int CLASS_MARKS[] = {34, 47, 36, 17, 87};
    int CLASS_WIDTH = 5;

    printf("\n\t\t");
    
    for (int i = 0; i < CLASS_WIDTH; i++) {
        if (i == 0) {
            printf("\t  CL ");
            printf("\t  f ");
            printf("  CF ");
            printf(" Xm ");
            printf("\t CB \n");
        }

        printf("\t\t");
        if (!(LOWER_LIMITS[i] < 10 || UPPER_LIMITS[i] < 10)) {
            printf("\t| %i-%i |", LOWER_LIMITS[i], UPPER_LIMITS[i]);     
        } else {
            printf("\t| %i -%i |", LOWER_LIMITS[i], UPPER_LIMITS[i]);            
        }
        
        if (!(FREQUENCIES[i] > 9)) {
            printf(" %i |", FREQUENCIES[i]);            
        } else {
            printf(" %i|", FREQUENCIES[i]);            
        }

        if (!(COMMULATIVE_FREQUENCIES[i] > 9)) {
            printf(" %i |", COMMULATIVE_FREQUENCIES[i]);
        } else {
            printf(" %i|", COMMULATIVE_FREQUENCIES[i]);
        }

        if (!(CLASS_MARKS[i] > 9))
            printf(" %i  |", CLASS_MARKS[i]);
        else
            printf(" %i |", CLASS_MARKS[i]);

        printf(" %.1f-%.1f |\n", LOWER_BOUNDARIES[i], UPPER_BOUNDARIES[i]);
    }

    printf("\n\t");
    // for (int i = 0; i < 72; i++) printf("#");
    printf("\n");
    printf("\t\t Maximum Value: %d\n", 34);
    printf("\t\t Minimum Value: %d\n", 45);
    printf("\t\t    ClassRange: %i\n", 56);
    printf("\t\tClass Interval: %i\n", 78);
    printf("\t\t   Class Width: %i\n", 56);
    printf("\t\t          Mean: %.2f\n", 45.4);
    printf("\t\t            SD: %.2f\n", 56.6);
    printf("\t\t      Variance: %.2f\n", 3453.3);
    printf("\t");
    // for (int i = 0; i < 72; i++) printf("#");
    printf("\n");

    InputValidation();

}

void GetOrder() {
    char text[] = "Please select$$(1) Descending order (2) Ascending order";
    TUI(text);
    InputValidation();
}