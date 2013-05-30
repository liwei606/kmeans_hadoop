#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

const int max_iter = 15;
const double damp = 0.85;

const int k = 4;			// number of centers
const int dim = 2;			// dimension
const int n = 20;			// number of data points
double p[n][dim];			// data points
double ctr[k][dim];			// centroid of each cluster
int cluster[n];				// the cluster number each point belongs to
double distoration[k];
double dis[n][k];
int count[k];

int iteration = 0;

double total_distoration;
double best_distoration = 10;
int best_cluster[n];

void cal_dis() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			dis[i][j] = 0;
			for (int d = 0; d < dim; ++d) {
				dis[i][j] += (p[i][dim] - ctr[j][dim]) * (p[i][dim] - ctr[j][dim]);
			}
			dis[i][j] = sqrt(dis[i][j]);
			//cout << "dis: [" << i << "][" << j << "]: " << dis[i][j] << endl;
		}
	}
}

void assign_cluster() {
	for (int i = 0; i < n; ++i) {
		double d = dis[i][0];
		cluster[i] = 0;
		for (int j = 1; j < k; ++j) {
			if (dis[i][j] < d) {
				d = dis[i][j];
				cluster[i] = j;
			}
		}
		//cout << "cluster for point " << i << " : " << cluster[i] << endl;
	}
}

void invalidate_distoration() {
	for (int i = 0; i < k; ++i) {
		distoration[i] = 0;
	}
}

void validate_distoration() {
	total_distoration = 0;
	for (int i = 0; i < k; ++i) {
		distoration[i] = sqrt(distoration[i]);
		total_distoration += distoration[i];
		//cout << "distoration " << i << ": " << distoration[i] << endl;
	}
	//cout << "Total distoration: " << total_distoration << endl;
}

void compute_distoration() {
	invalidate_distoration();
	for (int i = 0; i < n; ++i) {
		int c = cluster[i];
		for (int d = 0; d < dim; ++d) {
			distoration[c] += dis[i][c] * dis[i][c];
		}
	}
	validate_distoration();
}

void update_centroid() {
	double sum[k][dim];
	memset(sum, 0, k * dim * sizeof(double));
	memset(count, 0, k * sizeof(int));
	//__asm__();
	for (int i = 0; i < n; ++i) {
		int c = cluster[i];
		count[c]++;
		for (int d = 0; d < dim; ++d) {
			sum[c][d] += p[i][d];
		}
	}
	for (int i = 0; i < k; ++i) {
		//cout << "centroid " << i << " : ";
		for (int d = 0; d < dim; ++d) {
			if (count[i]) ctr[i][d] = ctr[i][d] * (1 - damp) + damp * sum[i][d] / double(count[i]);
			else ctr[i][d] = p[i][d];
			//cout << ctr[i][d] << "\t";
		}
		//cout << endl;
	}
	//__asm__();
}

void kmeans() {
	for (iteration = 0; iteration < max_iter; ++iteration) {
		//cout << "Iteration: " << iteration << endl;
		cal_dis();
	
		// assign point to each cluster
		assign_cluster();
		compute_distoration();
	
		// update cluster centroid
		update_centroid();
		bool contain0cluster = false;
		if (total_distoration <= best_distoration) {
			for (int i = 0; i < k; ++i) {
				if (count[i] == 0) contain0cluster = true;
			}
			if (!contain0cluster) {
				best_distoration = total_distoration;
				for (int i = 0; i < n; ++i) {
					best_cluster[i] = cluster[i];
				}
			}
		}
	}
	
}
    
int main(int argc, char **argv)
{
	freopen("data_pts.txt", "r", stdin);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < dim; ++j)
			cin >> p[i][j];
	}
	fclose(stdin);
	
	// center initialization
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < dim; ++j)
			ctr[i][j] = p[i*k][j];
	}
	
	freopen("output.txt", "w", stdout);
	
	kmeans();
	//cout << " =============================================== " << endl;
	cout << "Average Distoration: " << best_distoration / 4.0 << endl;
	for (int i = 0; i < n; ++i) {
		cout << "Points: " << i << " in cluster: " << best_cluster[i] + 1 << endl;
	}
	fclose(stdout);
}
