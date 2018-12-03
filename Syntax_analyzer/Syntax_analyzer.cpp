#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void writeToFile(string input)
{
	ofstream fout;
	fout.open("synt.txt");
	fout << input;
	fout.close();
}

int main()
{
	string str = "if(a + b * c > d );";
	writeToFile(str);
}

