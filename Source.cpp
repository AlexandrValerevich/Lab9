/*���� ������ ����. ����������� ����� ������, ������� ����� ������ ��
���� �� � ��� �������. ���������� ����� �������� ��������� �
�����, � �������� ��� ����������.*/

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
			if (str.substr(i + 1, 2) == "� " || str.substr(i + 1, 3) == "�� ") {
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

	cout << "������� ������: ";
	getline(cin ,str);
	
	InsertCommaBeforeAAndNo(str); //������� ������� ����� � � ��

	cout << str << endl; //����� ������ � ��������

	string biggestSubstr = FindBiggestSubstr(str); //����� ������� ���������
	cout << "����� ������� ���������: " << biggestSubstr << endl; 

	string biggestWordInSubstr = FindBiggestWord(biggestSubstr); //����� ������� ����� � ����� ������� ���������
	cout << "����� ������� ����� � ����� ������� ���������: " << biggestWordInSubstr << endl;

	return 0;
}