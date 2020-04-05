#include "Matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

vector <Matrix> matrixes;
void LoadMatrix() {
	ifstream fin;
	fin.open("MatrixTmp.txt");
	
	int n, m;
	vector <vector <f> > tmp;
	while (fin >> n >> m) {
		tmp.clear();
		tmp.resize(n);
		for (int i=0;i<n;i++) {
			tmp[i].resize(m);
			for (int j=0;j<m;j++) fin >> tmp[i][j];
		}
		matrixes.push_back(Matrix(tmp));
	}
}
void SaveMatrix() {
	ofstream fout;
	fout.open("MatrixTmp.txt");
	
	for (Matrix tmp: matrixes) {
		fout << tmp.row() << ' ' << tmp.col() << endl;
		for (int i=0;i<tmp.row();i++) {
			for (int j=0;j<tmp.col();j++) fout << tmp.mat()[i][j] << ' ';
			fout << endl;
		}
	}
}
void CreateMatrix() {
	Matrix tmp;
	matrixes.push_back(tmp);
}
void ListMatrix() {
	int i=0;
	for (Matrix tmp: matrixes) {
		i++; cout << "========== " << i << " ==========" << endl;
		tmp.PrintMatrix(); 
	}
}
void TwoMatrix() {
	char c;
	int id1, id2;
	cout << "Answer two matrixes id: "; cin >> id1 >> id2;
	cout << "+, -, * ? "; cin >> c;
	
	Matrix tmp1 = matrixes[id1-1], tmp2 = matrixes[id2-1];
	if (c == '+') tmp1.Plus(tmp2).PrintMatrix();
	if (c == '-') tmp1.Plus(tmp2.NumMul(-1)).PrintMatrix();
	if (c == '*') tmp1.RightMul(tmp2).PrintMatrix();
}
void DetInvT() {
	int id;
	cout << "Answer matrix id: "; cin >> id;
	
	Matrix tmp = matrixes[id-1];
	cout << "Det: " << tmp.det() << endl;
	cout << "Inv: " << endl;
	tmp.Inv().PrintMatrix();
	cout << "T: " << endl;
	tmp.T().PrintMatrix();
	tmp.GaussianElimination().PrintMatrix();
}

int AskQ() {
	cout << "Please choose one: " << endl;
	cout << "1. Save and Exit" << endl;
	cout << "2. Create a new matrix" << endl;
	cout << "3. List all matrix" << endl;
	cout << "4. Two matrixes calculation" << endl;
	cout << "5. Det, Inv, T" << endl;
	cout << "Q: ";
	
	int q;
	cin >> q;
	return q;
}
bool Work(int q) {
	switch (q) {
		case 1:
			SaveMatrix();
			return 0;
		case 2:
			CreateMatrix();
			return 1;
		case 3:
			ListMatrix();
			return 1;
		case 4:
			TwoMatrix();
			return 1;
		case 5:
			DetInvT();
			return 1;
	}
}

main () {
	LoadMatrix();
	int query;
	while (query = AskQ()) if (!Work(query)) break;
}

