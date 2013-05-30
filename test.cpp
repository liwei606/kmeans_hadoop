#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int k = 4;
const int d = 2;
double sum[k][d];

int main() {
	memset(sum, 0, k * d * sizeof(double));
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < d; ++j) {
			cout << "sum[" << i << "][" << j << "]: " << sum[i][j] << endl;
		}
	}
	return 0;
}
