#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double d[8];
double validate = 0.999645;

int main() {
	freopen("distoration_all.txt", "r", stdin);
	freopen("kmeans_er.txt", "w", stdout);
	double error;
	for (int i = 0; i < 8; ++i) {
		cin >> d[i];
		error = (d[i] - validate) / validate;
		if (error < 0) error = 0;
		cout << error << endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
