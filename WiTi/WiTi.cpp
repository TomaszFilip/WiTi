#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

class Dane {
public:
	int ilezadan;
	int ileparametrow;
	vector<vector<int>> zadania; //zapisane w postaci [ID][p(czas wykonywania)][w(waga)][d(oczekiwany czas dostarczenia)]
	Dane(int n, int m) {
		ilezadan = n;
		ileparametrow = m + 1; //odczytana+1(ID)
		zadania.resize(ilezadan, vector<int>(ileparametrow, 0));
	}
};

int obliczKare(vector<int> permutacja, Dane dane)
{
	int czas = 0; 
	int kara = 0;
	vector<int> spoznienia(permutacja.size());
	//uzupelniamy wektor spoznien dla kazdego zadania
	for (int i = 0;i < permutacja.size();i++)
	{
		czas += dane.zadania[i][1];
		if (dane.zadania[i][3] < czas)
		{
			spoznienia[i] = czas - dane.zadania[i][3];
		}
	}
	//kara jest rowna sumie spoznien pomnozonych przez wagi
	for (int i = 0;i < permutacja.size();i++)
	{
		kara += (spoznienia[i] * dane.zadania[i][2]);
	}
	return kara;
}

Dane wczytajDanezpliku(const char nazwa[], int &iz, int &ip)
{
	ifstream myfile(nazwa);
	if (myfile.is_open())
	{
		myfile >> iz;
		myfile >> ip;
	}
	Dane _dane(iz,ip);
	if (myfile.is_open())
	{
		for (int i = 0;i < _dane.ilezadan;i++)
		{
			_dane.zadania[i][0] = i;
			myfile >> _dane.zadania[i][1];
			myfile >> _dane.zadania[i][2];
			myfile >> _dane.zadania[i][3];
		}
		myfile.close();
	}
	return _dane;
}

void przegladZupelny(Dane dane)
{
	//TODO
	vector<int> minKaraPermutacja;
	vector<int> permutacja;
	for (int i = 0;i < dane.ilezadan;i++)
	{
		permutacja.push_back()
	}
}
	
		

int main()
{
	int ilezadan;
	int ileparametrow;
	//Wczytywanie danych
	char nazwapliku[100];
	cout << "Podaj nazwe pliku" << endl;
	cin >> nazwapliku;
	Dane dane = wczytajDanezpliku(nazwapliku,ilezadan,ileparametrow);
	//Permutacja naturalna
	vector<int> permutacja;
	for (int i = 0; i < dane.ilezadan;i++)
	{
		permutacja.push_back(i);
	}

	cout<<obliczKare(permutacja, dane);
}

