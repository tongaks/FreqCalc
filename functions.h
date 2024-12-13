#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
bool CheckTempFile();
void GetFileName();
void CreateFile();
bool LoadPreviousData();
void GetPreviousDataCount();
bool AskLoadPreviousData();
void LoadSavedData();
