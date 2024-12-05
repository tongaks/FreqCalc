#include "functions.h"

int main() {
	int condition = DisplayMainMenu();
	switch (condition) {
	case 1:
		break;
	case 2:
		LoadPreviousData();
		break;
	case 3:
		return 0;
	default:
		main();
		break;
	}

	CheckTempFile();
	AskLoadPreviousData();
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
	DisplayFrequencyTable();

	GetFileName();
	ClearArrayAndVariables();
	main();
	return 0;
}