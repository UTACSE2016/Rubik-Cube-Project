#pragma once
#ifndef CUBIECUBE_H
#define CUBIECUBE_H
#include "cubeDefs.h"
#include <stdint.h>
#include <vector>



class CubieCube
{
public:
	
	//************ Initialize to Id-Cube *******************
	// corner permutations
	Corner cp[8] = { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB };

	char co[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	
	Edge ep[12] = { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR };

	char eo[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//************ Moves on the cubie level *******************
	static Corner cpU[8];

	static char coU[8];

	static Edge epU[12];
	static char eoU[12];

	static Corner cpR[8];
	static char coR[8];
	static Edge epR[12];
	static char eoR[12];

	static Corner cpF[8];
	static char coF[8];
	static Edge epF[12];
	static char eoF[12];

	static Corner cpD[8];
	static char coD[8];
	static Edge epD[12];
	static char eoD[12];

	static Corner cpL[8];
	static char coL[8];
	static Edge epL[12];
	static char eoL[12];

	static Corner cpB[8];
	static char coB[8];
	static Edge epB[12];
	static char eoB[12];

	// This CubieCube array represents the 6 basic cube moves
	
	static vector<CubieCube> moveCube;	


	CubieCube();
	
	
	
	static vector<CubieCube> setupMoveCube();



	short getTwist(); // return the twist of the 8 corners. 0 <= twist < 3^7
	short getFlip();  // return the flip of the 12 edges. 0<= flip < 2^11
	short cornerParity(); // Parity of the corner permutation
	short getFRtoBR(); 	// permutation of the UD-slice edges FR,FL,BL and BR
	int Cnk(int n, int k);
	short getURFtoDLF();
	static void rotateLeft(Edge arr[], int l, int r);
	static void rotateLeft(Corner arr[], int l, int r);
	short getURtoUL();
	short getUBtoDF();
	void setURtoDF(int idx);
	void rotateRight(Edge arr[], int l, int r);
	static int getURtoDF(short idx1, short idx2);
	int getURtoDF();
	void setTwist(short twist);
	void cornerMultiply(CubieCube b);
	void setFlip(short flip);
	void edgeMultiply(CubieCube b);
	void setFRtoBR(short idx);
	void setURFtoDLF(short idx);
	static void rotateRight(Corner arr[], int l, int r);
	void setURtoUL(short idx);
	void setUBtoDF(short idx);
	int verify();
	short edgeParity();
};

#endif