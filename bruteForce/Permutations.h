#pragma once
#include "cubeDefs.h"

class Permutations
{
public:

	Color currentState[54] = {U,U,U,U,U,U,U,U,U,R,R,R,R,R,R,R,R,R,F,F,F,F,F,F,F,F,F,D,D,D,D,D,D,D,D,D,L,L,L,L,L,L,L,L,L,B,B,B,B,B,B,B,B,B};
	Moves previousMove;

	// Functions:
	static void applyMove(int moveType,Color currentState[]);
	void printCurrentState();


};

