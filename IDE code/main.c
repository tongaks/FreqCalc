#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int mainMenu();
void uiStore();
int inputValidation();
void getPopulationSize();
void getClassDatas();
void getClassInterval();
void getPopulationOrder();
void getClassLimits();
void getFrequencies();
void getCumulativeFrequencies();
void getClassBoundariesAndClassMarks();
void getMeanValue();
void getStandardDeviation();
void getSquaredDeviation();
void getVarianceValue();
void displayInterval();
void displayFrequencyTable();

char USER_INPUT[100];
int INPUT_CHECK = 0;

int POPULATION_SIZE = 0;
int CLASS_INTERVAL = 0;
int CLASS_LIMIT_ORDER = 2;
int CLASS_RANGE = 0;
int CLASS_WIDTH = 0;

int* CLASS_SET;
int* UPPER_LIMITS;
int* LOWER_LIMITS;
int* FREQUENCIES;
int* CUMULATIVE_FREQUENCIES;

float* UPPER_BOUNDARIES;
float* LOWER_BOUNDARIES;
float* CLASS_MARKS;
float* MEAN_DEVIATION;
float* SQUARED_DEVIATION;

int MIN_DATA = 0;
int MAX_DATA = 0;
float MEAN = 0;
float STANDARD_DEVIATION = 0;
float TOTAL_SQUARED_DEVIATION = 0;
float VARIANCE = 0;

int main(){
    int programState = 0;
    while(programState != 3){
        programState = mainMenu();

        switch(programState){
            case 1:
                getPopulationSize();
                getClassDatas();
                getClassInterval();
                getPopulationOrder();
                getClassLimits();
                getFrequencies();
                getCumulativeFrequencies();
                getClassBoundariesAndClassMarks();
                getMeanValue();
                getStandardDeviation();
                getVarianceValue();

                displayInterval();
                displayFrequencyTable();
                break;

            case 2:

                break;
        }

    }

    return 0;
}

void tuiStore(int tuiIndex){ //Function to store textual user interface
    switch(tuiIndex){
        case 0:
            putchar(254);
            for(int i = 0; i < 58; i++){putchar(196);}
            putchar(254);
            printf("\n");

            break;

        case 1:
            printf("\n");
            break;


    }

}

int inputValidation(int inputVariable, int inputIndex){
    INPUT_CHECK = 0;
    fgets(USER_INPUT, 100, stdin);

    for(int i = 0; i < 100; i++){
        if(isalpha(USER_INPUT[i]) != 0){
            INPUT_CHECK = 1;

        }

    }

    if(INPUT_CHECK == 0){
        inputVariable = atoi(USER_INPUT);
        printf("[[%d]]\n", inputVariable);

    }   else{
            for(int i = 0; i < 100; i++){
                USER_INPUT[i] = '\0';
            }

        }

    switch(inputIndex){
        case 0:
            if(inputVariable < 1 || inputVariable > 3){
                printf("  [!] Please input a value from the selection...");
                inputVariable = 0;

            }

            break;

        case 1:
            if(inputVariable < 2){
            printf("  [!] Please input a value greater than 1...");
            inputVariable = 0;

            }

            break;

        case 2:
            if(inputVariable < 0){
                printf("  [!] Please input a value greater than 0...\n");
                inputVariable = -1;

            }

            break;

        case 3:
            if(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1){
                printf("  [!] Please select an input between 0 and 1...\n");
                //inputVariable = 2;
            }

            break;

        case 4:


            break;

    }

    return inputVariable;

}

int mainMenu(){
    int programState = 0;
    tuiStore(0);
    printf("           Frequency Distribution Table Calculator\n");
    tuiStore(0);

    printf("\n      Selection:\n\n");
    printf("            (1) New table\n");
    printf("            (2) Open existing table\n");
    printf("            (3) Exit\n\n");
    tuiStore(0);

    while(programState < 1 || programState > 3){
        printf("\n  [+] Enter: ");
        programState = inputValidation(programState, 0);

    }


    tuiStore(1);

    return programState;

}

void getPopulationSize(){

    tuiStore(0);
    while(POPULATION_SIZE < 2){
        printf("\n  [+] Insert Population Size: ");
        POPULATION_SIZE = inputValidation(POPULATION_SIZE, 1);

    }

    CLASS_SET = (int *) malloc(POPULATION_SIZE * sizeof(int));

    printf("  [!] The population size is %d\n\n", POPULATION_SIZE);

}

void getClassDatas(){
    tuiStore(0);


    for(int i = 0; i < POPULATION_SIZE; i++){
        CLASS_SET[i] = -1;
        while(CLASS_SET[i] < 0){
            printf("  [+] Insert Class Content #%d: ", i + 1);
            CLASS_SET[i] = inputValidation(CLASS_SET[i], 2);


        }

    }

    tuiStore(1);
}

void getClassInterval(){
    printf("  [%%] Computing class interval... \n");
	int minData = CLASS_SET[0];
    int maxData = CLASS_SET[0];
    double k = 0;				// class width

    for(int i = 0; i < POPULATION_SIZE; i++){
        if (maxData < CLASS_SET[i]){    //max
            maxData = CLASS_SET[i];

        }

        if (CLASS_SET[i] < minData){    //min
            minData = CLASS_SET[i];

        }

    }

    MIN_DATA = minData;
    MAX_DATA = maxData;

    CLASS_RANGE = (double) maxData - minData;

    k = 1.0 + (3.3 * (log10(POPULATION_SIZE)));

    CLASS_WIDTH = round(k);

    CUMULATIVE_FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));

    UPPER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    LOWER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    CLASS_MARKS = (float *) malloc((CLASS_WIDTH + 1) * sizeof(*CLASS_MARKS));

    MEAN_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    SQUARED_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));

    k = (CLASS_RANGE / k);

    CLASS_INTERVAL = round(k);
    printf("  [/] Class interval computed...\n");

}

void getPopulationOrder(){
    tuiStore(1);
    tuiStore(0);

	printf("\n  [!] Selection:   [ 0 Descending Order ]   [ 1 Ascending Order ]\n\n");

    while(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1){
        printf("  [+] Select Population Order: ");
        CLASS_LIMIT_ORDER = inputValidation(CLASS_LIMIT_ORDER, 3);

    }

    tuiStore(0);
    tuiStore(1);

}

void getClassLimits(){
    printf("     Computing class limit... ");
	int UpperBound, LowerBound;
    UPPER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    LOWER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));

    int iterator = 0;
    for(int i = MAX_DATA; i >= CLASS_WIDTH;){
        LowerBound = i - (CLASS_INTERVAL - 1);
        UpperBound = i;

        UPPER_LIMITS[iterator] = UpperBound;
        LOWER_LIMITS[iterator] = LowerBound;

        i -= CLASS_INTERVAL;
        iterator++;

    }

    printf("     Done\n");

}

void getFrequencies(){
    printf("     Computing frequencies... ");

    for(int d = 0; d < CLASS_WIDTH + 1; d++){
        int freq = 0;

        for (int i = 0; i < POPULATION_SIZE; i++){
            if (CLASS_SET[i] <= UPPER_LIMITS[d] && CLASS_SET[i] >= LOWER_LIMITS[d]){
                freq++;

            }

        }

        FREQUENCIES[d] = freq;
        freq = 0;

    }

    printf("     Done\n");

}

void getCumulativeFrequencies(){
    printf("     Computing cumulative frequencies...   ");
    int last_val = 0;

    for(int i = 0; i <= CLASS_WIDTH + 1; i++){
        int val = FREQUENCIES[i];
        last_val += val;
        CUMULATIVE_FREQUENCIES[i] = last_val;

    }

    printf("Done\n");

}

void getClassBoundariesAndClassMarks(){
    printf("     Computing class boundary and class mark... ");
    for(int i = 0; i < POPULATION_SIZE; i++){
        UPPER_BOUNDARIES[i] = UPPER_LIMITS[i] + 0.5;
        LOWER_BOUNDARIES[i] = LOWER_LIMITS[i] - 0.5;

    }


    for(int i = 0; i < CLASS_WIDTH + 1; i++){
        CLASS_MARKS[i] = (LOWER_BOUNDARIES[i] + UPPER_BOUNDARIES[i]) / 2;

    }

    printf("     Done\n");

}

void getMeanValue(){
    printf("     Computing mean... ");
    for(int i = 0; i < POPULATION_SIZE; i++){
        MEAN += CLASS_SET[i];

    }

    MEAN /= 2;
    printf("     Done\n");

}

void getStandardDeviation(){
    printf("     Computing SD... ");
    for(int i = 0; i < CLASS_WIDTH + 1; i++){
        MEAN_DEVIATION[i] = CLASS_SET[i] - MEAN;

    }

    getSquaredDeviation();
    STANDARD_DEVIATION = sqrt(TOTAL_SQUARED_DEVIATION / POPULATION_SIZE);
    printf("     Done\n");

}

void getSquaredDeviation(){
    printf("Computing Squared SD... ");
    for(int i = 0; i < CLASS_WIDTH + 1; i++){
        SQUARED_DEVIATION[i] = abs(MEAN_DEVIATION[i] * MEAN_DEVIATION[i]);

    }

    for(int i = 0; i < CLASS_WIDTH + 1; i++){
        TOTAL_SQUARED_DEVIATION += SQUARED_DEVIATION[i];

    }

}

void getVarianceValue(){
    printf("     Computing Variance... ");
    VARIANCE = TOTAL_SQUARED_DEVIATION / POPULATION_SIZE;
    printf("     Done\n");

}

void displayInterval() {
	tuiStore(1);
	tuiStore(0);
	tuiStore(1);
	tuiStore(1);

	printf("\t     Maximum Value: %d\n", MAX_DATA);
    printf("\t     Minimum Value: %d\n", MIN_DATA);
    printf("\t        ClassRange: %i\n", CLASS_RANGE);
    printf("\t    Class Interval: %i\n", CLASS_INTERVAL);
    printf("\t       Class Width: %i\n", CLASS_WIDTH);
    printf("\t              Mean: %.2f\n", MEAN);
    printf("\tStandard Deviation: %.2f\n", STANDARD_DEVIATION);
    printf("\t          Variance: %.2f\n\n", VARIANCE);

	tuiStore(0);
	tuiStore(1);
	tuiStore(1);

}

void displayFrequencyTable(){
    for(int i = 0; i < CLASS_WIDTH + 1; i++){
        if(i == 0){
            printf("\t  CL ");
            printf("\t  f ");
            printf("  CF ");
            printf("  Xm ");
            printf("\t CB \n");

        }

        if(!(LOWER_LIMITS[i] < 10 || UPPER_LIMITS[i] < 10)){
            printf("\t| %i-%i |", LOWER_LIMITS[i], UPPER_LIMITS[i]);

        }   else{
                printf("\t| %i -%i |", LOWER_LIMITS[i], UPPER_LIMITS[i]);

            }

        if(!(FREQUENCIES[i] > 9)){
            printf(" %i |", FREQUENCIES[i]);

        }   else{
                printf(" %i|", FREQUENCIES[i]);

            }

        if(!(CUMULATIVE_FREQUENCIES[i] > 9)){
            printf(" %i |", CUMULATIVE_FREQUENCIES[i]);

        }   else{
                printf(" %i|", CUMULATIVE_FREQUENCIES[i]);

            }

        if(!(CLASS_MARKS[i] > 9)){
            printf(" %.1f  |", CLASS_MARKS[i]);

        }   else{
                printf(" %.1f |", CLASS_MARKS[i]);

            }

        if(!((int)LOWER_BOUNDARIES[i] > 9)){
            printf(" %.1lf -%.1lf |\n", LOWER_BOUNDARIES[i], UPPER_BOUNDARIES[i]);

        }   else{
                printf(" %.1lf-%.1lf |\n", LOWER_BOUNDARIES[i], UPPER_BOUNDARIES[i]);

            }

    }

}
