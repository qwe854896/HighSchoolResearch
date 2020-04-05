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
	cout << "讀取資料中..." << endl;
	int n;
	while (fin >> n) {
		fout << n << endl;
		// cout << n << endl;
		vote[n-V] = 1;
	}
	cout << "讀取完畢..." << endl; 
}

int main () {
	nin.open("num.txt");
	int times;
	nin >> times;
	times++;
	nout.open("num.txt");
	nout << times << endl;
	
	cout << "現在是第" << times << "次操作" << endl; 
	
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
	cout << "請輸入學號..." << endl; 
	
	while (cin >> N) {
		if (vote[N-V]) {
			cout << "此學號" << N << "已領票" << endl; 
		}
		else {
			vote[N-V] = 1;
			fout << N << endl;
		}
		
		cout << endl;
	}
	
}

