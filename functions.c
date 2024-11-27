#include "functions.h"

int POPULATION_SIZE = 0;
int CLASS_INTERVAL = 0;
int CLASS_LIMIT_ORDER = 0;
int CLASS_WIDTH = 0;
int CLASS_RANGE = 0;

int *CLASS_SET;
int *UPPER_LIMITS;
int *LOWER_LIMITS;

int MIN_DATA = 0;
int MAX_DATA = 0;

void GetPopulationSize() {
    printf("[+] Insert Population Size: ");
    scanf("%d", &POPULATION_SIZE);

    CLASS_SET = (int *) malloc(POPULATION_SIZE * sizeof(int));

    printf("[!] The population size is %i\n", POPULATION_SIZE);
}

void GetClassDatas() {
    for(int i = 0; i < POPULATION_SIZE; i++){
        printf("[+] Insert Class Content #%d: ", i + 1);
        scanf("%d", &CLASS_SET[i]);
    }
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
    
}

void GetPopulationOrder() {
	printf("\n[!] Selection:   [ 0 Descending Order ]   [ 1 Ascending Order ]\n\n");

    do {
        printf("[+] Select Population Order: ");
        scanf("%d", &CLASS_LIMIT_ORDER);
    } while(CLASS_LIMIT_ORDER < 0 || CLASS_LIMIT_ORDER > 1);

}

void DisplayInterval() {
	printf("\n");
	for (int i = 0; i < 60; i++) {
		printf("=");
	} printf("\n\n");

	printf(" Maximum Value: [%d]\n", MAX_DATA);
    printf(" Minimum Value: [%d]\n", MIN_DATA);
    printf("    ClassRange: [%i]\n", CLASS_RANGE);
    printf("Class Interval: [%i]\n", CLASS_INTERVAL);
    printf("   Class Width: [%i]\n\n", CLASS_WIDTH);

	for (int i = 0; i < 60; i++) {
		printf("=");
	} printf("\n");
}

void DisplayFrequencyTable() {
    printf("Class Limits:\n");
    for (int i = 0; i < CLASS_WIDTH + 1; i++) {
        printf("%i-%i\n", LOWER_LIMITS[i], UPPER_LIMITS[i]);
    }
}