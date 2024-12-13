#include <stdio.h>

int main() {
	int input;
	input = getchar();

	if (input < 57 && input > 47) printf("input is digit\n");
	else printf("input is not digit\n");
	return 0;
}