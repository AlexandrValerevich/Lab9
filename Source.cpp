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
		try
		{
			while (str.at(i) == ' ' && ' ' == str.at(i + 1)) {
				str.erase(i, 1);
			}
		}
		catch (const std::out_of_range&)
		{
			return;
		}
	}
}
void DelSpaceInEnd(string& str) {
	if (str.empty()) { return; }

	int lastIndex = str.size() - 1;
	while (str.at(lastIndex) == ' ')
	{
		str.erase(lastIndex--);
	}
}

string GetString() {
	string str;

	cout << "Введите строку: ";
	getline(cin, str);

	DelSpaceInStart(str);
	DelDoubleSpace(str);
	DelSpaceInEnd(str);

	return str;
}

void InsertCommaBeforeAAndNo(string& str) {

	if (str.empty()) { return; }


	for (size_t i = 0; i < str.length(); i++)
	{
		try
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
		catch (const std::out_of_range&)
		{
			return;
		}
	}
}
string FindBiggestSubstr(string& str) {

	if (str.empty()) { return ""; }


	int sizeOfMaxSubstr       = 0;
	int firstPosBiggestSubstr = 0;
	char ch;

	auto it = str.begin();
	while (*it != ',') {
		it++;
		if (it == str.end()) {
			return "";
		}
		firstPosBiggestSubstr++;
	}


	for (size_t i=firstPosBiggestSubstr, j = firstPosBiggestSubstr + 1; j < str.size(); j++)
	{
		ch = str.at(j);
		if (ch == ',') {
			if (j - i > sizeOfMaxSubstr) {
				sizeOfMaxSubstr       = j - i - 2; //вычет двух запятых
				firstPosBiggestSubstr = i + 2; //с учетом вычета одного пробела и запятой	
			}
			i = j;
		}
	}

	string biggestSubstr = str.substr(firstPosBiggestSubstr, sizeOfMaxSubstr);
	DelSpaceInStart(biggestSubstr);

	return biggestSubstr;
}
string FindBiggestWord(const string& str ) {

	if (str.empty()) { return ""; }

	int sizeOfBiggestWorld     = 0;
	int startIndexBiggeseWorld = 0;

	string temp = str + " ";

	for (size_t i = 0, j = 0; j < temp.length(); j++)
	{
		if (temp.at(j) == ' ' ) {
			if (j - i > sizeOfBiggestWorld) {
				sizeOfBiggestWorld = j - i;
				startIndexBiggeseWorld = i;
			}
			i = j + 1;
		}
	}
	
	return str.substr(startIndexBiggeseWorld, sizeOfBiggestWorld);
	
}

int main() {

	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string str;

	str = GetString();
	
	InsertCommaBeforeAAndNo(str); //Вставка запятых перед А и Но

	cout << str << endl; //Вывод строки с запятыми

	string biggestSubstr = FindBiggestSubstr(str); //самая большая подстрока
	cout << "Самая большая подстрока: " << biggestSubstr << endl; 

	string biggestWordInSubstr = FindBiggestWord(biggestSubstr); //Самое большое слово в самой большой подстроке
	cout << "Самое большое слово в самой большой подстроке: " << biggestWordInSubstr << endl;

	return 0;
}