#include "xlsxwriter.h"

int CLASS_WIDTH = 5;

int main() {
	lwx_workbook* workbook = workbook_new("test.xlsx");
	lwx_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);

	for (int i = 0; i < CLASS_WIDTH; i++) {
		for (int d = 0; d < i; d++);
	}	
}