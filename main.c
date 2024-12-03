#include "functions.h"

int main() {
	int condition = DisplayMainMenu();
	if (condition == 3) return 0;

	AskLoadPreviousData();
	GetClassDatas();
	GetClassInterval();
	GetPopulationOrder();
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