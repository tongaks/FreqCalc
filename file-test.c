#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int data_count = 0;
int popsize = 0;
int* dataset;


void CreateFile(int* arr, int dataset_size, char* filename) {
	FILE *file;

	char full_filename[256];
	strcpy(full_filename, filename);
	strcat(full_filename, ".txt");
	file = fopen(full_filename, "w");	
	
	fprintf(file, "data = ");
	for (int i = 0; i < dataset_size; i++) {
		if (i == dataset_size - 1) 
			fprintf(file, "%d", arr[i]);
		else fprintf(file, "%d, ", arr[i]);
	}  fprintf(file, "\n");

	fclose(file);
}


void ReadFromFile() {
	FILE* temp_file;
    temp_file = fopen("temp.txt", "r");
    if (temp_file == NULL) perror("[!] Failed to open temp file.\n");
    char buffer[5];

	dataset = (int*) malloc(popsize * sizeof(int));
    printf("Previous data count: %i\n", data_count);

    temp_file = fopen("temp.txt", "r");
	for (int i = 0; i < data_count; i++) {		// set the data to the array
    	if (fgets(buffer, 4, temp_file) != NULL) {
	    	dataset[i] = atoi(buffer);
    	} else printf("Invalid\n");
    } fclose(temp_file);

    for (int i = data_count; i < popsize; i++) {
    	printf("Enter data #%i: ", i+1);
    	scanf("%i", &dataset[i]);
    }

    for (int i = 0; i < popsize; i++) {
    	printf("%i, ", dataset[i]);
    } printf("\n");

}

int main() {
	// int dataset[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

	char choice[2];
	printf("Do you want to load the previous data set?: ");
	scanf("%1s", choice);


	if (strcmp("Y", choice) == 0 || strcmp("y", choice) == 0) {
		FILE* temp_file;
	    temp_file = fopen("temp.txt", "r");
	    if (temp_file == NULL) perror("[!] Failed to open temp file.\n");
	    char buffer[5];
	
		printf("Getting the previous number of data...\n");
	    while (true) {			// get the number of data previously inserted
    		if (fgets(buffer, 4, temp_file) != NULL) {
    			data_count += 1;
    		} else break;
    	} fclose(temp_file);

		printf("Enter the popsize: ");
		scanf("%i", &popsize);
	
		if (!(popsize < data_count)) ReadFromFile();
		else printf("[!] Popsize is less than the previous count.\n");
	} else printf("Exitting...\n");

	return 0;
}