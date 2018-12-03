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
						buffer = previousToken + previousTokenOfAction + actualToken; //формування виконання дій, якщо операція не перевищує по пріоритету дану
						cout << buffer << endl; //Виведення поточної дії
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
							previousToken.erase(); //якщо стек пустий потрібно очистити попередні лексеми
							previousTokenOfAction.erase();
							i++;
							return;
							 //для зберігання виконаних дій 
							

						}
						
					}

					else
					{
						//else if (str[i] == ')')
						//{
						//	buffer = previousToken + previousTokenOfAction + actualToken; //формування виконання дій, якщо операція не перевищує по пріоритету дану
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
			else if (pairsToAction) { //Якщо є три необхідних лексеми для порівняння
				if (previousPriority > actualPriority) { //Порівняння пріоритетів
					tokens.push(previousToken); //Якщо перевищує, то закинути у стек попередні лексеми 
					tokens.push(previousTokenOfAction); //--++---
					previousToken = actualToken; //На місце попередніх переміщуються ті, які були активними
					actualToken.erase(); //--++---
					previousTokenOfAction = actualTokenOfAction; //заміна активних лексем дії
					actualTokenOfAction.erase(); //очистка актуальних
					previousPriority = actualPriority; //оновлення пріоритету для попередніх лексем
					actualPriority = NULL; //очистка пріоритету для актуальних
					i--; // для того, заміна лексем не забирала ітерацію пошуку 
				}
				else {
					buffer = previousToken + previousTokenOfAction + actualToken; //формування виконання дій, якщо операція не перевищує по пріоритету дану
					cout << buffer << endl; //Виведення поточної дії
					if (!tokens.empty()) {
						previousTokenOfAction = tokens.top();
						previousPriority = tokensPriority.find(previousTokenOfAction[0])->second;
						tokens.pop();
						previousToken = tokens.top();
						tokens.pop();
						actualToken = buffer;
					}
					else {
						actualToken = buffer; //для зберігання виконаних дій 
						previousToken.erase(); //якщо стек пустий потрібно очистити попередні лексеми
						previousTokenOfAction.erase();

					}
					i--;
				}
			}
			else if (!actualToken.empty() && !actualTokenOfAction.empty()) { //запис актуальних лексем у попередні для вивільнення 
							//місця новим актуальним лексемам
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
			//else if (pairsToAction) { //Якщо є три необхідних лексеми для порівняння
			//	if (previousPriority > actualPriority) { //Порівняння пріоритетів
			//		tokens.push(previousToken); //Якщо перевищує, то закинути у стек попередні лексеми 
			//		tokens.push(previousTokenOfAction); //--++---
			//		previousToken = actualToken; //На місце попередніх переміщуються ті, які були активними
			//		actualToken.erase(); //--++---
			//		previousTokenOfAction = actualTokenOfAction; //заміна активних лексем дії
			//		actualTokenOfAction.erase(); //очистка актуальних
			//		previousPriority = actualPriority; //оновлення пріоритету для попередніх лексем
			//		actualPriority = NULL; //очистка пріоритету для актуальних
			//		i--; // для того, заміна лексем не забирала ітерацію пошуку 
			//	}
			//	else {
			//		buffer = previousToken + previousTokenOfAction + actualToken; //формування виконання дій, якщо операція не перевищує по пріоритету дану
			//		cout << buffer << endl; //Виведення поточної дії
			//		if (!tokens.empty()) {
			//			previousTokenOfAction = tokens.top();
			//			previousPriority = tokensPriority.find(previousTokenOfAction[0])->second;
			//			tokens.pop();
			//			previousToken = tokens.top();
			//			tokens.pop();
			//			actualToken = buffer;
			//		}
			//		else {
			//			actualToken = buffer; //для зберігання виконаних дій 
			//			previousToken.erase(); //якщо стек пустий потрібно очистити попередні лексеми
			//			previousTokenOfAction.erase();

			//		}
			//		i--;
			//	}
			//}
			//else if (!actualToken.empty() && !actualTokenOfAction.empty()) { //запис актуальних лексем у попередні для вивільнення 
			//				//місця новим актуальним лексемам
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

