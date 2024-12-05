#include <stdio.h>

int main() {
	// int number;
	// scanf("%i", &number);

	// char buffer[256];
	// sprintf(buffer, "%d", number);
	// printf("string: %s\n", buffer);

	// FILE* create_file;
	// create_file = fopen("sprintf.txt", "w");
	// fclose(create_file);

	// FILE* append_file;
	// append_file = fopen("sprintf.txt", "w");
	// // fputs(buffer, append_file);
	// fprintf(append_file, "%i\n", number);
	// fclose(append_file);

	FILE* shit = fopen("temp.txt", "w");
	fclose(shit);

	return 0;
}