#include "functions.h"

int POPULATION_SIZE = 0;
int CLASS_INTERVAL = 0;
int CLASS_LIMIT_ORDER = 0;
int CLASS_WIDTH = 0;
int CLASS_RANGE = 0;

int *CLASS_SET;
int *UPPER_LIMITS;
int *LOWER_LIMITS;
int *FREQUENCIES;
int *COMMULATIVE_FREQUENCIES;

float *UPPER_BOUNDARIES;
float *LOWER_BOUNDARIES;
float *CLASS_MARKS;
float *MEAN_DEVIATION;
float *SQUARED_DEVIATION;

int MIN_DATA = 0;
int MAX_DATA = 0;
float MEAN = 0;
float STANDARD_DEVIATION = 0;
float TOTAL_SQUARED_DEVIATION = 0;
float VARIANCE = 0;

void GetPopulationSize() {
    printf("\n============================================================\n");
    printf("[+] Insert Population Size: ");
    scanf("%d", &POPULATION_SIZE);

    CLASS_SET = (int *) malloc(POPULATION_SIZE * sizeof(int));

    printf("[!] The population size is %i\n", POPULATION_SIZE);
}

void GetMeanValue() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        MEAN += CLASS_SET[i];
    }  MEAN /= 2;
}

void GetClassDatas() {
    printf("\n============================================================\n");
    for(int i = 0; i < POPULATION_SIZE; i++){
        printf("[+] Insert Class Content #%d: ", i + 1);
        scanf("%d", &CLASS_SET[i]);
    }
}

void GetSquaredDeviation() {
    SQUARED_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        SQUARED_DEVIATION[i] = abs(MEAN_DEVIATION[i] * MEAN_DEVIATION[i]);
    }

    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        TOTAL_SQUARED_DEVIATION += SQUARED_DEVIATION[i];
    }    
}

void GetStandardDeviation() {
    MEAN_DEVIATION = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        MEAN_DEVIATION[i] = CLASS_SET[i] - MEAN;
    }

    GetSquaredDeviation();
    STANDARD_DEVIATION = sqrt(TOTAL_SQUARED_DEVIATION / POPULATION_SIZE);
}

void GetVarianceValue() {
    VARIANCE = TOTAL_SQUARED_DEVIATION / POPULATION_SIZE;
}

void GetClassInterval() {
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

    CLASS_WIDTH = k;
    UPPER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    LOWER_LIMITS = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));
    COMMULATIVE_FREQUENCIES = (int *) malloc((CLASS_WIDTH + 1) * sizeof(int));

    k = (CLASS_RANGE / k);

    CLASS_INTERVAL = round(k);
}

void GetClassLimits() {
	int UpperBound, LowerBound;

    int iterator = 0;
    for (int i = MAX_DATA; i >= CLASS_WIDTH;) {
        LowerBound = i - (CLASS_INTERVAL - 1);
        UpperBound = i;

        UPPER_LIMITS[iterator] = UpperBound;
        LOWER_LIMITS[iterator] = LowerBound;

        i -= CLASS_INTERVAL;
        iterator++;
    }
}

void GetFrequencies() {
    for (int d = 0; d < CLASS_WIDTH + 1; d++) {
        int freq = 0;
        
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (CLASS_SET[i] <= UPPER_LIMITS[d] && CLASS_SET[i] >= LOWER_LIMITS[d]) {
                freq++;
            }
        }

        FREQUENCIES[d] = freq;
        freq = 0;
    }
}

void GetCommulativeFrequencies() {
    int last_val = 0;
    for (int i = 0; i <= CLASS_WIDTH; i++) {
        int val = FREQUENCIES[i];

        last_val += val;
        COMMULATIVE_FREQUENCIES[i] = last_val;
    }
}

void GetClassBoundariesAndClassMarks() {
    UPPER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    LOWER_BOUNDARIES = (float *) malloc((CLASS_WIDTH + 1) * sizeof(float));
    CLASS_MARKS = (float *) malloc((CLASS_WIDTH + 1) * sizeof(*CLASS_MARKS));

    for (int i = 0; i < POPULATION_SIZE; i++) {
        UPPER_BOUNDARIES[i] = UPPER_LIMITS[i] + 0.5;
        LOWER_BOUNDARIES[i] = LOWER_LIMITS[i] - 0.5;
    }
   

    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        CLASS_MARKS[i] = (LOWER_BOUNDARIES[i] + UPPER_BOUNDARIES[i]) / 2;
    }
}

void GetPopulationOrder() {
	printf("\n[!] Selection:   [ 0 Descending Order ]   [ 1 Ascending Order ]\n\n");

    do {
        printf("[+] Select Population Order: ");
        scanf("%d", &CLASS_LIMIT_ORDER);
    } while(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1);

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
            printf("\t   CB \n");
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
}