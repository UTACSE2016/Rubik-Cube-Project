#pragma once
#ifndef COORDCUBE_H
#define COORDCUBE_H
#include "CubieCube.h"
#include <stdint.h>
class CoordCube
	
{
public:

	static short N_TWIST; // 3^7 possible corner orientations
	static short N_FLIP; // 2^11 possible edge flips
	static short N_SLICE1;// 12 choose 4 possible positions of FR,FL,BL,BR edges
	static short N_SLICE2;// 4! permutations of FR,FL,BL,BR edges in phase2
	static short N_PARITY; // 2 possible corner parities
	static short N_URFtoDLF;// 8!/(8-6)! permutation of URF,UFL,ULB,UBR,DFR,DLF corners
	static short N_FRtoBR; // 12!/(12-4)! permutation of FR,FL,BL,BR edges
	static short N_URtoUL; // 12!/(12-3)! permutation of UR,UF,UL edges
	static short N_UBtoDF; // 12!/(12-3)! permutation of UB,DR,DF edges
	static short N_URtoDF; // 8!/(8-6)! permutation of UR,UF,UL,UB,DR,DF edges in phase2

	static int N_URFtoDLB;// 8! permutations of the corners
	static int N_URtoBR;// 8! permutations of the corners

	static short N_MOVE;

	// All coordinates are 0 for a solved cube except for UBtoDF, which is 114
	short twist;
	short flip;
	short parity;
	short FRtoBR;
	short URFtoDLF;
	short URtoUL;
	short UBtoDF;
	int URtoDF;
	
	static short twistMove[2187][18];
	static void twistMoveMethod();
	static short flipMove [2048][18];
	static void flipMoveMethod();
	static short FRtoBR_Move[11880][18];
	static void FRtoBRMethod();
	static char Slice_Flip_Prun[506880];
	static void Slice_Flip_PrunMethod();
	static void setPruning(char table[], int index, char value);
	static char getPruning(char table[], int index);
	static char Slice_Twist_Prun[541283];
	static void Slice_Twist_PrunMethod();
	static short URFtoDLF_Move[20160][18];
	static void URFtoDLFMethod();

	static char Slice_URFtoDLF_Parity_Prun[483840];

	static short parityMove[2][18];
	static void parityMoveMethod();

	static short URtoUL_Move[1320][18];
	static void URtoUL_Method();

	static short UBtoDF_Move[1320][18];
	static void UBtoDF_Method();

	static short MergeURtoULandUBtoDF[336][336];
	static void MergeURtoULandUBtoDFMethod();

	static char Slice_URtoDF_Parity_Prun[483840];
	static void Slice_URtoDF_Parity_Prun_Method();

	static short URtoDF_Move[20160][18];
	static void URtoDF_Move_Method();
	
	void move(int m);

	CoordCube(CubieCube c);





};

#endif