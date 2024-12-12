#include "test.h"

int main() {
    int res = MainMenu();
    if (res == 3) return 0;
    DisplayData();
    
    res = AskLoadPrevData();
    GetPopSize();
    GetData();
    GetOrder();

	return 0;
}