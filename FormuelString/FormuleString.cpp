#include "FormuleString.h"


double FormuleString::polynomialCalcule(string formule, double x)
{
	partitionFormule(formule);
	
	double retour = 0;
	string valeur1;
	string valeur2;
	string operation;

	try
	{
		//la premiere valeur doit etre une valeur numerique ou une variable
		if (metaDonneFormule[0] == etatMetaDonne::nombre)
		{
			retour = stof(partitionsFormule[0]);
		}
		else if (metaDonneFormule[0] == etatMetaDonne::variableX)
		{
			retour = x;
		}
		else
		{
			cout << "ERREUR : LA VALEUR INITIALE N'EST PAS UNE VALEUR NUMÉRIQUE OU UNE VARIABLE" << endl;
			return 0;
		}

		for (int i = 0; i < longueurPartitions; i += 3)
		{
			if (metaDonneFormule[i + 1] == etatMetaDonne::operation)
			{
				if (metaDonneFormule[i] == etatMetaDonne::variableX)
				{
					valeur1 = to_string(x);
				}
				else if (metaDonneFormule[i] == etatMetaDonne::nombre)
				{
					valeur1 = partitionsFormule[i];
				}

				if (metaDonneFormule[i + 2] == etatMetaDonne::variableX)
				{
					valeur2 = to_string(x);
				}
				else if (metaDonneFormule[i + 2] == etatMetaDonne::nombre)
				{
					valeur2 = partitionsFormule[i];
				}

				cout << valeur1 << endl;
				cout << partitionsFormule[i + 1] << endl;
				cout << valeur2 << endl;
				retour = partitionCalcule(valeur1, partitionsFormule[i + 1], valeur2);
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "ERREUR : FORMULE N'EST PAS BIEN ÉCRITE" << endl;
	}

	return retour;
}

double FormuleString::partitionCalcule(string valeur1, string operation, string valeur2)
{
	if (operation == "+")
	{
		return stod(valeur1) + stod(valeur2);
	}
	else if (operation == "-")
	{
		return stod(valeur1) - stod(valeur2);
	}
}

void FormuleString::partitionFormule(string formule)
{
	string nombre;
	string operation;
	int index = 0;
	int longueur = formule.length();
	int i = 0;

	while (i < longueur)
	{
		if (isdigit(formule[i]))
		{
			//pour les nombres
			while (isdigit(formule[i]) && i < longueur)
			{
				nombre += formule[i];
				i++;
			}

			partitionsFormule.push_back(nombre);
			metaDonneFormule.push_back(etatMetaDonne::nombre);
			nombre = "";
			index++;
		}
		else if (toupper(formule[i]) != 'X')
		{
			//pour l'operation
			while (toupper(formule[i]) != 'X' && !isdigit(formule[i]) && i < longueur)
			{
				operation += formule[i];
				i++;
			}

			partitionsFormule.push_back(operation);
			metaDonneFormule.push_back(etatMetaDonne::operation);
			operation = "";
			index++;
		}
		else
		{
			//pour les variable(x)
			partitionsFormule.push_back("X");
			metaDonneFormule.push_back(etatMetaDonne::variableX);
			i++;
			index++;
		}

	}

	longueurPartitions = index;
}
