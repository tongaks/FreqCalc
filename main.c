#include "headers/functions.h"

int main() {
	int condition = DisplayMainMenu();
	switch (condition) {
	case 1:
		break;
	case 2:
		LoadSavedData();
		break;
	case 3:
		return 0;
	default:
		main();
		break;
	}

	if (CheckTempFile() == false) return 0;
	if (AskLoadPreviousData()) GetClassDatas();
	GetPopulationOrder();
	GetClassInterval();
	GetClassLimits();
	GetFrequencies();
	GetCommulativeFrequencies();
	GetClassBoundariesAndClassMarks();
	GetMeanValue();
	GetStandardDeviation();
	GetVarianceValue();

	DisplayInterval();
	DisplayTable();

	GetFileName();
	ClearArrayAndVariables();
	main();
	return 0;
}