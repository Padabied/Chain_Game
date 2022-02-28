#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

struct message {
	const char* menu = "\n1 - ОДИНОЧНАЯ ИГРА\n2 - ИГРА ВДВОЕМ\n3 - ПРАВИЛА ИГРЫ\n4 - ВЫХОД ИЗ ИГРЫ";
	const char* rules = "\nСлучайным образом Вы получаете 2 слова.\nВаша задача - превратить первое слово во второе, изменяя в каждом шаге лишь одну букву.\nЕсли вы играете вдвоем, то побеждает игрок, выполнивший превращение за меньшее количество ходов.\nВо время игры введите 4, чтобы выйти\nВо время игры введите 5, чтобы поменять слова.\n";
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
				printf("Желаете сыграть еще раз?\n1 - ДА\n2 - НЕТ\n");
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

	printf("Получить из %s - %s\n", firstWord, secondWord);
	
    while (true) {
		response = new char[255];
		printf("%s - ", prevWord);
		cin >> response;
		if (response[0] == '4') {
			return 0;
		}
		else if (response[0] == '5') return singleGame();

		if (!isWord(response)) {
			printf("%s не является словом\n", response);
		}
		else if (!isChecked(prevWord, response)) {
			printf("Измените одну букву в слове %s\n", prevWord);
		}
		else if (!isInVocabulary(response)) {
			printf("Слова %s нет в словаре. Всё равно желаете продолжить?\n1 - ДА\n2 - НЕТ\n", response);

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
			printf("Поздравляем! Вы справились за %d ходов!\n", step);
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
	printf("Игрок №1, введите своё имя!\n");
	cin >> firstName;
	printf("Игрок №2, введите своё имя!\n");
	cin >> secondName;

	printf("Ходит %s!\n", firstName);
	int firstScore = singleGame();
	printf("Ходит %s!\n", secondName);
	int secondScore = singleGame();

	if (firstScore < secondScore) printf("Победил %s, набрав %d баллов!\n", firstName, firstScore);
	else if (secondScore < firstScore) printf("Победил %s, набрав %d баллов!\n", secondName, secondScore);
	else printf("Победила дружба!\n");
}

//проверяет, является ли второе слово- первым с одной измененной буквой
bool isChecked(char* s1, char* s2) {
	int changedCnt = 0;
	for (int i = 0; i < 4; i++) {
		if (s1[i] != s2[i]) changedCnt++;
	}

	if (changedCnt != 1) return false;

	return true;
}

//проверяет, является ли строка словом (наличие символов, цифр и тд)
bool isWord(char* str) {
	for (int i = 0; i < 4; i++) {
	    if ((int)str[i] < -64 || (int)str[i] > -1) return false;
	}
	return true;
}

//проверяет, есть ли слово в документе
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

//проверяет, достигнута ли цель
bool checkWin(char* str, char* win) {
	for (int i = 0; i < 4; i++) {
		if (str[i] != win[i]) {
			return false;
		}
	}
    return true;
}

