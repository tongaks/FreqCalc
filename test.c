#include <stdio.h>

int main() {
	int UPPER_LIMITS[] = {10, 60, 40, 20, 30,};
	int LOWER_LIMITS[] = {6, 60, 40, 20, 30,};
	int FREQUENCIES[] = {5, 2, 4, 6, 6};
	int CLASS_MARK[] = {31, 33, 55, 13, 34,};

	printf("========================================================================\n");
	printf("\tClass Limit\tf\tClass Mark\tClass Boundaries\n");
	printf("========================================================================\n");

	for (int i = 0; i < 5; i++) {
		printf("\t [ %i-%i ]", LOWER_LIMITS[i], UPPER_LIMITS[i]);
		printf("\t [ %i ] ", FREQUENCIES[i]);
		printf("\t [ %i ]", CLASS_MARK[i]);
		printf("\t\t[ %i-%i ]\n", LOWER_LIMITS[i], UPPER_LIMITS[i]);
	}

	return 0;
}