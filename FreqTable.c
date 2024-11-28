#include "functions.h"

int populationSize = 0;
int classInterval = 0;
int populationOrder = 0;
int interval_k = 0;

int minValueGlobal = 0;
int maxValueGlobal = 0;

void classContents();
double getClassInterval();
void displayClassLimits();

int main(){
    printf("Insert Population Size: ");
    scanf("%i", &populationSize);

    int classSet[populationSize];

    classContents(classSet);

    classInterval = getClassInterval(classSet);
    printf("Class Interval: [%d]", classInterval);

    printf("\n\nSelection:\n   [Descending Order - '0']   [Ascending Order - '1']\n\n");
    do{
        printf("Select Population Order: ");
        scanf("%d", &populationOrder);
    } while(populationOrder < 0 || populationOrder > 1);

    displayClassLimits();

    return 0;
}

void displayClassLimits() {
    int UpperBound, LowerBound;
    int UpperBoundaries[interval_k + 1];
    int LowerBoundaries[interval_k + 1];

    int iterator = 0;
    for (int i = maxValueGlobal; i >= interval_k;) {
        LowerBound = i - (classInterval - 1);     
        UpperBound = i;

        UpperBoundaries[iterator] = UpperBound;
        LowerBoundaries[iterator] = LowerBound;

        i -= 10;
        iterator++;
    }

    if (populationOrder == 0) {
        for (int i = 0; i < interval_k + 1; i++) { // Descending
            printf("%i - %i\n", LowerBoundaries[i], UpperBoundaries[i]);
        }        
    } else if (populationOrder == 1) {
        for (int i = interval_k; i >= 0; i--) { // ascending
            printf("%i - %i\n", LowerBoundaries[i], UpperBoundaries[i]);
        }        
    }
}

void classContents(int* classSet){
    putchar('\n');
    for(int i = 0; i < populationSize; i++){
        printf("Insert Class Content #%d: ", i + 1);
        scanf("%d", &classSet[i]);

    } printf("\n\n");
}

double getClassInterval(int* classSet){
    int minimumValue = classSet[0];     //for saving the lowest value within classSet[]
    int maximumValue = classSet[0];     //for saving the highest value within classSet[]
    double classRange = 0;              //class range = higest value - lowest value
    double k = 0;                       // value of k, also used for CI later

    //loops for populationSize times
    //two conditions to find the lowest and highest values within classSet[]
    for(int i = 0; i < populationSize; i++){
        if(maximumValue < classSet[i]) maximumValue = classSet[i];
        if(classSet[i] < minimumValue) minimumValue = classSet[i];

    }

    //Saves the lowest and highest values in a separate global variable
    minValueGlobal = minimumValue;
    maxValueGlobal = maximumValue;

    //displays class range, minimum, and maximum value
    classRange = (double)maximumValue - minimumValue;
    printf(" Maximum Value: [%d]\n", maximumValue);
    printf(" Minimum Value: [%d]\n", minimumValue);
    printf("    ClassRange: [%.0lf]\n", classRange);

    //calculates and prints k
    k = 1.0 + (3.3 * (log10(populationSize)));
    printf("             k: [%.2lf]\n", k);

    //gets class interval by dividing the class range by k
    //result is then re-assigned in the same variable k
    interval_k = round(k);
    k = (classRange / k);

    return round(k);
}