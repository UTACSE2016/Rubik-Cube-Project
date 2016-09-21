#include <iostream>
#include <string>
#include <sstream>
#include "Search.h"
#include "CoordCube.h"
#include <ctime>
using namespace std;



int main()
{

	CoordCube::twistMoveMethod();
	CoordCube::flipMoveMethod();
	CoordCube::FRtoBRMethod();
	CoordCube::URFtoDLFMethod();
	CoordCube::URtoDF_Move_Method();
	CoordCube::URtoUL_Method();
	CoordCube::UBtoDF_Method();
	CoordCube::MergeURtoULandUBtoDFMethod();
	CoordCube::parityMoveMethod(); // Slice_URFtoDRF
	CoordCube::Slice_URtoDF_Parity_Prun_Method();
	CoordCube::Slice_Flip_PrunMethod();
	CoordCube::Slice_Twist_PrunMethod();
	

	string cubeString;
	string solution;

	//cout << "Hello, enter cube orientation: ";
	//getline(cin, cubeString);
	cubeString = "BRDFULRDBLURBRLFRBBLDFFLUBURDLRDDFFLRDDBLULUFFBUFBUURD";

	clock_t begin = clock();
	solution = Search::solution(cubeString);
	cout << solution << endl;
	clock_t end = clock();
	
	
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Total Elapsed Time: (" << elapsed_secs << " secs)" << endl;

	cout << Search::phase2;

	/*
	begin = clock();
	solution = Search::solution(cubeString);
	cout << solution << endl;
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Second Pass Total Elapsed Time: (" << elapsed_secs << " secs)" << endl;
	*/
	getchar();

	
}