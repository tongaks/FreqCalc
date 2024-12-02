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
void DisplayInterval();
void DisplayFrequencyTable();

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

int InputValidation();

// file related functions
void GetFileName();
void CreateFile();
void LoadPreviousData();
void GetPreviousDataCount();
void AskLoadPreviousData();
