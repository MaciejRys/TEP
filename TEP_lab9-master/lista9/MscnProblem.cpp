#include "pch.h"
#include "MscnProblem.h"

#include <iostream>

using namespace std;

MscnProblem::MscnProblem() {
	this->D = 0;
	this->F = 0;
	this->M = 0;
	this->S = 0;

	this->sd = new double[D];
	this->sf = new double[F];
	this->sm = new double[M];
	this->ss = new double[S];

	this->cd = new double*[D];
	for (int i = 0; i < D; i++) {
		this->cd[i] = new double[F];
	}
	this->cf = new double*[F];
	for (int i = 0; i < F; i++) {
		this->cf[i] = new double[M];
	}
	this->cm = new double*[M];
	for (int i = 0; i < M; i++) {
		this->cm[i] = new double[S];
	}

	this->ud = new double[D];
	this->uf = new double[F];
	this->um = new double[M];

	this->p = new double[S];

	this->xdminmax = new double*[2 * D];
	for (int i = 0; i < 2 * D; i++) {
		this->xdminmax[i] = new double[F];
	}
	this->xfminmax = new double*[2 * F];
	for (int i = 0; i < 2 * F; i++) {
		this->xfminmax[i] = new double[M];
	}
	this->xmminmax = new double*[2 * M];
	for (int i = 0; i < 2 * M; i++) {
		this->xmminmax[i] = new double[S];
	}
}

MscnProblem::~MscnProblem() {
	for (int i = 0; i < 2 * M; i++) {
		delete[] this->xmminmax[i];
	}
	delete[] xmminmax;
	for (int i = 0; i < 2 * F; i++) {
		delete[] this->xfminmax[i];
	}
	delete[] xfminmax;
	for (int i = 0; i < 2 * D; i++) {
		delete[] this->xdminmax[i];
	}
	delete[] xdminmax;
	
	delete[] p;
	
	delete[] um;
	delete[] uf;
	delete[] ud;

	for (int i = 0; i < M; i++) {
		delete[] this->cm[i];
	}
	delete[] cm;
	for (int i = 0; i < F; i++) {
		delete[] this->cf[i];
	}
	delete[] cf;
	for (int i = 0; i < D; i++) {
		delete[] this->cd[i];
	}
	delete[] cd;

	delete[] ss;
	delete[] sm;
	delete[] sf;
	delete[] sd;
}

int MscnProblem::getFactories() {
	return this->F;
}

int MscnProblem::getShops() {
	return this->S;
}

int MscnProblem::getWarehouses() {
	return this->M;
}

int MscnProblem::getProviders() {
	return this->D;
}

bool MscnProblem::setProviders(int numberOfProviders) {
	if (numberOfProviders <= 0 || this->D == numberOfProviders) {
		return false;
	}

	int minLength = this->D <= numberOfProviders ? this->D : numberOfProviders;
	double* temp = new double[numberOfProviders];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->sd[i];
	}
	delete[] this->sd;
	this->sd = temp;

	double** tempMatrix = new double*[numberOfProviders];
	for (int i = 0; i < numberOfProviders; i++) {
		tempMatrix[i] = new double[F];
	}
	for (int i = 0; i < minLength; i++) {
		for (int j = 0; j < this->F; j++) {
			tempMatrix[i][j] = this->cd[i][j];
		}
	}
	for (int i = 0; i < D; i++) {
		delete[] this->cd[i];
	}
	delete[] this->cd;
	this->cd = tempMatrix;

	temp = new double[numberOfProviders];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->ud[i];
	}
	delete[] this->ud;
	this->ud = temp;

	tempMatrix = new double*[2 * numberOfProviders];
	for (int i = 0; i < 2 * numberOfProviders; i++) {
		tempMatrix[i] = new double[F];
	}
	for (int i = 0; i < 2 * minLength; i++) {
		for (int j = 0; j < this->F; j++) {
			tempMatrix[i][j] = xdminmax[i][j];
		}
	}
	for (int i = 0; i < D; i++) {
		delete[] this->xdminmax[i];
	}
	delete[] this->xdminmax;
	this->xdminmax = tempMatrix;

	this->D = numberOfProviders;
	return true;
}

bool MscnProblem::setFactories(int numberOfFactories) {
	if (numberOfFactories <= 0 || this->F == numberOfFactories) {
		return false;
	}

	int minLength = this->F <= numberOfFactories ? this->F : numberOfFactories;
	double* temp = new double[numberOfFactories];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->sf[i];
	}
	delete[] this->sf;
	this->sf = temp;

	double** tempMatrix = new double*[D];
	for (int i = 0; i < D; i++) {
		tempMatrix[i] = new double[numberOfFactories];
	}
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->cd[i][j];
		}
	}
	for (int i = 0; i < D; i++) {
		delete[] this->cd[i];
	}
	delete[] cd;
	this->cd = tempMatrix;

	tempMatrix = new double*[numberOfFactories];
	for (int i = 0; i < numberOfFactories; i++) {
		tempMatrix[i] = new double[M];
	}
	for (int i = 0; i < minLength; i++) {
		for (int j = 0; j < M; j++) {
			tempMatrix[i][j] = this->cf[i][j];
		}
	}
	for (int i = 0; i < F; i++) {
		delete[] this->cf[i];
	}
	delete[] this->cf;
	this->cf = tempMatrix;

	temp = new double[numberOfFactories];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->uf[i];
	}
	delete[] this->uf;
	this->uf = temp;

	tempMatrix = new double*[2 * D];
	for (int i = 0; i < 2 * D; i++) {
		tempMatrix[i] = new double[numberOfFactories];
	}
	for (int i = 0; i < 2 * D; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->xdminmax[i][j];
		}
	}
	for (int i = 0; i < 2 * D; i++) {
		delete[] this->xdminmax[i];
	}
	delete[] this->xdminmax;
	this->xdminmax = tempMatrix;

	tempMatrix = new double*[2 * numberOfFactories];
	for (int i = 0; i < 2 * numberOfFactories; i++) {
		tempMatrix[i] = new double[M];
	}
	for (int i = 0; i < 2 * minLength; i++) {
		for (int j = 0; j < M; j++) {
			tempMatrix[i][j] = this->xfminmax[i][j];
		}
	}
	for (int i = 0; i < 2 * F; i++) {
		delete[] this->xfminmax[i];
	}
	delete[] this->xfminmax;
	this->xfminmax = tempMatrix;

	this->F = numberOfFactories;
	return true;
}

bool MscnProblem::setWarehouses(int numberOfWarehouses) {
	if (numberOfWarehouses <= 0 || this->M == numberOfWarehouses) {
		return false;
	}

	int minLength = this->M <= numberOfWarehouses ? this->M : numberOfWarehouses;
	double* temp = new double[numberOfWarehouses];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->sm[i];
	}
	delete[] this->sm;
	this->sm = temp;

	double** tempMatrix = new double*[F];
	for (int i = 0; i < F; i++) {
		tempMatrix[i] = new double[numberOfWarehouses];
	}
	for (int i = 0; i < F; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->cf[i][j];
		}
	}
	for (int i = 0; i < F; i++) {
		delete[] this->cf[i];
	}
	delete[] this->cf;
	this->cf = tempMatrix;

	tempMatrix = new double*[numberOfWarehouses];
	for (int i = 0; i < numberOfWarehouses; i++) {
		tempMatrix[i] = new double[S];
	}
	for (int i = 0; i < minLength; i++) {
		for (int j = 0; j < S; j++) {
			tempMatrix[i][j] = this->cm[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		delete[] this->cm[i];
	}
	delete[] this->cm;
	this->cm = tempMatrix;

	temp = new double[numberOfWarehouses];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->um[i];
	}
	delete[] this->um;
	this->um = temp;

	tempMatrix = new double*[2 * F];
	for (int i = 0; i < 2 * F; i++) {
		tempMatrix[i] = new double[numberOfWarehouses];
	}
	for (int i = 0; i < 2 * F; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->xfminmax[i][j];
		}
	}
	for (int i = 0; i < 2 * F; i++) {
		delete[] this->xfminmax[i];
	}
	delete[] this->xfminmax;
	this->xfminmax = tempMatrix;

	tempMatrix = new double*[2 * numberOfWarehouses];
	for (int i = 0; i < 2 * numberOfWarehouses; i++) {
		tempMatrix[i] = new double[S];
	}
	for (int i = 0; i < 2 * minLength; i++) {
		for (int j = 0; j < S; j++) {
			tempMatrix[i][j] = this->xmminmax[i][j];
		}
	}
	for (int i = 2 * minLength; i < 2 * numberOfWarehouses; i++) {
		for (int j = 0; j < S; j++) {
			tempMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < 2 * M; i++) {
		delete[] this->xmminmax[i];
	}
	delete[] this->xmminmax;
	this->xmminmax = tempMatrix;

	this->M = numberOfWarehouses;
	return true;
}

bool MscnProblem::setShops(int numberOfShops) {
	if (numberOfShops <= 0 || this->S == numberOfShops) {
		return false;
	}

	int minLength = this->S <= numberOfShops ? this->S : numberOfShops;
	double* temp = new double[numberOfShops];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->ss[i];
	}
	delete[] this->ss;
	this->ss = temp;

	double** tempMatrix = new double*[M];
	for (int i = 0; i < M; i++) {
		tempMatrix[i] = new double[numberOfShops];
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->cm[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		delete[] this->cm[i];
	}
	delete[] this->cm;
	this->cm = tempMatrix;

	temp = new double[numberOfShops];
	for (int i = 0; i < minLength; i++) {
		temp[i] = this->p[i];
	}
	delete[] this->p;
	this->p = temp;

	tempMatrix = new double*[2 * M];
	for (int i = 0; i < 2 * M; i++) {
		tempMatrix[i] = new double[numberOfShops];
	}
	for (int i = 0; i < 2 * M; i++) {
		for (int j = 0; j < minLength; j++) {
			tempMatrix[i][j] = this->xmminmax[i][j];
		}
	}
	for (int i = 0; i < 2 * M; i++) {
		for (int j = minLength; j < numberOfShops; j++) {
			tempMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < 2 * M; i++) {
		delete[] this->xmminmax[i];
	}
	delete[] this->xmminmax;
	this->xmminmax = tempMatrix;

	this->S = numberOfShops;
	return true;
}

bool MscnProblem::setCostInCDMatrix(int dIndex, int fIndex, double costValue) {
	if (costValue < 0 || dIndex < 0 || dIndex >= D || fIndex < 0 || fIndex >= F) {
		return false;
	}
	this->cd[dIndex][fIndex] = costValue;
	return true;
}

bool MscnProblem::setCostInCFMatrix(int fIndex, int mIndex, double costValue) {
	if (costValue < 0 || fIndex < 0 || fIndex >= F || mIndex < 0 || mIndex >= M) {
		return false;
	}
	this->cf[fIndex][mIndex] = costValue;
	return true;
}

bool MscnProblem::setCostInCMMatrix(int mIndex, int sIndex, double costValue) {
	if (costValue < 0 || mIndex < 0 || mIndex >= M || sIndex < 0 || sIndex >= S) {
		return false;
	}
	this->cm[mIndex][sIndex] = costValue;
	return true;
}

bool MscnProblem::setProviderProductionCapacity(int index, double capacityValue) {
	if (capacityValue < 0 || index < 0 || index >= D) {
		return false;
	}
	this->sd[index] = capacityValue;
	for (int i = 0; i < F; i++) {
		xdminmax[2 * index][i] = 0;
		xdminmax[(2 * index) + 1][i] = sd[index];
	}
	return true;
}

bool MscnProblem::setFactoryProductionCapacity(int index, double capacityValue) {
	if (capacityValue < 0 || index < 0 || index >= F) {
		return false;
	}
	this->sf[index] = capacityValue;
	for (int i = 0; i < M; i++) {
		xfminmax[2 * index][i] = 0;
		xfminmax[(2 * index) + 1][i] = sf[index];
	}
	return true;
}

bool MscnProblem::setWarehouseCapacity(int index, double capacityValue) {
	if (capacityValue < 0 || index < 0 || index >= M) {
		return false;
	}
	this->sm[index] = capacityValue;
	this->setXmminmax();
	return true;
}

bool MscnProblem::setShopDemand(int index, double demandValue) {
	if (demandValue < 0 || index < 0 || index >= S) {
		return false;
	}
	this->ss[index] = demandValue;
	this->setXmminmax();
	return true;
}

bool MscnProblem::setUsingProviderCost(int index, double costValue) {
	if (costValue < 0 || index < 0 || index >= D) {
		return false;
	}
	this->ud[index] = costValue;
	return true;
}

bool MscnProblem::setUsingFactoryCost(int index, double costValue) {
	if (costValue < 0 || index < 0 || index >= F) {
		return false;
	}
	this->uf[index] = costValue;
	return true;
}

bool MscnProblem::setUsingWarehouseCost(int index, double costValue) {
	if (costValue < 0 || index < 0 || index >= M) {
		return false;
	}
	this->um[index] = costValue;
	return true;
}

bool MscnProblem::setShopIncome(int index, double incomeValue) {
	if (incomeValue < 0 || index < 0 || index >= S) {
		return false;
	}
	this->p[index] = incomeValue;
	return true;
}

double MscnProblem::getQuality(double *** solution, int D, int F, int M, int S) {
	if (!checkSolution(solution, D, F, M, S)) {
		return -1;
	}
	double Kt = 0;
	double Ku = 0;
	double P = 0;
	double z = 0;

	for (int i = 0; i < this->D; i++) {
		for (int j = 0; j < this->F; j++) {
			Kt += cd[i][j] * solution[0][i][j];
		}
	}
	for (int i = 0; i < this->F; i++) {
		for (int j = 0; j < this->M; j++) {
			Kt += cf[i][j] * solution[1][i][j];
		}
	}
	for (int i = 0; i < this->M; i++) {
		for (int j = 0; j < this->S; j++) {
			Kt += cm[i][j] * solution[2][i][j];
		}
	}

	for (int i = 0; i < this->D; i++) {
		double temp = 0;
		for (int j = 0; j < this->F; j++) {
			temp += solution[0][i][j];
		}
		int epsilon = temp <= 0 ? 0 : 1;
		Ku += epsilon * temp * ud[i];
	}
	for (int i = 0; i < this->F; i++) {
		double temp = 0;
		for (int j = 0; j < this->M; j++) {
			temp += solution[1][i][j];
		}
		int epsilon = temp <= 0 ? 0 : 1;
		Ku += epsilon * temp * uf[i];
	}
	for (int i = 0; i < this->M; i++) {
		double temp = 0;
		for (int j = 0; j < this->S; j++) {
			temp += solution[2][i][j];
		}
		int epsilon = temp <= 0 ? 0 : 1;
		Ku += epsilon * temp * um[i];
	}

	for (int i = 0; i < this->M; i++) {
		for (int j = 0; j < this->S; j++) {
			P += p[j] * solution[2][i][j];
		}
	}

	z = P - Kt - Ku;

	return z;
}

bool MscnProblem::constraintsSatisfied(double *** solution, int D, int F, int M, int S) {
	if (!checkSolution(solution, D, F, M, S)) {
		return false;
	}

	double temp = 0;
	double temp2 = 0;

	for (int i = 0; i < this->D; i++) {
		for (int j = 0; j < this->F; j++) {
			temp += solution[0][i][j];
		}
		if (temp > sd[i]) {
			return false;
		}
		temp = 0;
	}

	for (int i = 0; i < this->F; i++) {
		for (int j = 0; j < this->M; j++) {
			temp += solution[1][i][j];
		}
		if (temp > sf[i]) {
			return false;
		}
		temp = 0;
	}

	for (int i = 0; i < this->M; i++) {
		for (int j = 0; j < this->S; j++) {
			temp += solution[2][i][j];
		}
		if (temp > sm[i]) {
			return false;
		}
		temp = 0;
	}

	for (int i = 0; i < this->S; i++) {
		for (int j = 0; j < this->M; j++) {
			temp += solution[2][j][i];
		}
		if (temp > ss[i]) {
			return false;
		}
		temp = 0;
	}

	for (int i = 0; i < this->D; i++) {
		for (int j = 0; j < this->D; j++) {
			temp += solution[0][j][i];
		}
		for (int j = 0; j < this->M; j++) {
			temp2 += solution[1][i][j];
		}
		if (temp < temp2) {
			return false;
		}
		temp = 0;
		temp2 = 0;
	}

	for (int i = 0; i < this->M; i++) {
		for (int j = 0; j < this->F; j++) {
			temp += solution[1][j][i];
		}
		for (int j = 0; j < this->S; j++) {
			temp2 += solution[2][i][j];
		}
		if (temp < temp2) {
			return false;
		}
	}

	return true;
}

double MscnProblem::getMin(int solutionId, int colId, int rowId) {
	if (solutionId < 0 || solutionId >= 3 || colId < 0 || rowId < 0) {
		return -1;
	}
	switch (solutionId) {
	case 0:
		if (colId >= 2 * D || rowId >= F) {
			return -1;
		}
		return xdminmax[2 * colId][rowId];
		break;
	case 1:
		if (colId >= 2 * F || rowId >= M) {
			return -1;
		}
		return xfminmax[2 * colId][rowId];
		break;
	case 2:
		if (colId >= 2 * M || rowId >= S) {
			return -1;
		}
		return xmminmax[2 * colId][rowId];
		break;
	}
}

double MscnProblem::getMax(int solutionId, int colId, int rowId) {
	if (solutionId < 0 || solutionId >= 3 || colId < 0 || rowId < 0) {
		return -1;
	}
	switch (solutionId) {
	case 0:
		if (colId >= 2 * D || rowId >= F) {
			return -1;
		}
		return xdminmax[(2 * colId) + 1][rowId];
		break;
	case 1:
		if (colId >= 2 * F || rowId >= M) {
			return -1;
		}
		return xfminmax[(2 * colId) + 1][rowId];
		break;
	case 2:
		if (colId >= 2 * M || rowId >= S) {
			return -1;
		}
		return xmminmax[(2 * colId) + 1][rowId];
		break;
	}
}

bool MscnProblem::setXmminmax() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < S; j++) {
			xmminmax[2 * i][j] = 0;
			xmminmax[(2 * i) + 1][j] = sm[i];
		}
	}
	for (int i = 0; i < S; i++) {
		for (int j = 0; j < M; j++) {
			if (xmminmax[(2 * j) + 1][i] > ss[i]) {
				xmminmax[(2 * j) + 1][i] = ss[i];
			}
		}
	}
	return true;
}

bool MscnProblem::saveProblem(string fileName) {
	FILE* fileToWrite = fopen(fileName.c_str(), "w+");
	if (fileToWrite == nullptr) {
		return false;
	}
	fprintf(fileToWrite, "D %d\n", D);
	fprintf(fileToWrite, "F %d\n", F);
	fprintf(fileToWrite, "M %d\n", M);
	fprintf(fileToWrite, "S %d\n", S);
	fputs("sd\n", fileToWrite);
	for (int i = 0; i < D; i++) {
		fprintf(fileToWrite, "%g ", sd[i]);
	}
	fputs("\nsf\n", fileToWrite);
	for (int i = 0; i < F; i++) {
		fprintf(fileToWrite, "%g ", sf[i]);
	}
	fputs("\nsm\n", fileToWrite);
	for (int i = 0; i < M; i++) {
		fprintf(fileToWrite, "%g ", sm[i]);
	}
	fputs("\nss\n", fileToWrite);
	for (int i = 0; i < S; i++) {
		fprintf(fileToWrite, "%g ", ss[i]);
	}
	fputs("\ncd\n", fileToWrite);
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < F; j++) {
			fprintf(fileToWrite, "%g ", cd[i][j]);
		}
		fputs("\n", fileToWrite);
	}
	fputs("cf\n", fileToWrite);
	for (int i = 0; i < F; i++) {
		for (int j = 0; j < M; j++) {
			fprintf(fileToWrite, "%g ", cf[i][j]);
		}
		fputs("\n", fileToWrite);
	}
	fputs("cm\n", fileToWrite);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < S; j++) {
			fprintf(fileToWrite, "%g ", cm[i][j]);
		}
		fputs("\n", fileToWrite);
	}
	fputs("ud\n", fileToWrite);
	for (int i = 0; i < D; i++) {
		fprintf(fileToWrite, "%g ", ud[i]);
	}
	fputs("\nuf\n", fileToWrite);
	for (int i = 0; i < F; i++) {
		fprintf(fileToWrite, "%g ", uf[i]);
	}
	fputs("\num\n", fileToWrite);
	for (int i = 0; i < M; i++) {
		fprintf(fileToWrite, "%g ", um[i]);
	}
	fputs("\np\n", fileToWrite);
	for (int i = 0; i < S; i++) {
		fprintf(fileToWrite, "%g ", p[i]);
	}
	fputs("\nxdminmax\n", fileToWrite);
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < F; j++) {
			fprintf(fileToWrite, "%g %g ", xdminmax[2 * i][j], xdminmax[(2 * i) + 1][j]);
		}
		fputs("\n", fileToWrite);
	}
	fputs("xfminmax\n", fileToWrite);
	for (int i = 0; i < F; i++) {
		for (int j = 0; j < M; j++) {
			fprintf(fileToWrite, "%g %g ", xfminmax[2 * i][j], xfminmax[(2 * i) + 1][j]);
		}
		fputs("\n", fileToWrite);
	}
	fputs("xmminmax\n", fileToWrite);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < S; j++) {
			fprintf(fileToWrite, "%g %g ", xmminmax[2 * i][j], xmminmax[(2 * i) + 1][j]);
		}
		fputs("\n", fileToWrite);
	}

	fclose(fileToWrite);
	return true;
}

bool MscnProblem::openProblem(string fileName) {
	FILE* fileToRead = fopen(fileName.c_str(), "r");
	if (fileToRead == nullptr) {
		return false;
	}
	string temp = "";
	int j = 0;
	int k = 0;
	int l = 0;
	char line[500];
	for (int i = 0; i < 4; i++) {
		fgets(line, 500, fileToRead);
		j = 2;
		while (line[j] != '\n') {
			temp += line[j];
			j++;
		}
		switch (i) {
		case 0:
			this->setProviders(stoi(temp));
			break;
		case 1:
			this->setFactories(stoi(temp));
			break;
		case 2:
			this->setWarehouses(stoi(temp));
			break;
		case 3:
			this->setShops(stoi(temp));
			break;
		}
		temp = "";
	}
	for (int i = 0; i < 4; i++) {
		fgets(line, 500, fileToRead);
		fgets(line, 500, fileToRead);
		temp = "";
		j = 0;
		k = 0;
		while (line[j] != '\n') {
			if (line[j] != ' ') {
				temp += line[j];
			}
			else {
				switch (i) {
				case 0:
					this->setProviderProductionCapacity(k, stod(temp));
					break;
				case 1:
					this->setFactoryProductionCapacity(k, stod(temp));
					break;
				case 2:
					this->setWarehouseCapacity(k, stod(temp));
					break;
				case 3:
					this->setShopDemand(k, stod(temp));
					break;
				}
				temp = "";
				k++;
			}
			j++;
		}
	}
	for (int i = 0; i < 3; i++) {
		fgets(line, 500, fileToRead);
		temp = "";
		j = 0;
		k = 0;
		l = 0;
		switch (i) {
		case 0:
			l = D;
			break;
		case 1:
			l = F;
			break;
		case 2:
			l = M;
			break;
		}
		for (int m = 0; m < l; m++) {
			j = 0;
			k = 0;
			fgets(line, 500, fileToRead);
			while (line[j] != '\n') {
				if (line[j] != ' ') {
					temp += line[j];
				}
				else {
					switch (i) {
					case 0:
						this->setCostInCDMatrix(m, k, stod(temp));
						break;
					case 1:
						this->setCostInCFMatrix(m, k, stod(temp));
						break;
					case 2:
						this->setCostInCMMatrix(m, k, stod(temp));
						break;
					}
					temp = "";
					k++;
				}
				j++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		fgets(line, 500, fileToRead);
		fgets(line, 500, fileToRead);
		temp = "";
		j = 0;
		k = 0;
		while (line[j] != '\n') {
			if (line[j] != ' ') {
				temp += line[j];
			}
			else {
				switch (i) {
				case 0:
					this->setUsingProviderCost(k, stod(temp));
					break;
				case 1:
					this->setUsingFactoryCost(k, stod(temp));
					break;
				case 2:
					this->setUsingWarehouseCost(k, stod(temp));
					break;
				case 3:
					this->setShopIncome(k, stod(temp));
					break;
				}
				temp = "";
				k++;
			}
			j++;
		}
	}
	
		
	for (int i = 0; i < 12; i++) {
		fgets(line, 500, fileToRead);


	
	}
	for (int i = 0; i < 6; i++) {

		fgets(line, 500, fileToRead);
		cout << line << endl;
		string temp = "";
		for (int j = 6; j < 10; j++) {
			temp += line[j];
		}


		switch (i) {
		case 0:
			this->dfmin = stod(temp);
			break;
		case 1:
			this->dfmax = stod(temp);

			break;
		case 2:
			this->fcmin = stod(temp);
			break;
		case 3:
			this->fcmax = stod(temp);
			break;
		case 4:
			this->csmin = stod(temp);
			break;
		case 5:
			this->csmax = stod(temp);
			break;
		}

	}

	fclose(fileToRead);
	return true;
}

bool MscnProblem::checkSolution(double *** solution, int D, int F, int M, int S) {
	if (solution == nullptr || this->D != D || this->F != F || this->M != M || this->S != S) {
		return false;
	}
	for (int i = 0; i < this->D; i++) {
		for (int j = 0; j < this->F; j++) {
			if (solution[0][i][j] < 0) {
				return false;
			}
		}
	}
	for (int i = 0; i < this->F; i++) {
		for (int j = 0; j < this->M; j++) {
			if (solution[1][i][j] < 0) {
				return false;
			}
		}
	}
	for (int i = 0; i < this->M; i++) {
		for (int j = 0; j < this->S; j++) {
			if (solution[2][i][j] < 0) {
				return false;
			}
		}
	}
	return true;
}
