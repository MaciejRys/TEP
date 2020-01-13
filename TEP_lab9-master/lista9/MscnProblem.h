#pragma once
#pragma warning(disable:4996)

#include <string>

using namespace std;

class MscnProblem {

private:
	int D;		//liczba dostawc�w
	int F;		//liczba fabryk
	int M;		//liczba magazyn�w
	int S;		//liczba sklep�w
	
	double* sd;		//moc produkcyjna dostawcy
	double* sf;		//moc produkcyjna fabryki
	double* sm;		//pojemno�� magazynu
	double* ss;		//zapotrzebowanie rynkowe sklepu

	double** cd;		//koszt wytworzenie i przewiezienia surowca od dostawcy d do fabryki f
	double** cf;		//koszt wyprodukowania produktu w fabryce f i przewiezienia go do magazynu m
	double** cm;		//koszt przechowania produktu w magazynie m i przewiezienia go do sklepu s

	double* ud;		//jednorazowy koszt korzystania z us�ug dostawcy d
	double* uf;		//jednorazowy koszt korzystania z fabryki f
	double* um;		//jednorazowy koszt korzystania z magazynu m

	double* p;		//przych�d ze sprzeda�y produktu w sklepie s

	double** xdminmax;		//warto�� min i max ilo�ci surowca wytwarzanego u dostawcy d i transportowanego do fabryki f
	double** xfminmax;		//warto�� min i max ilo�ci produkt�w wytwarzanych w fabryce f i transportowanych do magazynu m
	double** xmminmax;		//warto�� min i max ilo�ci produkt�w przechowywanych w magazynie m i transportowanych do sklepu s

	double dfmin;
	double dfmax;
	double fcmin;
	double fcmax;
	double csmin;
	double csmax;

public:
	MscnProblem();		//konstruktor bezparametrowy
	~MscnProblem();		//destruktor

	int getProviders();  //otrzymanie ilo�ci dostawc�w
	int getFactories();  //otrzymanie ilo�ci fabryk
	int getWarehouses(); //otrzymanie ilosci magazynow
	int getShops();      //otrzymanie ilosci sklep�w

	bool setProviders(int numberOfProviders);		//ustawia ilo�� dostawc�w
	bool setFactories(int numberOfFactories);		//ustawia ilo�� fabryk
	bool setWarehouses(int numberOfWarehouses);		//ustawia ilo�� magazyn�w
	bool setShops(int numberOfShops);				//ustawia ilo�� sklep�w

	bool setCostInCDMatrix(int dIndex, int fIndex, double costValue);		//ustawia nowy koszt w cd[dIndex][fIndex]
	bool setCostInCFMatrix(int fIndex, int mIndex, double costValue);		//ustawia nowy koszt w cf[fIndex][mIndex]
	bool setCostInCMMatrix(int mIndex, int sIndex, double costValue);		//ustawia nowy koszt w cm[mIndex][sIndex]

	bool setProviderProductionCapacity(int index, double capacityValue);		//ustawia now� moc produkcji dostawcy o zadanym indeksie
	bool setFactoryProductionCapacity(int index, double capacityValue);			//ustawia now� moc produkcji fabryki o zadanym indeksie
	bool setWarehouseCapacity(int index, double capacityValue);					//ustawia now� pojemno�� magazynu o zadanym indeksie
	bool setShopDemand(int index, double demandValue);							//ustawia now� warto�� zapotrzebowania sklepu o zadanym indeksie

	bool setUsingProviderCost(int index, double costValue);						//ustawia nowy koszt korzystania z us�ug dostawcy o zadanym indeksie
	bool setUsingFactoryCost(int index, double costValue);						//ustawia nowy koszt korzystania z us�ug fabryki o zadanym indeksie
	bool setUsingWarehouseCost(int index, double costValue);					//ustawia nowy koszt korzystania z us�ug magazynu o zadanym indeksie

	bool setShopIncome(int index, double incomeValue);							//ustawia nowy przych�d ze sprzeda�y produktu w sklepie o zadanym indeksie

	double getQuality(double*** solution, int D, int F, int M, int S);			//zwraca warto�� zysku dla rozwi�zania
	bool constraintsSatisfied(double*** solution, int D, int F, int M, int S);	//sprawdza czy rozwi�zanie nie �amie ogranicze� i zwraca true je�li tak jest

	double getMin(int solutionId, int colId, int rowId);						//zwraca minimaln� warto�� dla solution[solutionId][colId][rowId]
	double getMax(int solutionId, int colId, int rowId);						//zwraca maksymaln� warto�� dla solution[solutionId][colId][rowId]

	bool setXmminmax();

	bool saveProblem(string fileName);		//zapisuje obiekt do pliku tekstowego
	bool openProblem(string fileName);		//odczytuje obiekt z pliku tekstowego


	bool checkSolution(double*** solution, int D, int F, int M, int S);	//sprawdza rozwi�zanie pod wzgl�dem d�ugo�ci tablic
};
