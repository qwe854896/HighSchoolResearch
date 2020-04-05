#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define f double

class Matrix {
	public:
		Matrix() {
			cout << "row: "; cin >> _row;
			cout << "col: "; cin >> _col;
			cout << "matrix: " << endl;
			_mat.resize(_row);
			for (int i=0;i<_row;i++) {
				_mat[i].resize(_col);
				for (int j=0;j<_col;j++) cin >> _mat[i][j];
			}
		}
		Matrix(int mode, int n, int m) { //special Matrix
			_row = n;
			_col = m;
			_mat.resize(n);
			for (int i=0;i<n;i++) {
				_mat[i].resize(m);
				for (int j=0;j<m;j++) {
					if (mode and i == j) _mat[i][j] = 1;
					else _mat[i][j] = 0;
				}
			}
		}
		Matrix(vector <vector <f> > mat) {
			_row = mat.size();
			_col = mat[0].size();
			_mat = mat;
		} 
		
		void PrintMatrix() {
			for (int i=0;i<_row;i++) {
				for (int j=0;j<_col;j++) cout << _mat[i][j] << ' ';
				cout << endl;
			}
		}
		
		int row() {
			return _row;
		}
		int col() {
			return _col;
		}
		f det() {
			if (!_CalDet) GaussianElimination();
			return _det;
		}
		vector <vector <f> > mat() {
			return _mat;
		}
		
		Matrix Plus(Matrix B) {
			if (row() != B.row() or col() != B.col()) return Matrix(0, 0, 0);
			Matrix C(0, row(), col());
			for (int i=0;i<row();i++) for (int j=0;j<col();j++) C._mat[i][j] = mat()[i][j] + B.mat()[i][j];
			
			return C;
		}
		Matrix NumMul(int c) {
			Matrix C(0, row(), col());
			for (int i=0;i<row();i++) for (int j=0;j<col();j++) C._mat[i][j] = c * mat()[i][j];
			
			return C;
		}
		Matrix T() {
			if (_CalT) return Matrix(_T);
			Matrix C(0, col(), row());
			for (int i=0;i<col();i++) for (int j=0;j<row();j++) C._mat[i][j] = mat()[j][i];
			
			_CalT = 1; _T = C.mat();
			C._CalT = 1; C._T = mat();
			return C;
		}
		
		Matrix LeftMul(Matrix B) {
			if (B.col() != row()) return Matrix(0, 0, 0);
			Matrix AT = T();
			Matrix C(0, B.row(), col());
			for (int i=0;i<B.row();i++) for(int j=0;j<col();j++) for (int k=0;k<row();k++) C._mat[i][j] += B.mat()[i][k] * AT.mat()[j][k];
			
			return C;
		}
		Matrix RightMul(Matrix B) {
			return B.LeftMul(Matrix(mat()));
		}
		Matrix Inv() { //only square
			if (_CalInv) return Matrix(_Inv);
			
			if (row() != col()) return Matrix(0, 0, 0);
			Matrix tmp = Matrix(mat());
			tmp._col *= 2;
			
			for (int i=0;i<row();i++) for (int j=0;j<row();j++) tmp._mat[i].push_back((i == j));
			tmp = tmp.GaussianElimination();
			
			Matrix INV(0, row(), col());
			for (int i=0;i<row();i++) for (int j=0;j<col();j++) INV._mat[i][j] = tmp.mat()[i][j+_row];
			
			_CalInv = 1; _Inv = INV.mat();
			INV._CalInv = 1; INV._Inv = mat();
			return INV;
		}
//		Matrix LeftInv() {
//			
//		}
//		Matrix RightInv() {
//			
//		}

		Matrix GaussianElimination() {
			if (_CalG) return Matrix(_G);
			_det = 1;
			Matrix G = *this;
			for (int i=0;i<row();i++) { //pivot
			
				f MAX = abs(G.mat()[i][i]);
				int MAXj = i;
				for (int j=i+1;j<row();j++) if (abs(G.mat()[j][i]) > MAX) MAX = abs(G.mat()[j][i]), MAXj = j;
				if (MAXj != i) _det *= -1, swap(G._mat[i], G._mat[MAXj]);
				
				f fixA = G.mat()[i][i];
				if (!fixA) return _det = 0, G;
				
				for (int j=i+1;j<row();j++) { //process
					f fixB = G.mat()[j][i];
					for (int k=i;k<col();k++) G._mat[j][k] = fixA * G.mat()[j][k] - fixB * G.mat()[i][k]; //fix
					_det *= fixA;
				}
				
			}
			
			f tmp = _det;
			_det = 1;
			for (int i=row()-1;i>=0;i--) { //pivot
				f fixA = G.mat()[i][i];
				_det *= fixA;
				
				for (int j=i;j<col();j++) G._mat[i][j] /= fixA; //fix
				
				for (int j=0;j<i;j++) { //process
					f fixB = G.mat()[j][i];
					for (int k=i;k<col();k++) G._mat[j][k] -= fixB * G.mat()[i][k]; //fix
				}
			}
			
			_CalDet = 1; _det /= tmp;
			_CalG = 1; _G = G.mat();
			return G;
		} 
		
		
	private:
		bool _CalDet = 0, _CalT = 0, _CalG = 0, _CalInv = 0;
		int _row, _col;
		f _det;
		vector <vector <f> > _mat, _T, _G, _Inv;
};
