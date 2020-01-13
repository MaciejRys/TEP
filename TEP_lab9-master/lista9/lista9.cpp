// lista9.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "MscnProblem.h"

#include <iostream>

using namespace std;
void test() {
	int D = 1;
	int F = 1;
	int M = 1;
	int S = 1;
	double*** sol = new double** [2];
	sol[0] = new double* [D];
	sol[1] = new double* [F];
	sol[2] = new double* [M];
	sol[0][0] = new double[F];
	sol[1][0] = new double[M];
	sol[2][0] = new double[S];
	sol[0][0][0] = 1;
	sol[1][0][0] = 1;
	sol[2][0][0] = 1;

	MscnProblem problem;
	problem.setProviders(1);
	problem.setFactories(1);
	problem.setWarehouses(1);
	problem.setShops(1);

	problem.setProviderProductionCapacity(0, 100);
	problem.setFactoryProductionCapacity(0, 50);
	problem.setWarehouseCapacity(0, 10.5);
	problem.setShopDemand(0, 100);

	problem.setCostInCDMatrix(0, 0, 3);
	problem.setCostInCFMatrix(0, 0, 4);
	problem.setCostInCMMatrix(0, 0, 1);

	problem.setUsingProviderCost(0, 10);
	problem.setUsingFactoryCost(0, 10);
	problem.setUsingWarehouseCost(0, 10);

	problem.setShopIncome(0, 100);
	problem.saveProblem("problem3.txt");
	problem.openProblem("problem3.txt");

	cout << problem.getQuality(sol, D, F, M, S) << endl;
	cout << problem.constraintsSatisfied(sol, D, F, M, S) << endl;



}
void test2() {
	int D = 2;
	int F = 3;
	int M = 4;
	int S = 5;
	double*** sol = new double**[2];
	sol[0] = new double* [D];
	sol[1] = new double* [F];
	sol[2] = new double* [M];
	sol[0][0] = new double[F];
	sol[1][0] = new double[M];
	sol[2][0] = new double[S];
	
	sol[0][0][0] = 1;
	sol[0][0][1] = 2;
	sol[0][0][2] = 3;
	
	sol[0][1][0] = 4;
	sol[0][1][1] = 2;
	sol[0][1][2] = 3;
	

	sol[1][0][0] = 5;
	sol[1][0][1] = 1;
	sol[1][0][2] = 2;
	sol[1][0][3] = 1;

	sol[1][1][0] = 1;
	sol[1][1][1] = 3;
	sol[1][1][2] = 1;
	sol[1][1][3] = 4;

	sol[1][2][0] = 2;
	sol[1][2][1] = 1;
	sol[1][2][2] = 4;
	sol[1][2][3] = 3;


	sol[2][0][0] = 1;
	sol[2][0][1] = 1;
	sol[2][0][2] = 1;
	sol[2][0][3] = 1;
	sol[2][0][4] = 1;

	sol[2][1][0] = 1;
	sol[2][1][1] = 1;
	sol[2][1][2] = 1;
	sol[2][1][3] = 1;
	sol[2][1][4] = 1;

	sol[2][2][0] = 1;
	sol[2][2][1] = 1;
	sol[2][2][2] = 1;
	sol[2][2][3] = 1;
	sol[2][2][4] = 1;

	sol[2][3][0] = 1;
	sol[2][3][1] = 1;
	sol[2][3][2] = 1;
	sol[2][3][3] = 1;
	sol[2][3][4] = 1;

	MscnProblem problem;
	problem.openProblem("problem2.txt");

	cout << problem.getQuality(sol, D, F, M, S) << endl;
	cout << problem.constraintsSatisfied(sol, D, F, M, S) << endl;

}

int main() {
	//test();
	//test2();
	MscnProblem problem;
	problem.openProblem("problem2.txt");
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
