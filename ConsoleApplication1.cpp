// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

// deklaracje, prototypy itp.

void stwciagrosnocy(int *x, int n);
void stwciagmalejacy(int *x, int n);
void stwciaglosowy(int *x, int n);
void stwciagstaly(int *x, int n);
void stwciagaksztaltny(int *x, int n);
void BuildHeap(int *x, int n, int m);   // kopiec
void HeapSort(int *x, int n);
void HeapIfy(int *x, int n, int m);
void inssort(int *x, int n);            // insertion sort
void shellsort(int *x, int n);          // shell sort
void selsort(int *x, int n);            // selection sort
void quicksort(int *x, int o, int p);
void quicksortcount(int *x, int n);

void stwciagrosnocy(int *x, int n)
{
	for (int i = 1; i <= n; i++)
	{
		i = x[i - 1];
	}
}

void stwciagmalejacy(int *x, int n)
{
	int r = n;
	for (int i = 1; i <= n; i++)
	{
		r = x[i - 1];
		r--;
	}
}

void stwciaglosowy(int *x, int n)
{
	for (int i = 1; i <= n; i++)
	{
		x[i - 1] = rand() % n;
	}
}

void stwciagstaly(int *x, int n)
{
	int cos = rand() % n;
	for (int i = 1; i <= n; i++)
		x[i - 1] = cos;
}


void stwciagaksztaltny(int *x, int n)
{
	int r = 0;
	for (int i = 1; i <= n / 2; i++)
	{
		while (r % 2 != 0)
			r++;
		r++;
		r = x[i - 1];
	}
	for (int i = n / 2; i <= n; i++)
	{
		while (r % 2 == 0)
			r--;
		r--;
		r = x[i - 1];
	}
}

void HeapIfy(int *x, int n, int m)
{
	int largest, temp;
	int l = 2 * m, r = (2 * m) + 1;
	if (l <= n && x[l]>x[m])
		largest = l;
	else largest = m;
	if (r <= n && x[r]>x[largest])
		largest = r;
	if (largest != m)
	{
		temp = x[largest];
		x[largest] = x[m];
		x[m] = temp;
		HeapIfy(x, n, largest);
	}
}
void BuildHeap(int *x, int n)
{
	for (int i = n / 2; i>0; i--)
		HeapIfy(x, n, i);
}

void HeapSort(int *x, int n)
{
	int temp;
	BuildHeap(x, n);
	for (int i = n; i>1; i--)
	{
		temp = x[i];
		x[i] = x[1];
		x[1] = temp;
		n--;
		HeapIfy(x, n, 1);
	}
}

void inssort(int *x, int n)
{
	double dif;
	cout.setf(ios::fixed);  //ustawienie porpawnego wyswietlania czasu
	cout.precision(5);      //z dok³adnoœcia do 5 zer
	clock_t start, end;     //ustawiamy zmienne czasowe
	start = clock();        //zabieramy czas po ukoñczeniu algorymtu
	int temp, j;
	for (int i = 1; i < n; i++)
	{
		temp = x[i];
		for (j = i - 1; j >= 0 && x[j] > temp; j--)
			x[j + 1] = x[j];
		x[j + 1] = temp;
	}
	end = clock();
	dif = (end - start) / (double)CLOCKS_PER_SEC; //(koniec-start) dzielimy przez sekundy
	cout << "Wykonanie algorytmu zajelo: " << dif << " sekund" << endl;
}


void shellsort(int *x, int n)
{
	double dif;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, end;
	start = clock();
	int q, w, e, r;                             //odstep, zmienna ster, indeks tablicy, elem tablicy
	for (q = 1; q < n; q = 3 * q + 1);          //poczatkowa wartoœæ odstepu wed³ug Knutha
	q /= 9;
	if (!q)                                     //jeœli odstêp rowny jest zero
		q++;                                        //zwiekszamy go o jeden
	while (q)                                   //dopóki jest odstêp
	{
		for (w = n - q - 1; w >= 0; w--)    //dzielimy nasz¹ tablice na odstepy, które zmniejszamy co krok
		{
			r = x[w];                   //wybieramy element tablicy wskazany przez odstep
			e = w + q;                  //ustawiawmy indeks na kolejny element danego odstepu
			while ((e<n) && (r > x[e])) //wkonujemy dopóki indeks jest mniejszy od wielkosci tablciy i element jest wiekszy od elementu wskazanego przez e
			{
				x[e - q] = x[e];    //wymieniamy elementy
				e += q;             //zwiekszamy indeks o odstep
			}
			x[e - q] = r;               //wymieniamy elementy
		}
		q /= 3;                             //zmniejszamy odstep
	}
	end = clock();
	dif = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Wykonanie algorytmu zajelo: " << dif << " sekund" << endl;
}


void selsort(int *x, int n)
{
	double dif;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, end;
	start = clock();
	int mini, tmp;
	for (int i = 0; i < n - 1; i++)
	{
		mini = i;
		for (int j = i + 1; j < n; j++)
			if (x[j] < x[mini])
				mini = j;
		if (mini != i)
		{
			tmp = x[i];
			x[i] = x[mini];
			x[mini] = tmp;
		}
	}
	end = clock();
	dif = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Wykonanie algorytmu zajelo: " << dif << " sekund" << endl;
}

void quicksort(int *x, int o, int p)
{
	int i = o;                          //lewa wartoœæ
	int j = p;                          //prawa wartoœæ
	int tmp = x[p];                     //bierzemy x z po³owy naszej tablicy
	do
	{
		while (x[i] < tmp)          //dopóki lewy jest mniejszy od "x" czyli tmp to idziemy w prawo
			i++;
		while (x[j] > tmp)          //dopóki element prawy jest wiekszy od "x" czyli tmp to idziemy w lewo
			j--;
		if (i <= j)                 //jesli lewy jest mniejszy od prawego to zmieniamy i przechodzimy na kolejene elementy
		{
			swap(x[i], x[j]);
			i++;
			j--;
		}

	} while (i <= j);                     //pêtla wykonuje siê dopóki nie zajdzie zmiana
	if (o < j) quicksort(x, o, j);      //rekurencja
	if (p > i) quicksort(x, i, p);      //rekurencja
}

void quicksortcount(int *x, int n)
{
	double dif;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, end;
	start = clock();
	quicksort(x, 0, n - 1); // wlaczamy quicksort
	end = clock();
	dif = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Wykonanie algorytmu zajelo: " << dif << " sekund" << endl;
}

int main()
{
	srand(time(NULL));//wlaczenie zegara dla randomowania zmiennych
	int n, *ciag; //deklaracja dlugosci ciagu, i wskaznika na ciag
	cout << "Podaj liczbe elementow ciagu: ";
	cin >> n; //podanie wielkosci ciagu
	ciag = new int[n]; //stworzenie nowej tablicy dynamicznej o wielkosci podanej przez uzytkownika

	system("PAUSE");
	delete[] ciag;
	return 0;
}







