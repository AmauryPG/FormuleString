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

		for (int i = 1; i < longueurPartitions - 1; i++)
		{
			if (metaDonneFormule[i] == etatMetaDonne::operation && 
				(metaDonneFormule[i + 1] == etatMetaDonne::nombre || metaDonneFormule[i + 1] == etatMetaDonne::variableX))
			{
				if (metaDonneFormule[i + 1] == etatMetaDonne::nombre)
				{
					retour = partitionCalcule(retour, partitionsFormule[i], partitionsFormule[i + 1]);
				}
				else
				{
					retour = partitionCalcule(retour, partitionsFormule[i], to_string(x));
				}
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "ERREUR : FORMULE N'EST PAS BIEN ECRITE" << endl;
	}

	return retour;
}

double FormuleString::partitionCalcule(double valeur1, string operation, string valeur2)
{
	if (operation == "+")
	{
		return valeur1 + stod(valeur2);
	}
	else if (operation == "-")
	{
		return valeur1 - stod(valeur2);
	}
	else if (operation == "*")
	{
		return valeur1 * stod(valeur2);
	}
	else if (operation == "/")
	{
		return valeur1 / stod(valeur2);
	}
	else if (operation == "^")
	{
		return pow(valeur1, stod(valeur2));
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
