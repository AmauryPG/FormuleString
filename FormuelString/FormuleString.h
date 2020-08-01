#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FormuleString
{
public:
	double polynomialCalcule(string formule, double x);
private:
	vector<string> partitionsFormule;
	vector<int> metaDonneFormule;
	int longueurPartitions;

	enum etatMetaDonne
	{
		nombre = 0,
		operation = 1,
		variableX = 3
	};

	//
	//cette fonction change partitionsFormule et metaDonneFormule
	void partitionFormule(string formule);
	double partitionCalcule(string valeur1, string operation, string valeur2);
};

