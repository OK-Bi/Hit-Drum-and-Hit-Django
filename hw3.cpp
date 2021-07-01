#include <iostream>
#include <fstream>
using namespace std;

string xstr, ystr;
int M[101][101] = { 0, };
int P[101][101] = { 0, };
int penalty;
char xout[101], yout[101];



void opt(int m, int n) {
	// 초기값 설정 
	for (int i = 0; i <= m; i++)
		M[i][0] = 3 * i;
	for (int j = 1; j <= n; j++)
		M[0][j] = 3 * j;
	int a, b, c;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) { 
			if (xstr[i-1] == ystr[j-1])  // 문자열의 배열은 0부터 시작하므로 조정 
				penalty = 0;
			else
				penalty = 2;
			a = M[i - 1][j - 1] + penalty;
			b = M[i - 1][j] + 3; // gap penalty
			c = M[i][j - 1] + 3; //gap penalty
			
			M[i][j] = min(min(a,b),c );
			if (M[i][j] == a)
				P[i][j] = 1;
			else if (M[i][j] == b)
				P[i][j] = 2;
			else
				P[i][j] = 3;

		}

	}
}

void align(int m, int n) {
	int p = 101; //더 긴 문장에 맞춰야함 
	int i = m , j = n;
	for (int k = 1; k <= p; k++) {
		switch (P[i][j]){
			case 1: 
				xout[p- k] = xstr[i-1]; 
				yout[p - k] = ystr[j-1];
				i--;j--;
				break;
			case 2: 
				xout[p - k] = xstr[i-1];
				yout[p - k] = '-';
				i--;
				break;
			case 3: 
				xout[p - k] = '-';
				yout[p - k] = ystr[j-1];
				j--;
				break;
		}
	}
}

int main() {
	ifstream myfile;
	myfile.open("input.txt");
	int data; 
	int lenX, lenY;
	
	myfile >> data;
	for (int iter = 0; iter < data; iter++) {
		myfile >> lenX>> xstr;  
		myfile >> lenY >> ystr;
		for (int i = 0; i < 101; i++) {
			xout[i] = yout[i] = '*';
		}

		opt(lenX, lenY);
		align(lenX, lenY);
		

		for (int k = 0; k < 101; k++) {
			if (xout[k] == '*')
				continue;
			cout << xout[k];
		}
		cout << endl;
		for (int k = 0; k < 101; k++) {
			if (yout[k] == '*')
				continue;
			cout << yout[k];
		}

		cout << endl;

		for (int i = 0; i <= lenX; i++) {
			for (int j = 0; j <= lenY; j++) {
				cout << M[i][j] << "\t";
			}
			cout << endl;
		}
	}

}