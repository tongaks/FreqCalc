#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "xlsxwriter.h"

// ui related functions
int DisplayMainMenu();
void DisplayTable();
void DisplayClassSet();
void DisplayInterval();
void DisplayTable();

// computations
void GetMeanValue();
void GetStandardDeviation();
void GetSquaredDeviation();
void GetVarianceValue();
void GetFrequencies();
void GetClassBoundariesAndClassMarks();
void GetCommulativeFrequencies();
void GetPopulationSize();
void GetClassDatas();
void GetClassInterval();
void GetPopulationOrder();
void GetClassLimits();

int StringCount(const char* str);
void TUI(char* str);
void Warning(char* msg);
void ClearArrayAndVariables();
int InputValidation();

// file related functions
void CreateExcelFile(char* file_name, int class_width, int* lower_limits, int* upper_limits, 
                       int* frequencies, int* commulative_frequencies, float* class_marks, 
                       float* lower_boundaries, float* upper_boundaries);
void ClearTempFile();
bool CheckTempFile();
void GetFileName();
bool CreateFile();
bool LoadPreviousData();
void GetPreviousDataCount();
bool AskLoadPreviousData();
bool LoadSavedData();