#include "CoordCube.h"
#include "CubieCube.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

 short CoordCube::N_TWIST = 2187; // 3^7 possible corner orientations
 short CoordCube::N_FLIP = 2048; // 2^11 possible edge flips
 short CoordCube::N_SLICE1 = 495;// 12 choose 4 possible positions of FR,FL,BL,BR edges
 short CoordCube::N_SLICE2 = 24;// 4! permutations of FR,FL,BL,BR edges in phase2
 short CoordCube::N_PARITY = 2; // 2 possible corner parities
 short CoordCube::N_URFtoDLF = 20160;// 8!/(8-6)! permutation of URF,UFL,ULB,UBR,DFR,DLF corners
 short CoordCube::N_FRtoBR = 11880; // 12!/(12-4)! permutation of FR,FL,BL,BR edges
 short CoordCube::N_URtoUL = 1320; // 12!/(12-3)! permutation of UR,UF,UL edges
 short CoordCube::N_UBtoDF = 1320; // 12!/(12-3)! permutation of UB,DR,DF edges
 short CoordCube::N_URtoDF = 20160; // 8!/(8-6)! permutation of UR,UF,UL,UB,DR,DF edges in phase2

 int CoordCube::N_URFtoDLB = 40320;// 8! permutations of the corners
 int CoordCube::N_URtoBR = 479001600;// 8! permutations of the corners

 short CoordCube::parityMove[2][18] = { { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 } };


 short CoordCube::N_MOVE = 18;
 short CoordCube::twistMove[2187][18] = { { 0 } };;
 short CoordCube::flipMove[2048][18] = { {0} };
 short CoordCube::FRtoBR_Move[11880][18] = { { 0 } };;
 char CoordCube::Slice_Flip_Prun[506880] = { 0 };
 char CoordCube::Slice_Twist_Prun[541283];
 short CoordCube::URFtoDLF_Move[20160][18] = { { 0 } };
 char CoordCube::Slice_URFtoDLF_Parity_Prun[483840] = { 0 };
 short CoordCube::URtoUL_Move[1320][18] = { { 0 } };
 short CoordCube::UBtoDF_Move[1320][18] = { { 0 } };
 short CoordCube::MergeURtoULandUBtoDF[336][336] = { { 0 } };
 char CoordCube::Slice_URtoDF_Parity_Prun[483840] = { 0 };
 short CoordCube::URtoDF_Move[20160][18] = { { 0 } };





CoordCube::CoordCube(CubieCube c)
{
	twist = c.getTwist();
	twist = c.getTwist();
	flip = c.getFlip();
	parity = c.cornerParity();
	FRtoBR = c.getFRtoBR();
	URFtoDLF = c.getURFtoDLF();
	URtoUL = c.getURtoUL();
	UBtoDF = c.getUBtoDF();
	URtoDF = c.getURtoDF();// only needed in phase2
	
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Move table for the twists of the corners
// twist < 2187 in phase 2.
// twist = 0 in phase 2.


   
void CoordCube::twistMoveMethod()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_TWIST; i++) {
		a.setTwist(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.cornerMultiply(CubieCube::moveCube[j]);
				twistMove[i][3 * j + k] = a.getTwist();
			}
			a.cornerMultiply(CubieCube::moveCube[j]);// 4. faceturn restores
													// a
		}
	}


}

void CoordCube::flipMoveMethod()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_FLIP; i++) {
		a.setFlip(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.edgeMultiply(CubieCube::moveCube[j]);
				flipMove[i][3 * j + k] = a.getFlip();
			}
			a.edgeMultiply(CubieCube::moveCube[j]);
			// a
		}
	}
}

void CoordCube::FRtoBRMethod()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_FRtoBR; i++) {
		a.setFRtoBR(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.edgeMultiply(CubieCube::moveCube[j]);
				FRtoBR_Move[i][3 * j + k] = a.getFRtoBR();
			}
			a.edgeMultiply(CubieCube::moveCube[j]);
		}
	}
}

void CoordCube::Slice_Flip_PrunMethod()
{
	
	
	for (int i = 0; i < N_SLICE1 * N_FLIP / 2; i++)
		Slice_Flip_Prun[i] = -1;
	int depth = 0;
	setPruning(Slice_Flip_Prun, 0, (char)0);
	int done = 1;
	while (done != N_SLICE1 * N_FLIP) {
		for (int i = 0; i < N_SLICE1 * N_FLIP; i++) {
			int flip = i / N_SLICE1, slice = i % N_SLICE1;
			if (getPruning(Slice_Flip_Prun, i) == depth) {
				for (int j = 0; j < 18; j++) {
					int newSlice = FRtoBR_Move[slice * 24][j] / 24;
					int newFlip = flipMove[flip][j];
					if (getPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice) == 0x0f) {
						setPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice, (char)(depth + 1));
						done++;
					}
				}
			}
			
		}
		depth++;
	}


}

void CoordCube::Slice_Twist_PrunMethod()
{
	for (int i = 0; i < N_SLICE1 * N_TWIST / 2 + 1; i++)
		Slice_Twist_Prun[i] = -1;
	int depth = 0;
	setPruning(Slice_Twist_Prun, 0, (char)0);
	int done = 1;
	while (done != N_SLICE1 * N_TWIST) {
		for (int i = 0; i < N_SLICE1 * N_TWIST; i++) {
			int twist = i / N_SLICE1, slice = i % N_SLICE1;
			if (getPruning(Slice_Twist_Prun, i) == depth) {
				for (int j = 0; j < 18; j++) {
					int newSlice = FRtoBR_Move[slice * 24][j] / 24;
					int newTwist = twistMove[twist][j];
					if (getPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice) == 0x0f) {
						setPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice, (char)(depth + 1));
						done++;
					}
				}
			}
		}
		depth++;
	}
}
void CoordCube::setPruning(char table[], int index, char value)
{
	if ((index & 1) == 0)
		table[index / 2] &= 0xf0 | value;
	else
		table[index / 2] &= 0x0f | (value << 4);
}

char CoordCube::getPruning(char table[], int index)
{

	if ((index & 1) == 0)
	{
		
		return (char)(table[index / 2] & 15);
	}
	else
		return (char)((table[index / 2] & 0xf0) >> 4);
}




void CoordCube::URFtoDLFMethod()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_URFtoDLF; i++) {
		a.setURFtoDLF(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.cornerMultiply(CubieCube::moveCube[j]);
				URFtoDLF_Move[i][3 * j + k] = a.getURFtoDLF();
			}
			a.cornerMultiply(CubieCube::moveCube[j]);
		}
	}
}


void CoordCube::parityMoveMethod()
{
	for (int i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY / 2; i++)
		Slice_URFtoDLF_Parity_Prun[i] = -1;
	int depth = 0;
	setPruning(Slice_URFtoDLF_Parity_Prun, 0, (char)0);
	int done = 1;
	while (done != N_SLICE2 * N_URFtoDLF * N_PARITY) {
		for (int i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY; i++) {
			int parity = i % 2;
			int URFtoDLF = (i / 2) / N_SLICE2;
			int slice = (i / 2) % N_SLICE2;
			if (getPruning(Slice_URFtoDLF_Parity_Prun, i) == depth) {
				for (int j = 0; j < 18; j++) {
					switch (j) {
					case 3:
					case 5:
					case 6:
					case 8:
					case 12:
					case 14:
					case 15:
					case 17:
						continue;
					default:
						int newSlice = FRtoBR_Move[slice][j];
						int newURFtoDLF = URFtoDLF_Move[URFtoDLF][j];
						int newParity = parityMove[parity][j];
						if (getPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity) == 0x0f) {
							setPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity,
								(char)(depth + 1));
							done++;
						}
					}
				}
			}
		}
		depth++;
	}
}

void CoordCube::URtoUL_Method()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_URtoUL; i++) {
		a.setURtoUL(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.edgeMultiply(CubieCube::moveCube[j]);
				URtoUL_Move[i][3 * j + k] = a.getURtoUL();
			}
			a.edgeMultiply(CubieCube::moveCube[j]);
		}
	}
}

void CoordCube::UBtoDF_Method()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_UBtoDF; i++) {
		a.setUBtoDF(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.edgeMultiply(CubieCube::moveCube[j]);
				UBtoDF_Move[i][3 * j + k] = a.getUBtoDF();
			}
			a.edgeMultiply(CubieCube::moveCube[j]);
		}
	}
}
void CoordCube::URtoDF_Move_Method()
{
	CubieCube a = CubieCube();
	for (short i = 0; i < N_URtoDF; i++) {
		a.setURtoDF(i);
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				a.edgeMultiply(CubieCube::moveCube[j]);
				URtoDF_Move[i][3 * j + k] = (short)a.getURtoDF();
				// Table values are only valid for phase 2 moves!
				// For phase 1 moves, casting to short is not possible.
			}
			a.edgeMultiply(CubieCube::moveCube[j]);
		}
	}
}
void CoordCube::move(int m)
{
	twist = twistMove[twist][m];
	flip = flipMove[flip][m];
	parity = parityMove[parity][m];
	FRtoBR = FRtoBR_Move[FRtoBR][m];
	URFtoDLF = URFtoDLF_Move[URFtoDLF][m];
	URtoUL = URtoUL_Move[URtoUL][m];
	UBtoDF = UBtoDF_Move[UBtoDF][m];
	if (URtoUL < 336 && UBtoDF < 336)// updated only if UR,UF,UL,UB,DR,DF
									 // are not in UD-slice
		URtoDF = MergeURtoULandUBtoDF[URtoUL][UBtoDF];
}
void CoordCube::MergeURtoULandUBtoDFMethod()
{
	// for i, j <336 the six edges UR,UF,UL,UB,DR,DF are not in the
	// UD-slice and the index is <20160
	for (short uRtoUL = 0; uRtoUL < 336; uRtoUL++) {
		for (short uBtoDF = 0; uBtoDF < 336; uBtoDF++) {
			MergeURtoULandUBtoDF[uRtoUL][uBtoDF] = (short)CubieCube::getURtoDF(uRtoUL, uBtoDF);
		}
	}
}

void CoordCube::Slice_URtoDF_Parity_Prun_Method()
{
	for (int i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY / 2; i++)
		Slice_URtoDF_Parity_Prun[i] = -1;
	int depth = 0;
	setPruning(Slice_URtoDF_Parity_Prun, 0, (char)0);
	int done = 1;
	while (done != N_SLICE2 * N_URtoDF * N_PARITY) {
		for (int i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY; i++) {
			int parity = i % 2;
			int URtoDF = (i / 2) / N_SLICE2;
			int slice = (i / 2) % N_SLICE2;
			if (getPruning(Slice_URtoDF_Parity_Prun, i) == depth) {
				for (int j = 0; j < 18; j++) {
					switch (j) {
					case 3:
					case 5:
					case 6:
					case 8:
					case 12:
					case 14:
					case 15:
					case 17:
						continue;
					default:
						int newSlice = FRtoBR_Move[slice][j];
			
						int newURtoDF = URtoDF_Move[URtoDF][j];
						int newParity = parityMove[parity][j];
						if (getPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity) == 0x0f) {
							setPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity,
								(char)(depth + 1));
							done++;
						}
					}
				}
			}
		}
		depth++;
	}
}