#include <iostream>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"

using namespace std;

int main() {
	int x = 15;
	int y = 5;
	cout << "x + y = " << add(x, y) << endl;
	cout << "x - y = " << sub(x, y) << endl;
	cout << "x * y = " << mul(x, y) << endl;
	cout << "x / y = " << div(x, y) << endl;
	return 0;
}
