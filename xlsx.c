#include "headers/xlsxwriter.h"

int CLASS_WIDTH = 5;

int UPPER_LIMIT[] = {50, 40 , 30, 20, 10};
int LOWER_LIMIT[] = {41, 31 , 21, 11, 1};
int UPPER_BOUNDARIES[] = {55, 42 , 35, 22, 11};
int LOWER_BOUNDARIES[] = {52, 46 , 60, 25, 13};
int FREQUENCIES[] = {2, 2, 2, 2, 2};
int COMMULATIVE_FREQUENCIES[] = {2, 4, 6, 8, 10};
int CLASS_MARKS[] = {23, 45, 45, 76, 56};

int main() {
	lxw_workbook* workbook = workbook_new("test.xlsx");
	lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
	
	lxw_format *centered_format = workbook_add_format(workbook);
    format_set_align(centered_format, LXW_ALIGN_CENTER);
	
    worksheet_merge_range(worksheet, 0, 0, 0, 1, "Class interval", centered_format);		// Class interval
    worksheet_write_string(worksheet, 0, 2, "f", centered_format);							// f
    worksheet_write_string(worksheet, 0, 3, "cf", centered_format);							// cf
    worksheet_write_string(worksheet, 0, 4, "Xm", centered_format);							// Xm
    worksheet_merge_range(worksheet, 0, 5, 0, 6, "Class boundaries", centered_format);		// Class boudarues

    worksheet_write_string(worksheet, 1, 0, "Lower", centered_format);
    worksheet_write_string(worksheet, 1, 1, "Upper", centered_format);

    worksheet_write_string(worksheet, 1, 5, "Lower", centered_format);
    worksheet_write_string(worksheet, 1, 6, "Upper", centered_format);

    for (int i = 0; i < CLASS_WIDTH; i++) {													// 	write upper &lower of class interval
		worksheet_write_number(worksheet, 2+i, 0, LOWER_LIMIT[i], centered_format);
		worksheet_write_number(worksheet, 2+i, 1, UPPER_LIMIT[i], centered_format);
    }

    for (int i = 0; i < CLASS_WIDTH; i++) {													// 	write f
		worksheet_write_number(worksheet, 2+i, 2, FREQUENCIES[i], centered_format);
    }

    for (int i = 0; i < CLASS_WIDTH; i++) {													// 	write f
		worksheet_write_number(worksheet, 2+i, 3, COMMULATIVE_FREQUENCIES[i], centered_format);
    }

    for (int i = 0; i < CLASS_WIDTH; i++) {													// 	write f
		worksheet_write_number(worksheet, 2+i, 4, CLASS_MARKS[i], centered_format);
    }

    for (int i = 0; i < CLASS_WIDTH; i++) {													// 	write upper &lower of class interval
		worksheet_write_number(worksheet, 2+i, 5, LOWER_BOUNDARIES[i], centered_format);
		worksheet_write_number(worksheet, 2+i, 6, UPPER_BOUNDARIES[i], centered_format);
    }

    workbook_close(workbook);
    return 0;
}