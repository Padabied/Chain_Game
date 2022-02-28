#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

struct message {
	const char* menu = "\n1 - ��������� ����\n2 - ���� ������\n3 - ������� ����\n4 - ����� �� ����";
	const char* rules = "\n��������� ������� �� ��������� 2 �����.\n���� ������ - ���������� ������ ����� �� ������, ������� � ������ ���� ���� ���� �����.\n���� �� ������� ������, �� ��������� �����, ����������� ����������� �� ������� ���������� �����.\n�� ����� ���� ������� 4, ����� �����\n�� ����� ���� ������� 5, ����� �������� �����.\n";
	const char* goodbye = "Good bye !\n";
};

void printMessage(const char* message);
int singleGame();
void multiplayer();
char* getRandomWord();
bool isChecked(char* s1, char* s2);   
bool isWord(char* str); 
bool isInVocabulary(char* str); 
bool checkWin(char* str, char* win); 


void start() {

	message* mes = new message;
	int responce = 0;

    printMessage(mes->menu);
    scanf("%d", &responce);

	while (responce < 1 || responce > 4) {
		printMessage(mes->menu);
		scanf("%d", &responce);
	}

			switch (responce) {
			case 1: singleGame(); break;
			case 2: multiplayer(); break;
			case 3: printMessage(mes->rules);
				    start(); break;
			case 4: printMessage(mes->goodbye); exit(0);
			}

			while (true) {
				printf("������� ������� ��� ���?\n1 - ��\n2 - ���\n");
				scanf("%d", &responce);
				while (responce < 1 || responce > 2) scanf("%d", &responce);
				switch (responce) {
				case 1: start(); break;
				case 2: 
					cout << mes->goodbye; exit(0);
				}
			}
		}

void printMessage(const char* message) {
	cout << message << endl << endl;
}

char* getRandomWord() {
	FILE* words = fopen("words.txt", "rt");
	char* result = new char[5];

	int randomInt = rand() % 1868 + 1;
	for (int i = 0; i < randomInt; i++) {
		char* ignoredBuff = new char[255];
		fgets(ignoredBuff, 255, words);
	}

	fgets(result, 5, words);
	fclose(words);

	return result;
}

int singleGame() {
	message* mes = new message;
	int step = 0;
	char* firstWord = getRandomWord();
	char* secondWord = getRandomWord();

	char* response;
	char* prevWord = firstWord;

	printf("�������� �� %s - %s\n", firstWord, secondWord);
	
    while (true) {
		response = new char[255];
		printf("%s - ", prevWord);
		cin >> response;
		if (response[0] == '4') {
			return 0;
		}
		else if (response[0] == '5') return singleGame();

		if (!isWord(response)) {
			printf("%s �� �������� ������\n", response);
		}
		else if (!isChecked(prevWord, response)) {
			printf("�������� ���� ����� � ����� %s\n", prevWord);
		}
		else if (!isInVocabulary(response)) {
			printf("����� %s ��� � �������. �� ����� ������� ����������?\n1 - ��\n2 - ���\n", response);

			int resp;
			scanf("%d", &resp);
			while (resp < 1 || resp > 2) scanf("%d", &resp);

			switch (resp) {
			case 1: 
				prevWord = response;
				step++;
				break;
			case 2: break;
			}
        }
		else if (checkWin(response, secondWord)) {
			step++;
			printf("�����������! �� ���������� �� %d �����!\n", step);
			return step;
		}
		else {
			step++;
			prevWord = response;
		}
    }
	return step;
}

void multiplayer() {
	char* firstName = new char[255];
	char* secondName = new char[255];
	printf("����� �1, ������� ��� ���!\n");
	cin >> firstName;
	printf("����� �2, ������� ��� ���!\n");
	cin >> secondName;

	printf("����� %s!\n", firstName);
	int firstScore = singleGame();
	printf("����� %s!\n", secondName);
	int secondScore = singleGame();

	if (firstScore < secondScore) printf("������� %s, ������ %d ������!\n", firstName, firstScore);
	else if (secondScore < firstScore) printf("������� %s, ������ %d ������!\n", secondName, secondScore);
	else printf("�������� ������!\n");
}

//���������, �������� �� ������ �����- ������ � ����� ���������� ������
bool isChecked(char* s1, char* s2) {
	int changedCnt = 0;
	for (int i = 0; i < 4; i++) {
		if (s1[i] != s2[i]) changedCnt++;
	}

	if (changedCnt != 1) return false;

	return true;
}

//���������, �������� �� ������ ������ (������� ��������, ���� � ��)
bool isWord(char* str) {
	for (int i = 0; i < 4; i++) {
	    if ((int)str[i] < -64 || (int)str[i] > -1) return false;
	}
	return true;
}

//���������, ���� �� ����� � ���������
bool isInVocabulary(char* str ) {
	FILE* words = fopen("words.txt", "rt");
	while (!feof(words)) {
        bool in = true;
		char* wordFromFile = new char[255];
		fgets(wordFromFile, 255, words);
		for (int i = 0; i < 4; i++) {
			if (str[i] != wordFromFile[i]) {
				in = false;
				break;
			}
		}
		if (in) return true;
	}
	fclose(words);
    return false;
}

//���������, ���������� �� ����
bool checkWin(char* str, char* win) {
	for (int i = 0; i < 4; i++) {
		if (str[i] != win[i]) {
			return false;
		}
	}
    return true;
}

