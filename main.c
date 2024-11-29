#include "functions.h"

int main() {
	int condition = DisplayMainMenu();
	if (condition == 3) return 0;

	GetPopulationSize();
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
	return 0;
}