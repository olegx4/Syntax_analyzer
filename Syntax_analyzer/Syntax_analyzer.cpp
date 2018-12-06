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

string str, buffer, actualToken, previousToken, actualTokenOfAction, previousTokenOfAction = "";
stack<string> tokens;
int previousPriority, actualPriority;
map<string, int> tokensPriority = {
	{"*",1},
	{"/",1},
	{"%",1},
	{"+",2},
	{"-",2},
	{"<",3},
	{">",3},
	{"<=",3},
	{">=",3},
	{"==",4},
	{"!=",4},
	{"&&", 5},
	{"||", 6}
};

void parser(string str, int &i)
{
	//stack<string> tokens;

	string   previousToken, previousTokenOfAction = "";
	if (str[i] != '(')
	{
		i = str.find('(');
		i++;
	}
	else
		i++;
	for (i = i; i < str.length(); i++) {
		bool pairsToAction =
			!actualTokenOfAction.empty() &&
			!previousToken.empty() &&
			!previousTokenOfAction.empty();
		bool theEnd = str[i] == ')' &&
			!previousTokenOfAction.empty() &&
			!previousToken.empty() &&
			!actualToken.empty();
		if (str[i] == '(' && !pairsToAction)
		{
			if (!previousToken.empty() && !previousTokenOfAction.empty())
			{
				tokens.push(previousToken);
				tokens.push(previousTokenOfAction);
			}
			else
			{
				tokens.push(actualToken);
				tokens.push(actualTokenOfAction);
				previousToken = actualToken;
				actualToken.erase();
				previousTokenOfAction = actualTokenOfAction;
				actualTokenOfAction.erase();
				previousPriority = actualPriority;
				actualPriority = NULL;
			}
			tokens.push("(");


			parser(str, i);
		}
		if ((actualToken.empty() || actualTokenOfAction.empty()) && !theEnd) {
			while (isalnum(str[i])) {
				actualToken += str[i];
				i++;
			}
			while (str[i] != ')' && str[i] != '('  && ispunct(str[i])) {
				actualTokenOfAction += str[i];
				i++;
			}
			if (!actualTokenOfAction.empty())
				actualPriority = tokensPriority.find(actualTokenOfAction)->second;
			if (str[i] != ' ')
			{
				i--;
			}

		}
		else if (pairsToAction || theEnd) {
			if (pairsToAction)
			{
				previousPriority = tokensPriority.find(previousTokenOfAction)->second;
				actualPriority = tokensPriority.find(actualTokenOfAction)->second;
			}
			if (str[i] == ')' || (previousPriority <= actualPriority))
			{
				buffer = previousToken + previousTokenOfAction + actualToken;
				cout << buffer << endl;
				actualToken = buffer;
				if (!tokens.empty() && tokens.top() == "(")
				{
					tokens.pop();
					tokens.pop();
					tokens.pop();
					i++;
					return;
				}
				else if (!tokens.empty()) {
					previousTokenOfAction = tokens.top();
					previousPriority = tokensPriority.find(previousTokenOfAction)->second;
					tokens.pop();
					previousToken = tokens.top();
					tokens.pop();
				}
				else {

					previousToken.erase();
					previousTokenOfAction.erase();
					if (str[i] == ')')
						return;
				}
				i--;
			}
			else if (previousPriority > actualPriority) {
				tokens.push(previousToken);
				tokens.push(previousTokenOfAction);
				previousToken = actualToken;
				actualToken.erase();
				previousTokenOfAction = actualTokenOfAction;
				actualTokenOfAction.erase();
				previousPriority = actualPriority;
				actualPriority = NULL;
				i--;
			}

		}
		else if (!actualToken.empty() && !actualTokenOfAction.empty()) {
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

void main()
{



	ifstream fin("synt.txt");
	while (getline(fin, str)) {
		actualToken.erase();
		actualTokenOfAction.erase();
		int i = 0;
		parser(str, i);
	}
	fin.close();

}