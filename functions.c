#include "functions.h"
    
int POPULATION_SIZE = 0;
int CLASS_INTERVAL = 0;
int CLASS_LIMIT_ORDER = 0;
int CLASS_WIDTH = 0;
int CLASS_RANGE = 0;
char INPUT_BUFFER[100];
int DATA_COUNT = 0;
int ITERATOR = 0;

// arrays
int *CLASS_SET;
int *TEMP_CLASS_SET;
int *UPPER_LIMITS;
int *LOWER_LIMITS;
int *FREQUENCIES;
int *COMMULATIVE_FREQUENCIES;

float *UPPER_BOUNDARIES;
float *LOWER_BOUNDARIES;
float *CLASS_MARKS;
float *MEAN_DEVIATION;
float *SQUARED_DEVIATION;

// float and integer values for computations
int MIN_DATA = 0;
int MAX_DATA = 0;
float MEAN = 0;
float STANDARD_DEVIATION = 0;
float TOTAL_SQUARED_DEVIATION = 0;
float VARIANCE = 0;

// file handling
char FILE_NAME[256];

void GetPopulationSize() {
    printf("\n============================================================\n");
    printf("[+] Insert Population Size: ");
    scanf("%d", &POPULATION_SIZE);

    if (DATA_COUNT > POPULATION_SIZE) {
        printf("[!] Previous data count is greater than the population size.\n");
        exit(1);
    }

    CLASS_SET = (int *) malloc(POPULATION_SIZE * sizeof(int));
    printf("[!] The population size is %i\n", POPULATION_SIZE);
}

void GetMeanValue() {
    printf("Computing mean... ");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        MEAN += CLASS_SET[i];
    }  MEAN /= 2;
    printf("Done\n");
}

void GetPreviousDataCount() {
    printf("\n============================================================\n");
    FILE* temp_file;
    temp_file = fopen("temp.txt", "r");
    if (temp_file == NULL) perror("[!] Failed to open temp file.\n");

    char buffer[5];
    printf("[!] Getting the previous number of data...\n");
    while (true) {
        if (fgets(buffer, 4, temp_file) != NULL) {
            DATA_COUNT += 1;
        } else break;
    } 

    fclose(temp_file);
}

void LoadPreviousData() {
    FILE* temp_file;
    temp_file = fopen("temp.txt", "r");
    if (temp_file == NULL) perror("[!] Failed to open temp file.\n");

    char buffer[5];
    printf("[!] Setting the data to the list...\n");
    for (int i = 0; i < DATA_COUNT; i++) {
        if (fgets(buffer, 4, temp_file) != NULL) {
            CLASS_SET[i] = atoi(buffer);
        }
    }

    fclose(temp_file);
    printf("[!] Previous data loaded.\n");
    printf("============================================================\n");
}

void AskLoadPreviousData() {
    printf("\n============================================================\n");
    GetPreviousDataCount();

    int choice = 0;
    printf("[!] Load the previous data? (1) yes (2) no\n");
    printf("[!] Warning: choosing no clears out the previous data.\n");
    printf("[!] Previous number of data is: %i\n", DATA_COUNT);
    printf("[+] Enter here: ");
    scanf("%i", &choice);

    GetPopulationSize();

    if (InputValidation(choice) == 1) {
        LoadPreviousData();
        ITERATOR = DATA_COUNT;
    }

    FILE* clear_temp_file;  // clear temp file
    clear_temp_file = fopen("temp.txt", "w");
    fclose(clear_temp_file);
}

void GetClassDatas() {
    printf("\n============================================================\n");

    // create temp file to hold input data
    FILE* temp_file_create;
    temp_file_create = fopen("temp.txt", "r");
    
    if (temp_file_create == NULL) {
        temp_file_create = fopen("temp.txt", "w");
    } fclose(temp_file_create);

    printf("\n============================================================\n");
    for(int i = DATA_COUNT; i < POPULATION_SIZE; i++){
        FILE* temp_file;
        temp_file = fopen("temp.txt", "a");

        if (temp_file == NULL) perror("[!] Failed to open temp file.\n");

        while (true) {
            int data = 0;
            printf("[+] Insert Class Content #%d: ", i + 1);
            scanf("%d", &data);            

            if (InputValidation(data) != -1) {
                CLASS_SET[i] = data;
                break;
            } else {
                printf("[!] Error: Invalid input.\n");
            } 
        }

        fprintf(temp_file, "%i ", CLASS_SET[i]);
        fclose(temp_file);
    }

}

int InputValidation(int inputVariable) {
    bool isValid = true;
    // fgets(INPUT_BUFFER, 100, stdin);
    sprintf(INPUT_BUFFER, "%i", inputVariable);

    for (int i = 0; i < 100; i++) {
        if (isalpha(INPUT_BUFFER[i]) != 0) {
            isValid = false;
            break;
        }
    }

    if (isValid == true) inputVariable = atoi(INPUT_BUFFER);   // turn input char to int
    else return -1;

    for (int i = 0; i < 100; i++) INPUT_BUFFER[i] = '\0';     // clear input buffer
    return inputVariable;
}

void GetSquaredDeviation() {
    printf("Computing Squared SD... ");
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        SQUARED_DEVIATION[i] = abs(MEAN_DEVIATION[i] * MEAN_DEVIATION[i]);
    }

    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        TOTAL_SQUARED_DEVIATION += SQUARED_DEVIATION[i];
    }    
}

void GetStandardDeviation() {
    printf("Computing SD... ");
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        MEAN_DEVIATION[i] = CLASS_SET[i] - MEAN;
    }

    GetSquaredDeviation();
    STANDARD_DEVIATION = sqrt(TOTAL_SQUARED_DEVIATION / POPULATION_SIZE);
    printf("Done\n");
}

void GetVarianceValue() {
    printf("Computing Variance... ");
    VARIANCE = TOTAL_SQUARED_DEVIATION / POPULATION_SIZE;
    printf("Done\n");
}

void GetClassInterval() {
    printf("Computing class interval... ");
	int minData = CLASS_SET[0];
    int maxData = CLASS_SET[0];
    double k = 0;				// class width

    for (int i = 0; i < POPULATION_SIZE; i++){
        if (maxData < CLASS_SET[i])		// max 
        	maxData = CLASS_SET[i];
       
        if (CLASS_SET[i] < minData)		// min
        	minData = CLASS_SET[i];
    }

    MIN_DATA = minData;
    MAX_DATA = maxData;

    CLASS_RANGE = (double) maxData - minData;

    k = 1.0 + (3.3 * (log10(POPULATION_SIZE)));

    CLASS_WIDTH = round(k);

    COMMULATIVE_FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    
    UPPER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    LOWER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    CLASS_MARKS = (float *) malloc((CLASS_WIDTH + 1) * sizeof(*CLASS_MARKS));

    MEAN_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    SQUARED_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));

    k = (CLASS_RANGE / k);

    CLASS_INTERVAL = round(k);
    printf("Done\n");
}

void GetClassLimits() {
    printf("Computing class limit... ");
	int UpperBound, LowerBound;
    UPPER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    LOWER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));

    int iterator = 0;
    for (int i = MAX_DATA; i >= CLASS_WIDTH;) {
        LowerBound = i - (CLASS_INTERVAL - 1);
        UpperBound = i;

        UPPER_LIMITS[iterator] = UpperBound;
        LOWER_LIMITS[iterator] = LowerBound;

        i -= CLASS_INTERVAL;
        iterator++;
    } printf("Done\n");
}

void GetFrequencies() {
    printf("Computing frequencies... ");
    for (int d = 0; d < CLASS_WIDTH + 1; d++) {
        int freq = 0;
        
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (CLASS_SET[i] <= UPPER_LIMITS[d] && CLASS_SET[i] >= LOWER_LIMITS[d]) {
                freq++;
            }
        }

        FREQUENCIES[d] = freq;
        freq = 0;
    } printf("Done\n");
}

void GetCommulativeFrequencies() {
    printf("Computing commulative frequencies...   ");

    int last_val = 0;
    for (int i = 0; i <= CLASS_WIDTH + 1; i++) {
        int val = FREQUENCIES[i];

        last_val += val;
        COMMULATIVE_FREQUENCIES[i] = last_val;
    } printf("Done\n");
}

void GetClassBoundariesAndClassMarks() {
    printf("Computing class boundary and class mark... ");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        UPPER_BOUNDARIES[i] = UPPER_LIMITS[i] + 0.5;
        LOWER_BOUNDARIES[i] = LOWER_LIMITS[i] - 0.5;
    }
   

    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        CLASS_MARKS[i] = (LOWER_BOUNDARIES[i] + UPPER_BOUNDARIES[i]) / 2;
    } printf("Done\n");
}

void GetPopulationOrder() {
	printf("\n[!] Selection:   [ 0 Descending Order ]   [ 1 Ascending Order ]\n\n");

    do {
        printf("[+] Select Population Order: ");
        scanf("%d", &CLASS_LIMIT_ORDER);
    } while(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1);

    for (int i = 0; i < 60; i++) {
        printf("=");
    } printf("\n");
}

int DisplayMainMenu() {
    while (true) {
        int choice = 0;

        for (int i = 0; i < 60; i++) {
            printf("=");
        } printf("\n");

        printf("\tFrequency Distribution Table Calculator\n");

        for (int i = 0; i < 60; i++) {
            printf("=");
        } printf("\n");

        printf("\t\t(1) New table\n");
        printf("\t\t(2) Open existing table\n");
        printf("\t\t(3) Exit\n");
        printf("\t\tEnter: ");
        scanf("%i", &choice);

        while (getchar() != '\n');
        if (choice > 3 || choice < 1) {
            printf("Invalid input.\n");
            choice = 0;
            DisplayMainMenu();
        } else return choice;
    }
}

void DisplayInterval() {
	printf("\n");
	for (int i = 0; i < 60; i++) {
		printf("=");
	} printf("\n\n");

	printf("\t Maximum Value: %d\n", MAX_DATA);
    printf("\t Minimum Value: %d\n", MIN_DATA);
    printf("\t    ClassRange: %i\n", CLASS_RANGE);
    printf("\tClass Interval: %i\n", CLASS_INTERVAL);
    printf("\t   Class Width: %i\n", CLASS_WIDTH);
    printf("\t          Mean: %.2f\n", MEAN);
    printf("\t            SD: %.2f\n", STANDARD_DEVIATION);
    printf("\t      Variance: %.2f\n\n", VARIANCE);

	for (int i = 0; i < 60; i++) {
		printf("=");
	} printf("\n\n");
}

void DisplayFrequencyTable() {
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        if (i == 0) {
            printf("\t  CL ");
            printf("\t  f ");
            printf("  CF ");
            printf("  Xm ");
            printf("\t CB \n");
        }

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
            printf(" %.1f  |", CLASS_MARKS[i]);
        else
            printf(" %.1f |", CLASS_MARKS[i]);

        if (!((int)LOWER_BOUNDARIES[i] > 9))
            printf(" %.1lf -%.1lf |\n", LOWER_BOUNDARIES[i], UPPER_BOUNDARIES[i]);
        else
            printf(" %.1lf-%.1lf |\n", LOWER_BOUNDARIES[i], UPPER_BOUNDARIES[i]);
    }

    printf("\n");
    for (int i = 0; i < 60; i++) {
        printf("=");
    } printf("\n\n");
}

void GetFileName() {
    char choice[2];
    printf("[!] Do you want to save the computations?\n");
    printf("[+]Type Y|y or N|n: ");
    scanf("%1s", choice);

    if (strcmp("Y", choice) == 0 || strcmp("y", choice) == 0) {
        printf("\n[+] Enter file name: ");
        scanf("%s", FILE_NAME);
        CreateFile();
    } else return;
}

void CreateFile() {
    printf("\n[!] Saving file...\n");
    FILE* file;

    char full_filename[256];
    
    strcpy(full_filename, FILE_NAME);
    strcat(full_filename, ".txt");
    file = fopen(full_filename, "w");   
    
    fprintf(file, "data = ");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (i == POPULATION_SIZE - 1) 
            fprintf(file, "%d", CLASS_SET[i]);
        else fprintf(file, "%d, ", CLASS_SET[i]);
    }  fprintf(file, "\n");

    fclose(file);
    printf("[!] File saved as %s.txt.\n", FILE_NAME);
}