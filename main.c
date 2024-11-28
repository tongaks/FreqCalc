#include "functions.h"

int main() {
	int condition = DisplayMainMenu();
	if (condition == 3) return 0;

	GetPopulationSize();
	GetClassDatas();
	GetClassInterval();
	DisplayInterval();
	GetPopulationOrder();
	GetClassLimits();
	GetFrequencies();
	GetCommulativeFrequencies();
	GetClassBoundariesAndClassMarks();
	GetMeanValue();
	GetStandardDeviation();
	GetVarianceValue();

	DisplayFrequencyTable();
	return 0;
}