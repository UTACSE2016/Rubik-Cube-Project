#ifndef SEARCH_H
#define SEARCH_H

#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Search
{
public:

	static int ax[31];
	static int po[31];
	static int flip[31]; // phase1 coordinates
	static int twist[31];
	static int slice[31];

	static	int parity[31]; // phase2 coordinates
	static int URFtoDLF[31];
	static	int FRtoBR[31];
	static	int URtoUL[31];
	static	int UBtoDF[31];
	static	int URtoDF[31];

	static int minDistPhase1[31]; // IDA* distance do goal estimations
	static int minDistPhase2[31];

	static int phase2;
	static string solutionToString(int length, int depthPhase1);
	static string solutionToString(int length);
	static string solution(string cubeString);
	static int totalDepth(int depthPhase1, int maxDepth);
};
#endif