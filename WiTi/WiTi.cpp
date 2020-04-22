#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

bool sortcol(const vector<int>& v1, const vector<int>& v2) {
	return v1[3] < v2[3];
}
void sortD(Dane& dane, vector<int>& permutacja)
{
	Dane backup = dane;
	sort((dane.zadania).begin(), (dane.zadania).end(), sortcol);
	for (int unsigned i = 0; i < permutacja.size();i++)
	{
		permutacja[i] = dane.zadania[i][0];
	}
	dane = backup;
}

int obliczKare(vector<int> permutacja, Dane dane)
{
	int czas = 0; 
	int kara = 0;
	vector<int> spoznienia(permutacja.size());
	//uzupelniamy wektor spoznien dla kazdego zadania
	for (int i = 0;i < permutacja.size();i++)
	{
		czas += dane.zadania[permutacja[i]][1];
		if (dane.zadania[permutacja[i]][3] < czas)
		{
			spoznienia[i] = czas - dane.zadania[permutacja[i]][3];
		}
	}
	//kara jest rowna sumie spoznien pomnozonych przez wagi
	for (int i = 0;i < permutacja.size();i++)
	{
		kara += (spoznienia[i] * dane.zadania[permutacja[i]][2]);
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

void generujPermutacjeRekursywnie(int k, vector<int> zadania, Dane dane, int &minKara, vector<int> &optymalnaPermutacja)
{
	if (k == 1)
	{
		int karaDlaPermutacji = obliczKare(zadania, dane);
			if (karaDlaPermutacji < minKara)
			{
				minKara = karaDlaPermutacji;
				optymalnaPermutacja = zadania;
			}
	}
	else
	{
		generujPermutacjeRekursywnie(k - 1, zadania, dane, minKara, optymalnaPermutacja);
		for (int i = 0; i < k - 1;i++)
		{
			if (k % 2 == 0)
			{
				swap(zadania[i], zadania[k - 1]);
			}
			else
			{
				swap(zadania[0], zadania[k - 1]);
			}
			generujPermutacjeRekursywnie(k - 1, zadania, dane, minKara, optymalnaPermutacja);
		}
	}
}

vector<int> przegladZupelnyRekursywnie(Dane dane)
{
	vector<int> permutacja;
	for (int i = 0; i < dane.ilezadan;i++)
	{
		permutacja.push_back(i);
	}
	int minKara = obliczKare(permutacja, dane);
	vector<int> idealnapermutacja = permutacja;

	generujPermutacjeRekursywnie(permutacja.size(), permutacja, dane, minKara, idealnapermutacja);
	return idealnapermutacja;
}
	
void generujPermutacjeIteracyjnie(vector<int> zadania, Dane dane, int& minKara, vector<int>& optymalnaPermutacja)
{
	int n = zadania.size();
	vector<int> c(n, 0);
	//sprawdzenie kary poczatkowej permutacji//
	int karaDlaPermutacji = obliczKare(zadania, dane);
	if (karaDlaPermutacji < minKara)
	{
		minKara = karaDlaPermutacji;
		optymalnaPermutacja = zadania;
	}
	//										//
	int i = 0;
	while (i < n)
	{
		if (c[i] < i)
		{
			if (i % 2 == 0)
			{
				swap(zadania[0], zadania[i]);
			}
			else
			{
				swap(zadania[c[i]], zadania[i]);
			}
			//sprawdzenie kary obecnej permutacji//
			karaDlaPermutacji = obliczKare(zadania, dane);
			if (karaDlaPermutacji < minKara)
			{
				minKara = karaDlaPermutacji;
				optymalnaPermutacja = zadania;
			}
			//									//
			c[i]++;
			i = 0;
		}
		else
		{
			c[i] = 0;
			i++;
		}
	}
}

vector<int> przegladZupelnyIteracyjnie(Dane dane)
{
	vector<int> permutacja;
	for (int i = 0; i < dane.ilezadan;i++)
	{
		permutacja.push_back(i);
	}
	int minKara = obliczKare(permutacja, dane);
	vector<int> idealnapermutacja = permutacja;

	generujPermutacjeIteracyjnie(permutacja, dane, minKara, idealnapermutacja);
	return idealnapermutacja;
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

	cout<<obliczKare(permutacja, dane)<<endl;
	//funkcja przez rekursywny przeglad zupelny ustawi permutacje w optymalny sposob
	vector<int> optymalnaPermutacja = przegladZupelnyIteracyjnie(dane);
	cout << obliczKare(optymalnaPermutacja,dane)<<endl;
	sortD(dane, permutacja);
	cout << obliczKare(permutacja, dane) << endl;


}

