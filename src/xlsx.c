#include "../headers/functions.h"

void CreateExcelFile(char* file_name, int class_width, int* lower_limits, int* upper_limits, 
                       int* frequencies, int* commulative_frequencies, float* class_marks, 
                       float* lower_boundaries, float* upper_boundaries) {
    char full_file_name[100];
    sprintf(full_file_name, "%s.xlsx", file_name);

    lxw_workbook* workbook = workbook_new(full_file_name);
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
    
    lxw_format *centered_format = workbook_add_format(workbook);
    format_set_align(centered_format, LXW_ALIGN_CENTER);
    
    worksheet_merge_range(worksheet, 0, 0, 0, 1, "Class interval", centered_format);        // Class interval
    worksheet_write_string(worksheet, 0, 2, "f", centered_format);                            // f
    worksheet_write_string(worksheet, 0, 3, "cf", centered_format);                           // cf
    worksheet_write_string(worksheet, 0, 4, "Xm", centered_format);                           // Xm
    worksheet_merge_range(worksheet, 0, 5, 0, 6, "Class boundaries", centered_format);       // Class boundaries

    worksheet_write_string(worksheet, 1, 0, "Lower", centered_format);
    worksheet_write_string(worksheet, 1, 1, "Upper", centered_format);

    worksheet_write_string(worksheet, 1, 5, "Lower", centered_format);
    worksheet_write_string(worksheet, 1, 6, "Upper", centered_format);

    for (int i = 0; i < class_width + 1; i++) {                                                 // write upper & lower of class interval
        worksheet_write_number(worksheet, 2 + i, 0, lower_limits[i], centered_format);
        worksheet_write_number(worksheet, 2 + i, 1, upper_limits[i], centered_format);
    }

    for (int i = 0; i < class_width + 1; i++) {                                                 // write f
        worksheet_write_number(worksheet, 2 + i, 2, frequencies[i], centered_format);
    }

    for (int i = 0; i < class_width + 1; i++) {                                                 // write cf
        worksheet_write_number(worksheet, 2 + i, 3, commulative_frequencies[i], centered_format);
    }

    for (int i = 0; i < class_width + 1; i++) {                                                 // write Xm
        worksheet_write_number(worksheet, 2 + i, 4, class_marks[i], centered_format);
    }

    for (int i = 0; i < class_width + 1; i++) {                                                 // write upper & lower of class boundaries
        worksheet_write_number(worksheet, 2 + i, 5, lower_boundaries[i], centered_format);
        worksheet_write_number(worksheet, 2 + i, 6, upper_boundaries[i], centered_format);
    }

    workbook_close(workbook);
}
