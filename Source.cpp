#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <clocale>
#include <Windows.h>

using namespace std;

void start();

int main() {

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(0));

	start();
	return 0;
}


