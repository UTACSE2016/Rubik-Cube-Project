#include <iostream>
#include <string>
#include <sstream>
#include "Search.h"
#include <vector>
#include "cubeDefs.h"
#include "Permutations.h"
#include <time.h>

#define PRUNETABLEDEPTH 1
#define DEPTH5BRANCHES 12
using namespace std;



int main()
{

	int depth = 1;
	int max_depth = 5;
	int parent_index;


	vector< vector<Permutations> > vec;
	vector<Permutations> temp;

	Permutations root;
	temp.push_back(root);
	vec.push_back(temp);

	
	clock_t begin = clock();
	// Building Pruning Table
	for (depth; depth <= max_depth; depth++)
	{
		vector<Permutations> temp;
			for (int j = 0; j < pow(12,depth); j++) {
			Permutations pTemp;
			parent_index = j / 12;
			memcpy(&pTemp.currentState, vec[depth-1][parent_index].currentState, 54 * sizeof(Color));
			Permutations::applyMove(j, pTemp.currentState);
			temp.push_back(pTemp);
		}
		vec.push_back(temp);	
	}
	clock_t end = clock();
	
	
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Total Elapsed Time: (" << elapsed_secs << " secs)" << endl;

	
	cout << sizeof(Permutations);
	


	getchar();
}

