#include <stdio.h>
#include <limits.h>

#define MAX 100

enum v {
	A, B , C, D, E, F
};

int n;
int weight[MAX][MAX];
int vertex[MAX];

void init() {
	int i, j;

	for(i=0; i < n; i++) {
		for(j = 0; j < n; j++) {
			weight[i][j] = INT_MAX;
		}
		vertex[i] = INT_MAX;
	}
}

void edge_relexation() {

}

int check_negative_cycle() {
	return 0;
}

void print_graph() {
	
}

int main (void) {
	int i, ret;
	n = 6;

	init();

	// init edge weight
	// A = 0, B = 1, C = 2, D = 3, E = 4, F = 5
	weight[v.A][v.B] = 8;
	weight[v.A][v.C] = -2;
	weight[v.A][v.D] = 4;
	weight[v.B][v.E] = -2;
	weight[v.C][v.B] = 7;
	weight[v.C][v.E] = 3;
	weight[v.C][v.D] = 1;
	weight[v.F][v.C] = 9;
	weight[v.D][v.F] = 5;

	// edge-relexation 1 time for start vertex
	// start vertex : A
	for(i=0, i < n; i++)
		vertex[i] = vertex[i] > weight[v.A][i] ? weight[v.A][i]:vertex[i];

	// edge-relexation (v-1)*e times
	edge_relexation();

	// check negative cycle
	if(check_negative_cycle() < 0)
		printf("There is a negative cycle\n");
	else
		printf("All Succesfully done\n");

	print_graph();

	return 0;
}