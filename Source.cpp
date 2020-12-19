/*Дана строка слов. Сформируйте новую строку, вставив перед каждым из
слов «а» и «но» запятую. Определите самую короткую подстроку и
слово, с которого она начинается.*/

#include <iostream>
#include <string>
#include <clocale>
#include <iomanip>
#include <windows.h>


using namespace std;

void DelSpaceInStart(string& str) {

	if (str.empty()) { return; }

	std::string::iterator it = str.begin();
	while (*it == ' ')
	{
		str.erase(it);
	}
}

void DelDoubleSpace(string& str) {

	if (str.empty()) { return; }
	
	for (size_t i = 0; i < str.size(); i++)
	{
		while (str.at(i) == ' ' && ' ' == str.at(i+1) ) {
			str.erase(i, 1);
		}
	}
}

void InsertCommaBeforeAAndNo(string& str) {

	if (str.empty()) { return; }

	DelSpaceInStart(str);
	DelDoubleSpace(str);

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str.at(i) == ',') {
			while (str.at(++i) == ' ');
			continue;
		}
		if (str.at(i) == ' ') {
			if (str.substr(i + 1, 2) == "а " || str.substr(i + 1, 3) == "но ") {
				str.insert(i++, ",");
			}
		}
	}
}

string FindBiggestSubstr(string& str) {

	if (str.empty()) { return ""; }

	DelSpaceInStart(str);
	DelDoubleSpace(str);

	int sizeOfMaxSubstr       = 0;
	int firstPosBiggestSubstr = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		char ch = str.at(i);
		if (ch == ',') {
			for (size_t j = i + 1; j < str.size(); j++)
			{
				ch = str.at(j);
				if (ch == ',') {
					if (j - i > sizeOfMaxSubstr) {
						sizeOfMaxSubstr       = j - i - 1; 
						firstPosBiggestSubstr = i + 1;
						break;
					}
				}
			}
		}
	}

	string biggestSubstr = str.substr(firstPosBiggestSubstr, sizeOfMaxSubstr);
	DelSpaceInStart(biggestSubstr);

	return biggestSubstr;
}

string FindBiggestWord(string& str) {

	if (str.empty()) { return ""; }

	DelSpaceInStart(str);
	DelDoubleSpace(str);

	int sizeOfBiggestWorld     = 0;
	int startIndexBiggeseWorld = 0;

	bool haveSpace = false;

	for (size_t i = 0; i < str.length(); i++)
	{
		for (size_t j = i; j < str.length(); j++)
		{
			if (str.at(i) == ' ') {
				haveSpace = true;
				if (sizeOfBiggestWorld <= j - i - 1) {
					sizeOfBiggestWorld     = j - i - 1;
					startIndexBiggeseWorld = i;
				}
				i = j + 1;
				break;
			}
		}
	}
	if (haveSpace) return str.substr(startIndexBiggeseWorld, sizeOfBiggestWorld);
	else           return str;
}

int main() {

	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string str;

	cout << "Введите строку: ";
	getline(cin ,str);
	
	InsertCommaBeforeAAndNo(str); //Вставка запятых перед А и Но

	cout << str << endl; //Вывод строки с запятыми

	string biggestSubstr = FindBiggestSubstr(str); //самая большая подстрока
	cout << "Самая большая подстрока: " << biggestSubstr << endl; 

	string biggestWordInSubstr = FindBiggestWord(biggestSubstr); //Самое большое слово в самой большой подстроке
	cout << "Самое большое слово в самой большой подстроке: " << biggestWordInSubstr << endl;

	return 0;
}