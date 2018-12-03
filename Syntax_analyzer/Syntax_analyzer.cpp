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

int main()
{
	string str, buffer, actualToken, previousToken, actualTokenOfAction, previousTokenOfAction = ""; // "if(a + b * c > d );"
	stack<string> tokens;
	int previousPriority, actualPriority;
	map<char, int> tokensPriority = { 
		{'*',1}, 
		{'/',1},
		{'+',2},
		{'-',2},
		{ '<',3},
		{ '>',3},
		{')', 5}
	};
	map<char, int>::iterator it;
	
	

	//writeToFile(str);
	//readFromFile(str);
	int count = 0;
	ifstream fin("synt.txt");
	while (getline(fin, str)){
		for (int i = 0; i < str.length(); i++) {
			bool pairsToAction = /*!actualToken.empty() &&*/
				!actualTokenOfAction.empty() &&
				!previousToken.empty() &&
				!previousTokenOfAction.empty();
			bool twopairs = actualToken.empty() &&
				actualTokenOfAction.empty() &&
				previousToken.empty() &&
				previousTokenOfAction.empty();
			/*if (!tokens.empty() &&  twopairs)
			{
				previousToken = tokens.top();
				tokens.pop();
				previousTokenOfAction = tok
				
			}*/
			if (actualToken.empty() || actualTokenOfAction.empty()) {
				if (str[i] == ')')
					count++;
				while (isalpha(str[i])) {
					actualToken += str[i];
					i++;
				}
				while (str[i] != ';' && ispunct(str[i])) {
					actualTokenOfAction += str[i];
					actualPriority = tokensPriority.find(str[i])->second;
					i++;
				}
				
				if (count != 0)
					i-=2;
				
			}
			else if (pairsToAction)
			{
				if (previousPriority > actualPriority)
				{
					tokens.push(previousToken); 
					tokens.push(previousTokenOfAction);
					previousToken = actualToken;
					actualToken.erase();
					previousTokenOfAction = actualTokenOfAction;
					actualTokenOfAction.erase();
					i--;
				}
				else
				{
					buffer = previousToken + previousTokenOfAction + actualToken;
					cout << buffer << endl;
					//tokens.push(actualTokenOfAction);
					if (!tokens.empty()) {
						previousTokenOfAction = tokens.top();
						tokens.pop();
						previousToken = tokens.top();
						tokens.pop();
						actualToken = buffer;
					}
					else
					{
						actualToken = buffer;
						/*tokens.push(actualToken);
						actualToken.erase();
						tokens.push(actualTokenOfAction);
						actualTokenOfAction.erase();*/
						previousToken.erase();
						previousTokenOfAction.erase();

					}
					

					i--;
					
					
					//i--;
				}
				
			}
			else if (!actualToken.empty() && !actualTokenOfAction.empty()) {
				previousToken = actualToken;
				actualToken.erase();
				previousTokenOfAction = actualTokenOfAction;
				previousPriority = actualPriority;
				actualTokenOfAction.erase();
				i--;
			}
			
		}
	}
	fin.close();

}

