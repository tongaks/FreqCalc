#include "functions.h"
    
int POPULATION_SIZE = 0;
int CLASS_INTERVAL = 0;
int CLASS_LIMIT_ORDER = 0;
int CLASS_WIDTH = 0;
int CLASS_RANGE = 0;
int DATA_COUNT = 0;

// arrays
int *CLASS_SET;
int *ANOTHER_UPPER_LIMITS;
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

    while (true) {
        printf("[+] Insert Population Size: ");
        POPULATION_SIZE = InputValidation();

        if (POPULATION_SIZE != -1) {
            CLASS_SET = (int *) malloc(POPULATION_SIZE * sizeof(int));
            printf("[!] The population size is %i\n", POPULATION_SIZE);        
            break;
        } else if (POPULATION_SIZE > 5) {
            printf("Hmmm?\n");
        } else printf("Invalid input.\n");        
    }
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

    char buffer[5];
    FILE* temp_file = fopen("temp.txt", "r");
    while (true) {
        if (fgets(buffer, 4, temp_file) != NULL) {
            DATA_COUNT += 1;
        } else break;
    }

    fclose(temp_file);
}

bool CheckTempFile() {
    FILE* check = fopen("temp.txt", "r");
    if (check == NULL) {
        printf("[!] Failed to find temp file. Creating...\n");
        FILE* create = fopen("temp.txt", "w"); fclose(create);        
        printf("[!] temp.txt is created. Please open the system again.\n");
        exit(1);
    } fclose(check);
    return true;
}

void LoadPreviousData() {
    FILE* temp_file = fopen("temp.txt", "r"); 

    fseek(temp_file, 0, SEEK_END);
    int file_size = ftell(temp_file);
    fseek(temp_file, 0, SEEK_SET);

    char buffer[file_size + 1];
    fgets(buffer, file_size + 1, temp_file);
    fclose(temp_file);

    char* token = strtok(buffer, " ");
    for (int i = 0; token != NULL; i++) {
        CLASS_SET[i] = atoi(token);
        token = strtok(NULL, " ");        
    }

    printf("\n[!] Previous data loaded.\n");
    DisplayClassSet();
    printf("============================================================\n");
}

void AskLoadPreviousData() {
    GetPreviousDataCount();
    if (DATA_COUNT == 0) {
        while (getchar() != '\n');
        GetPopulationSize();
        GetClassDatas();
        return;        
    }

    printf("[!] Previous data count: %i\n", DATA_COUNT);
    printf("[!] Load the previous data? (1) yes (2) no\n");
    printf("[!] Warning: choosing no clears out the previous data.\n");

    while (true) {
        while (getchar() != '\n');
        printf("[+] Enter here: ");
        int res = InputValidation(0);
        
        if (res == 1) {
            GetPopulationSize();
            if (DATA_COUNT > POPULATION_SIZE) {
                Warning("Previous data count is greater than the population size\n");
                exit(1);
            } else if (DATA_COUNT == POPULATION_SIZE) {
                Warning("Previous data count and population is the same. Continuing to computation");
                LoadPreviousData();
            } break;
        } else if (res == 2) {
            GetPopulationSize();
            break;
        } else {
            printf("Invalid input. Press enter to try again\n");
        } 
    }


    FILE* clear_temp_file;  // clear temp file
    clear_temp_file = fopen("temp.txt", "w");
    fclose(clear_temp_file);
    GetClassDatas();            
}

void GetClassDatas() {
    printf("\n============================================================\n");

    CheckTempFile();

    printf("\n============================================================\n");
    for (int i = DATA_COUNT; i < POPULATION_SIZE; i++) {
        while (true) {
            printf("[+] Insert Class Content #%d: ", i + 1);

            int res = InputValidation(0);
            if (res == -1 || res == 0) {
                Warning("Invalid input.");
            } else {
                CLASS_SET[i] = res;
                break;
            } 
        }

        FILE* temp_file = fopen("temp.txt", "a");
        fprintf(temp_file, "%i ", CLASS_SET[i]);
        fclose(temp_file);
    }

}

int InputValidation() {
    char buffer[100];
    fgets(buffer, 100, stdin);

    for (int i = 0; i < strlen(buffer); i++) {
        if (isalpha(buffer[i])) return -1;
    } return atoi(buffer);
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
    printf("Class widht: %i\n", CLASS_WIDTH);

    COMMULATIVE_FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    
    UPPER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    LOWER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    CLASS_MARKS = (float *) malloc((CLASS_WIDTH + 1) * sizeof(*CLASS_MARKS));

    MEAN_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    SQUARED_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));

    ANOTHER_UPPER_LIMITS = (int*) malloc((CLASS_WIDTH + 1) * sizeof(int));

    CLASS_INTERVAL = round((CLASS_RANGE / k));
    printf("interval: %i\n", CLASS_INTERVAL);
    printf("Done\n");
}

void GetClassLimits() {
    printf("Computing class limit... ");
    UPPER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    LOWER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));

    int iterator = 0;
    for (int i = MAX_DATA; i > CLASS_WIDTH + 1;) {
    	int UpperBound = i;
        int LowerBound = i - (CLASS_INTERVAL - 1);

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

        for (int i = 0; i < CLASS_WIDTH + 1; i++) {
            ANOTHER_UPPER_LIMITS[i] = UPPER_LIMITS[i];
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
    } printf("Done.\n");
}

void GetClassBoundariesAndClassMarks() {
    printf("Computing class boundary and class mark... ");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        UPPER_BOUNDARIES[i] = UPPER_LIMITS[i] + 0.5;
        LOWER_BOUNDARIES[i] = LOWER_LIMITS[i] - 0.5;
    }

    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        CLASS_MARKS[i] = (LOWER_BOUNDARIES[i] + UPPER_BOUNDARIES[i]) / 2;
    } printf("Done.\n");
}

void GetPopulationOrder() {
	printf("\n[!] Selection:   (0) Descending Order (1) Ascending Order\n\n");

    do {
        printf("[+] Select sorting order: ");
        scanf("%d", &CLASS_LIMIT_ORDER);
    } while(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1);

    for (int i = 0; i < 60; i++) printf("=");
    printf("\n");
}

int DisplayMainMenu() {
    while (true) {
        int choice = 0;

        for (int i = 0; i < 60; i++) printf("=");
        printf("\n");

        printf("\tFrequency Distribution Table Calculator\n");

        for (int i = 0; i < 60; i++) printf("=");
        printf("\n");

        printf("\t\t(1) New table\n");
        printf("\t\t(2) Open existing table\n");
        printf("\t\t(3) Exit\n");
        printf("\t\tEnter: ");
        scanf("%i", &choice);

        if ((choice > 3 || choice < 1) && InputValidation(choice) != -1) {
            printf("Invalid input.\n");
            continue;
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

void DisplayClassSet() {
    printf("[!] Dataset:\n");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (i == POPULATION_SIZE - 1) printf("%i ", CLASS_SET[i]);
        else printf("%i, ", CLASS_SET[i]);
    } printf("\n");
}

void DisplayTable() {
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
    printf("[+] Type Y|y or N|n: ");
    scanf("%1s", choice);

    if (strcmp("Y", choice) == 0 || strcmp("y", choice) == 0) {
        printf("\n[+] Enter file name: ");
        scanf("%s", FILE_NAME);
        CreateFile();
    } else return;
}

void CreateFile() {
    printf("\n[!] Saving file...\n");

    char full_filename[256];
    strcpy(full_filename, FILE_NAME);
    strcat(full_filename, ".txt");
    printf("[!] Full filename: %s\n", full_filename);

    FILE* create_file = fopen(full_filename, "w");
    fclose(create_file);

    FILE* file = fopen(full_filename, "a");
    if (file == NULL) Warning("File not found.");

    for (int i = 0; i < POPULATION_SIZE; i++) {
        char buffer[256];
        int val = CLASS_SET[i];
        sprintf(buffer, "%i ", val);
        fputs(buffer, file);
    }

    fclose(file);
    printf("[!] File saved as %s.txt.\n", FILE_NAME);
}

void LoadSavedData() {
    printf("\n[+] Enter file name: ");
    scanf("%s", FILE_NAME);
}

void Warning(char* msg) {
    printf("[!] Warning: %s.\n", msg);
}

void ClearArrayAndVariables() {
    memset(CLASS_SET, 0, sizeof(CLASS_SET));
    memset(UPPER_LIMITS, 0, sizeof(UPPER_LIMITS));
    memset(LOWER_LIMITS, 0, sizeof(LOWER_LIMITS));
    memset(FREQUENCIES, 0, sizeof(FREQUENCIES));
    memset(COMMULATIVE_FREQUENCIES, 0, sizeof(COMMULATIVE_FREQUENCIES));
    memset(UPPER_BOUNDARIES, 0, sizeof(UPPER_BOUNDARIES));
    memset(LOWER_BOUNDARIES, 0, sizeof(LOWER_BOUNDARIES));
    memset(CLASS_MARKS, 0, sizeof(CLASS_MARKS));
    memset(MEAN_DEVIATION, 0, sizeof(MEAN_DEVIATION));
    memset(SQUARED_DEVIATION, 0, sizeof(SQUARED_DEVIATION));

    POPULATION_SIZE = 0;
    CLASS_INTERVAL = 0;
    CLASS_LIMIT_ORDER = 0;
    CLASS_WIDTH = 0;
    CLASS_RANGE = 0;
    DATA_COUNT = 0;

    MIN_DATA = 0;
    MAX_DATA = 0;
    MEAN = 0;
    STANDARD_DEVIATION = 0;
    TOTAL_SQUARED_DEVIATION = 0;
    VARIANCE = 0;
}