#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>;
#include <ctype.h>
#include <map>

using namespace std;

void writeToFile(string input)
{
	ofstream fout;
	fout.open("synt.txt");
	fout << input;
	fout.close();
}

//void readFromFile(string output)
//{
//	
//}
string str, buffer, actualToken, previousToken, actualTokenOfAction, previousTokenOfAction = ""; // "if(a + b * c > d );"

int previousPriority, actualPriority;
map<char, int> tokensPriority = {
	{'*',1},
	{'/',1},
	{'%',1},
	{'+',2},
	{'-',2},
	{ '<',3},
	{ '>',3},
	{ '<=',3},
	{ '>=',3},
	{ '==',4},
	{ '!=',4},
	{'&&', 5},
	{'||', 6}
	//{')', 7},
	//{'(', 7}

};
map<char, int>::iterator it;

int count = 0;

void syntAnalyzer(string str, int &i)
{
	stack<string> tokens;
	string  /*actualToken,*/ previousToken,/*, actualTokenOfAction,*/ previousTokenOfAction = "";
	if (str[i] == '(')
	{
		i++;
		for ( i = i; i < str.length(); i++) {
		
		
			
			bool pairsToAction =
				!actualTokenOfAction.empty() &&
				!previousToken.empty() &&
				!previousTokenOfAction.empty();

			if (actualToken.empty() || actualTokenOfAction.empty()) {
				
				while (isalpha(str[i])) {
					actualToken += str[i];
					i++;
				}
				while (str[i] != ';' && ispunct(str[i])) {
					if (str[i] == '(')
						syntAnalyzer(str, i);
					else if (str[i] == ')')
					{
						buffer = previousToken + previousTokenOfAction + actualToken; //���������� ��������� ��, ���� �������� �� �������� �� ��������� ����
						cout << buffer << endl; //��������� ������� 䳿
						if (!tokens.empty()) {
							previousTokenOfAction = tokens.top();
							previousPriority = tokensPriority.find(previousTokenOfAction[0])->second;
							tokens.pop();
							previousToken = tokens.top();
							tokens.pop();
							actualToken = buffer;
						}
						else {
							actualToken = buffer;
							previousToken.erase(); //���� ���� ������ ������� �������� �������� �������
							previousTokenOfAction.erase();
							i++;
							return;
							 //��� ��������� ��������� �� 
							

						}
						
					}

					else
					{
						//else if (str[i] == ')')
						//{
						//	buffer = previousToken + previousTokenOfAction + actualToken; //���������� ��������� ��, ���� �������� �� �������� �� ��������� ����
						//	cout << buffer << endl;
						//	if(tokens.empty())
						//		return;
						//}
						actualTokenOfAction += str[i];
						actualPriority = tokensPriority.find(str[i])->second;
						i++;
					}
				}

				//if (count != 0)
				//	i -= 2;
				if (str[i] != ' ')
				{
					i--;
				}
			}
			else if (pairsToAction) { //���� � ��� ���������� ������� ��� ���������
				if (previousPriority > actualPriority) { //��������� ���������
					tokens.push(previousToken); //���� ��������, �� �������� � ���� �������� ������� 
					tokens.push(previousTokenOfAction); //--++---
					previousToken = actualToken; //�� ���� ��������� ������������ �, �� ���� ���������
					actualToken.erase(); //--++---
					previousTokenOfAction = actualTokenOfAction; //����� �������� ������ 䳿
					actualTokenOfAction.erase(); //������� ����������
					previousPriority = actualPriority; //��������� ��������� ��� ��������� ������
					actualPriority = NULL; //������� ��������� ��� ����������
					i--; // ��� ����, ����� ������ �� �������� �������� ������ 
				}
				else {
					buffer = previousToken + previousTokenOfAction + actualToken; //���������� ��������� ��, ���� �������� �� �������� �� ��������� ����
					cout << buffer << endl; //��������� ������� 䳿
					if (!tokens.empty()) {
						previousTokenOfAction = tokens.top();
						previousPriority = tokensPriority.find(previousTokenOfAction[0])->second;
						tokens.pop();
						previousToken = tokens.top();
						tokens.pop();
						actualToken = buffer;
					}
					else {
						actualToken = buffer; //��� ��������� ��������� �� 
						previousToken.erase(); //���� ���� ������ ������� �������� �������� �������
						previousTokenOfAction.erase();

					}
					i--;
				}
			}
			else if (!actualToken.empty() && !actualTokenOfAction.empty()) { //����� ���������� ������ � �������� ��� ���������� 
							//���� ����� ���������� ��������
				previousToken = actualToken;
				actualToken.erase();
				previousTokenOfAction = actualTokenOfAction;
				previousPriority = actualPriority;
				actualTokenOfAction.erase();
				actualPriority = NULL;
				i--;
			}
		}
		
	}
	else if (str[i] == ')')
	{
		
		return;
	}
	actualToken.erase();
}

int main()
{
	//writeToFile(str);
	//readFromFile(str);
	//string str, buffer, actualToken, previousToken, actualTokenOfAction, previousTokenOfAction = ""; // "if(a + b * c > d );"
	//stack<string> tokens;
	//int previousPriority, actualPriority;
	//map<char, int> tokensPriority = {
	//	{'*',1},
	//	{'/',1},
	//	{'%',1},
	//	{'+',2},
	//	{'-',2},
	//	{ '<',3},
	//	{ '>',3},
	//	{ '<=',3},
	//	{ '>=',3},
	//	{ '==',4},
	//	{ '!=',4},
	//	{'&&', 5},
	//	{'||', 6},
	//	{')', 7},
	//	{'(', 7},

	//};
	//map<char, int>::iterator it;
	//
	//int count = 0;
	ifstream fin("synt.txt");

	while (getline(fin, str)) {
		int i = 0;
		actualToken.erase();
		syntAnalyzer(str, i);
		//for (int i = 0; i < str.length(); i++) {
			//bool pairsToAction =
			//	!actualTokenOfAction.empty() &&
			//	!previousToken.empty() &&
			//	!previousTokenOfAction.empty();
		
			//if (actualToken.empty() || actualTokenOfAction.empty()) {
			//	/*if (str[i] == ')')
			//		count++;*/
			//	while (isalpha(str[i])) {
			//		actualToken += str[i];
			//		i++;
			//	}
			//	while (str[i] != ';' && ispunct(str[i])) {
			//		actualTokenOfAction += str[i];
			//		actualPriority = tokensPriority.find(str[i])->second;
			//		i++;
			//	}
			//	
			//	//if (count != 0)
			//	//	i -= 2;
			//	if (str[i] != ' ')
			//	{
			//		i--;
			//	}
			//}
			//else if (pairsToAction) { //���� � ��� ���������� ������� ��� ���������
			//	if (previousPriority > actualPriority) { //��������� ���������
			//		tokens.push(previousToken); //���� ��������, �� �������� � ���� �������� ������� 
			//		tokens.push(previousTokenOfAction); //--++---
			//		previousToken = actualToken; //�� ���� ��������� ������������ �, �� ���� ���������
			//		actualToken.erase(); //--++---
			//		previousTokenOfAction = actualTokenOfAction; //����� �������� ������ 䳿
			//		actualTokenOfAction.erase(); //������� ����������
			//		previousPriority = actualPriority; //��������� ��������� ��� ��������� ������
			//		actualPriority = NULL; //������� ��������� ��� ����������
			//		i--; // ��� ����, ����� ������ �� �������� �������� ������ 
			//	}
			//	else {
			//		buffer = previousToken + previousTokenOfAction + actualToken; //���������� ��������� ��, ���� �������� �� �������� �� ��������� ����
			//		cout << buffer << endl; //��������� ������� 䳿
			//		if (!tokens.empty()) {
			//			previousTokenOfAction = tokens.top();
			//			previousPriority = tokensPriority.find(previousTokenOfAction[0])->second;
			//			tokens.pop();
			//			previousToken = tokens.top();
			//			tokens.pop();
			//			actualToken = buffer;
			//		}
			//		else {
			//			actualToken = buffer; //��� ��������� ��������� �� 
			//			previousToken.erase(); //���� ���� ������ ������� �������� �������� �������
			//			previousTokenOfAction.erase();

			//		}
			//		i--;
			//	}
			//}
			//else if (!actualToken.empty() && !actualTokenOfAction.empty()) { //����� ���������� ������ � �������� ��� ���������� 
			//				//���� ����� ���������� ��������
			//	previousToken = actualToken;
			//	actualToken.erase();
			//	previousTokenOfAction = actualTokenOfAction;
			//	previousPriority = actualPriority;
			//	actualTokenOfAction.erase();
			//	actualPriority = NULL;
			//	i--;
			//}

		//}
		str, buffer, actualToken, previousToken, actualTokenOfAction, previousTokenOfAction = "";
	}
	fin.close();

}

