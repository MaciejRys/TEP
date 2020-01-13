#pragma once
#pragma warning(disable:4996)

#include <string>

using namespace std;

class MscnProblem {

private:
	int D;		//liczba dostawców
	int F;		//liczba fabryk
	int M;		//liczba magazynów
	int S;		//liczba sklepów
	
	double* sd;		//moc produkcyjna dostawcy
	double* sf;		//moc produkcyjna fabryki
	double* sm;		//pojemnoœæ magazynu
	double* ss;		//zapotrzebowanie rynkowe sklepu

	double** cd;		//koszt wytworzenie i przewiezienia surowca od dostawcy d do fabryki f
	double** cf;		//koszt wyprodukowania produktu w fabryce f i przewiezienia go do magazynu m
	double** cm;		//koszt przechowania produktu w magazynie m i przewiezienia go do sklepu s

	double* ud;		//jednorazowy koszt korzystania z us³ug dostawcy d
	double* uf;		//jednorazowy koszt korzystania z fabryki f
	double* um;		//jednorazowy koszt korzystania z magazynu m

	double* p;		//przychód ze sprzeda¿y produktu w sklepie s

	double** xdminmax;		//wartoœæ min i max iloœci surowca wytwarzanego u dostawcy d i transportowanego do fabryki f
	double** xfminmax;		//wartoœæ min i max iloœci produktów wytwarzanych w fabryce f i transportowanych do magazynu m
	double** xmminmax;		//wartoœæ min i max iloœci produktów przechowywanych w magazynie m i transportowanych do sklepu s

	double dfmin;
	double dfmax;
	double fcmin;
	double fcmax;
	double csmin;
	double csmax;

public:
	MscnProblem();		//konstruktor bezparametrowy
	~MscnProblem();		//destruktor

	int getProviders();  //otrzymanie iloœci dostawców
	int getFactories();  //otrzymanie iloœci fabryk
	int getWarehouses(); //otrzymanie ilosci magazynow
	int getShops();      //otrzymanie ilosci sklepów

	bool setProviders(int numberOfProviders);		//ustawia iloœæ dostawców
	bool setFactories(int numberOfFactories);		//ustawia iloœæ fabryk
	bool setWarehouses(int numberOfWarehouses);		//ustawia iloœæ magazynów
	bool setShops(int numberOfShops);				//ustawia iloœæ sklepów

	bool setCostInCDMatrix(int dIndex, int fIndex, double costValue);		//ustawia nowy koszt w cd[dIndex][fIndex]
	bool setCostInCFMatrix(int fIndex, int mIndex, double costValue);		//ustawia nowy koszt w cf[fIndex][mIndex]
	bool setCostInCMMatrix(int mIndex, int sIndex, double costValue);		//ustawia nowy koszt w cm[mIndex][sIndex]

	bool setProviderProductionCapacity(int index, double capacityValue);		//ustawia now¹ moc produkcji dostawcy o zadanym indeksie
	bool setFactoryProductionCapacity(int index, double capacityValue);			//ustawia now¹ moc produkcji fabryki o zadanym indeksie
	bool setWarehouseCapacity(int index, double capacityValue);					//ustawia now¹ pojemnoœæ magazynu o zadanym indeksie
	bool setShopDemand(int index, double demandValue);							//ustawia now¹ wartoœæ zapotrzebowania sklepu o zadanym indeksie

	bool setUsingProviderCost(int index, double costValue);						//ustawia nowy koszt korzystania z us³ug dostawcy o zadanym indeksie
	bool setUsingFactoryCost(int index, double costValue);						//ustawia nowy koszt korzystania z us³ug fabryki o zadanym indeksie
	bool setUsingWarehouseCost(int index, double costValue);					//ustawia nowy koszt korzystania z us³ug magazynu o zadanym indeksie

	bool setShopIncome(int index, double incomeValue);							//ustawia nowy przychód ze sprzeda¿y produktu w sklepie o zadanym indeksie

	double getQuality(double*** solution, int D, int F, int M, int S);			//zwraca wartoœæ zysku dla rozwi¹zania
	bool constraintsSatisfied(double*** solution, int D, int F, int M, int S);	//sprawdza czy rozwi¹zanie nie ³amie ograniczeñ i zwraca true jeœli tak jest

	double getMin(int solutionId, int colId, int rowId);						//zwraca minimaln¹ wartoœæ dla solution[solutionId][colId][rowId]
	double getMax(int solutionId, int colId, int rowId);						//zwraca maksymaln¹ wartoœæ dla solution[solutionId][colId][rowId]

	bool setXmminmax();

	bool saveProblem(string fileName);		//zapisuje obiekt do pliku tekstowego
	bool openProblem(string fileName);		//odczytuje obiekt z pliku tekstowego


	bool checkSolution(double*** solution, int D, int F, int M, int S);	//sprawdza rozwi¹zanie pod wzglêdem d³ugoœci tablic
};
