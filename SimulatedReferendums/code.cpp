#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define V 510001

bool vote[210000] = {0}; // + 510001

ifstream fin;
ifstream nin;
ofstream fout;
ofstream nout;

void load_saves() {
	cout << "Ū����Ƥ�..." << endl;
	int n;
	while (fin >> n) {
		fout << n << endl;
		// cout << n << endl;
		vote[n-V] = 1;
	}
	cout << "Ū������..." << endl; 
}

int main () {
	nin.open("num.txt");
	int times;
	nin >> times;
	times++;
	nout.open("num.txt");
	nout << times << endl;
	
	cout << "�{�b�O��" << times << "���ާ@" << endl; 
	
	if (times & 1) {
		fin.open("saves/memory_1.txt");
		fout.open("saves/memory_2.txt");
	}
	else {
		fin.open("saves/memory_2.txt");
		fout.open("saves/memory_1.txt");
	}
	
	
	load_saves();
	
	int N;
	cout << "�п�J�Ǹ�..." << endl; 
	
	while (cin >> N) {
		if (vote[N-V]) {
			cout << "���Ǹ�" << N << "�w�Ⲽ" << endl; 
		}
		else {
			vote[N-V] = 1;
			fout << N << endl;
		}
		
		cout << endl;
	}
	
}

