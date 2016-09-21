#include "CubieCube.h"
#include "cubeDefs.h"
#include <stdint.h>
#include <vector>



Corner CubieCube::cpU[8] = { UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB };
char CubieCube::coU[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
Edge CubieCube::epU[12] = { UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR };
char CubieCube::eoU[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

Corner CubieCube::cpR[8] = { DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR };
char CubieCube::coR[8] = { 2, 0, 0, 1, 1, 0, 0, 2 };
Edge CubieCube::epR[12] = { FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR };
char CubieCube::eoR[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

Corner CubieCube::cpF[8] = { UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB };
char CubieCube::coF[8] = { 1, 2, 0, 0, 2, 1, 0, 0 };
Edge CubieCube::epF[12] = { UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR };
char CubieCube::eoF[12] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 };

Corner CubieCube::cpD[8] = { URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR };
char CubieCube::coD[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
Edge CubieCube::epD[12] = { UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR };
char CubieCube::eoD[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

Corner CubieCube::cpL[8] = { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB };
char CubieCube::coL[8] = { 0, 1, 2, 0, 0, 2, 1, 0 };
Edge CubieCube::epL[12] = { UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR };
char CubieCube::eoL[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

Corner CubieCube::cpB[8] = { URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL };
char CubieCube::coB[8] = { 0, 0, 1, 2, 0, 0, 2, 1 };
Edge CubieCube::epB[12] = { UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB };
char CubieCube::eoB[12] = { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 };

vector<CubieCube> CubieCube::moveCube = CubieCube::setupMoveCube();



CubieCube::CubieCube()
{
	
	
}

void CubieCube::setFlip(short flip) {
	int flipParity = 0;
	for (int i = BR - 1; i >= UR; i--) {
		flipParity += eo[i] = (char)(flip % 2);
		flip /= 2;
	}
	eo[BR] = (char)((2 - flipParity % 2) % 2);
}

void CubieCube::edgeMultiply(CubieCube b) {
	Edge ePerm[12];
	char eOri[12];
	for (int i = 0; i < BR + 1; i++) {
		ePerm[i] = ep[b.ep[i]];
		eOri[i] = (char)((b.eo[i] + eo[b.ep[i]]) % 2);
	}
	for (int i = 0; i < BR + 1; i++) {
		ep[i] = ePerm[i];
		eo[i] = eOri[i];
	}
}


void CubieCube::setFRtoBR(short idx) {
	int x;
	Edge sliceEdge[4] = { FR, FL, BL, BR };
	Edge otherEdge[8] = { UR, UF, UL, UB, DR, DF, DL, DB };
	int b = idx % 24; // Permutation
	int a = idx / 24; // Combination
	for (int i = 0; i < BR + 1; i++)
		ep[i] = DB;// Use UR to invalidate all edges

	for (int j = 1, k; j < 4; j++)// generate permutation from index b
	{
		k = b % (j + 1);
		b /= j + 1;
		while (k-- > 0)
			rotateRight(sliceEdge, 0, j);
	}

	x = 3;// generate combination and set slice edges
	for (int j = UR; j <= BR; j++)
		if (a - Cnk(11 - j, x + 1) >= 0) {
			ep[j] = sliceEdge[3 - x];
			a -= Cnk(11 - j, x-- + 1);
		}
	x = 0; // set the remaining edges UR..DB
	for (int j = UR; j <= BR; j++)
		if (ep[j] == DB)
			ep[j] = otherEdge[x++];
}

short CubieCube::getTwist()
{
	short ret = 0;
	for (int i = URF; i < DRB; i++)
		ret = (short)(3 * ret + co[i]);
	return ret;
}

short CubieCube::getFlip()
{
	short ret = 0;
	for (int i = UR; i < BR; i++)
		ret = (short)(2 * ret + eo[i]);
	return ret;
}

short CubieCube::cornerParity()
{
	int s = 0;
	for (int i = DRB; i >= URF + 1; i--)
		for (int j = i - 1; j >= URF; j--)
			if (cp[j] > cp[i])
				s++;
	return (short)(s % 2);
}

int CubieCube::Cnk(int n, int k)
{
	int i, j, s;
	if (n < k)
		return 0;
	if (k > n / 2)
		k = n - k;
	for (s = 1, i = n, j = 1; i != n - k; i--, j++) {
		s *= i;
		s /= j;
	}
	return s;
}



void CubieCube::rotateLeft(Edge arr[], int l, int r)
{
	Edge temp = arr[l];
	for (int i = l; i < r; i++)
		arr[i] = arr[i + 1];
	arr[r] = temp;
}



short CubieCube::getFRtoBR()
{
	int a = 0, x = 0;
	Edge edge4[4];
	// compute the index a < (12 choose 4) and the permutation array perm.
	for (int j = BR; j >= UR; j--)
		if (FR <= ep[j] && ep[j] <= BR) {
			a += Cnk(11 - j, x + 1);
			edge4[3 - x++] = ep[j];
		}

	int b = 0;
	for (int j = 3; j > 0; j--)// compute the index b < 4! for the
							   // permutation in perm
	{
		int k = 0;
		while (edge4[j]!= j + 8) {
			rotateLeft(edge4, 0, j);
			k++;
		}
		b = (j + 1) * b + k;
	}
	return (short)(24 * a + b);
}


void CubieCube::rotateLeft(Corner arr[], int l, int r)
// Left rotation of all array elements between l and r
{
	Corner temp = arr[l];
	for (int i = l; i < r; i++)
		arr[i] = arr[i + 1];
	arr[r] = temp;
}


short CubieCube::getURFtoDLF()
{
	// Permutation of all corners except DBL and DRB
	int a = 0, x = 0;
	Corner corner6[6];
	// compute the index a < (8 choose 6) and the corner permutation.
	for (int j = URF; j <= DRB; j++)
		if (cp[j] <= DLF) {
			a += Cnk(j, x + 1);
			corner6[x++] = cp[j];
		}

	int b = 0;
	for (int j = 5; j > 0; j--)// compute the index b < 6! for the
							   // permutation in corner6
	{
		int k = 0;
		while (corner6[j]!= j) {
			rotateLeft(corner6, 0, j);
			k++;
		}
		b = (j + 1) * b + k;
	}
	return (short)(720 * a + b);
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Multiply this CubieCube with another cubiecube b, restricted to the corners.<br>
// Because we also describe reflections of the whole cube by permutations, we get a complication with the corners. The
// orientations of mirrored corners are described by the numbers 3, 4 and 5. The composition of the orientations
// cannot
// be computed by addition modulo three in the cyclic group C3 any more. Instead the rules below give an addition in
// the dihedral group D3 with 6 elements.<br>
//	 
// NOTE: Because we do not use symmetry reductions and hence no mirrored cubes in this simple implementation of the
// Two-Phase-Algorithm, some code is not necessary here.
//	
void CubieCube::cornerMultiply(CubieCube b) {
	Corner cPerm[8];
	char cOri[8];
	
	for (int i = 0; i < DRB + 1; i++) {
		cPerm[i] = cp[b.cp[i]];

		char oriA = co[b.cp[i]];
		char oriB = b.co[i];
		char ori = 0;
		;
		if (oriA < 3 && oriB < 3) // if both cubes are regular cubes...
		{
			ori = (char)(oriA + oriB); // just do an addition modulo 3 here
			if (ori >= 3)
				ori -= 3; // the composition is a regular cube

						  // +++++++++++++++++++++not used in this implementation +++++++++++++++++++++++++++++++++++
		}
		else if (oriA < 3 && oriB >= 3) // if cube b is in a mirrored
										// state...
		{
			ori = (char)(oriA + oriB);
			if (ori >= 6)
				ori -= 3; // the composition is a mirrored cube
		}
		else if (oriA >= 3 && oriB < 3) // if cube a is an a mirrored
										// state...
		{
			ori = (char)(oriA - oriB);
			if (ori < 3)
				ori += 3; // the composition is a mirrored cube
		}
		else if (oriA >= 3 && oriB >= 3) // if both cubes are in mirrored
										 // states...
		{
			ori = (char)(oriA - oriB);
			if (ori < 0)
				ori += 3; // the composition is a regular cube
						  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
		cOri[i] = ori;
	}
	for (int i = 0; i < DRB + 1; i++) {
		cp[i] = cPerm[i];
		co[i] = cOri[i];
	}
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CubieCube::setTwist(short twist) {
	int twistParity = 0;
	for (int i = DRB - 1; i >= URF; i--) {
		twistParity += co[i] = (char)(twist % 3);
		twist /= 3;
	}
	co[DRB] = (char)((3 - twistParity % 3) % 3);
}

short CubieCube::getURtoUL() {
	int a = 0, x = 0;
	Edge edge3[3];
	// compute the index a < (12 choose 3) and the edge permutation.
	for (int j = UR; j <= BR; j++)
		if (ep[j] <= UL) {
			a += Cnk(j, x + 1);
			edge3[x++] = ep[j];
		}

	int b = 0;
	for (int j = 2; j > 0; j--)// compute the index b < 3! for the
							   // permutation in edge3
	{
		int k = 0;
		while (edge3[j]!= j) {
			rotateLeft(edge3, 0, j);
			k++;
		}
		b = (j + 1) * b + k;
	}
	return (short)(6 * a + b);
}


// Permutation of the three edges UB,DR,DF
short CubieCube::getUBtoDF() {
	int a = 0, x = 0;
	Edge edge3[3];
	// compute the index a < (12 choose 3) and the edge permutation.
	for (int j = UR; j <= BR; j++)
		if (UB <= ep[j] && ep[j] <= DF) {
			a += Cnk(j, x + 1);
			edge3[x++] = ep[j];
		}

	int b = 0;
	for (int j = 2; j > 0; j--)// compute the index b < 3! for the
							   // permutation in edge3
	{
		int k = 0;
		while (edge3[j]!= UB + j) {
			rotateLeft(edge3, 0, j);
			k++;
		}
		b = (j + 1) * b + k;
	}
	return (short)(6 * a + b);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CubieCube::rotateRight(Edge arr[], int l, int r)
// Right rotation of all array elements between l and r
{
	Edge temp = arr[r];
	for (int i = r; i > l; i--)
		arr[i] = arr[i - 1];
	arr[l] = temp;
}

int CubieCube::getURtoDF()
{
	int a = 0, x = 0;
	Edge edge6[6];
	// compute the index a < (12 choose 6) and the edge permutation.
	for (int j = UR; j <= BR; j++)
		if (ep[j] <= DF) {
			a += Cnk(j, x + 1);
			edge6[x++] = ep[j];
		}

	int b = 0;
	for (int j = 5; j > 0; j--)// compute the index b < 6! for the
							   // permutation in edge6
	{
		int k = 0;
		while (edge6[j] != j) {
			rotateLeft(edge6, 0, j);
			k++;
		}
		b = (j + 1) * b + k;
	}
	return 720 * a + b;
}



int CubieCube::getURtoDF(short idx1, short idx2) {
	CubieCube a = CubieCube();
	CubieCube b = CubieCube();
	a.setURtoUL(idx1);
	b.setUBtoDF(idx2);
	for (int i = 0; i < 8; i++) {
		if (a.ep[i] != BR)
			if (b.ep[i] != BR)// collision
				return -1;
			else
				b.ep[i] = a.ep[i];
	}
	return b.getURtoDF();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CubieCube::setURtoDF(int idx) {
	int x;
	Edge edge6[12] = { UR, UF, UL, UB, DR, DF };
	Edge otherEdge[12] = { DL, DB, FR, FL, BL, BR };
	int b = idx % 720; // Permutation
	int a = idx / 720; // Combination
	for (int i = 0; i < BR + 1; i++)
	{
		ep[i] = BR;// Use BR to invalidate all edges
	}
		

	for (int j = 1, k; j < 6; j++)// generate permutation from index b
	{
		k = b % (j + 1);
		b /= j + 1;
		while (k-- > 0)
			rotateRight(edge6, 0, j);
	}
	x = 5;// generate combination and set edges
	for (int j = BR; j >= 0; j--)
		if (a - Cnk(j, x + 1) >= 0) {
			ep[j] = edge6[x];
			a -= Cnk(j, x-- + 1);
		}
	x = 0; // set the remaining edges DL..BR
	for (int j = UR; j <= BR; j++)
		if (ep[j] == BR)
			ep[j] = otherEdge[x++];
}

vector<CubieCube> CubieCube::setupMoveCube()
{
	vector<CubieCube> moveCube;
	
	//***** CUBE 1******
	CubieCube cube1 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube1.cp[i] = cube1.cpU[i];
		cube1.co[i] = cube1.coU[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube1.ep[i] = cube1.epU[i];
		cube1.eo[i] = cube1.eoU[i];
	}

	moveCube.push_back(cube1);


	//***** CUBE 2******
	CubieCube cube2 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube2.cp[i] = cube2.cpR[i];
		cube2.co[i] = cube2.coR[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube2.ep[i] = cube2.epR[i];
		cube2.eo[i] = cube2.eoR[i];
	}

	moveCube.push_back(cube2);

	//***** CUBE 3******
	CubieCube cube3 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube3.cp[i] = cube3.cpF[i];
		cube3.co[i] = cube3.coF[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube3.ep[i] = cube3.epF[i];
		cube3.eo[i] = cube3.eoF[i];
	}
	moveCube.push_back(cube3);

	//***** CUBE 4******
	CubieCube cube4 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube4.cp[i] = cube4.cpD[i];
		cube4.co[i] = cube4.coD[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube4.ep[i] = cube4.epD[i];
		cube4.eo[i] = cube4.eoD[i];
	}
	moveCube.push_back(cube4);

	//***** CUBE 5******
	CubieCube cube5 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube5.cp[i] = cube5.cpL[i];
		cube5.co[i] = cube5.coL[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube5.ep[i] = cube5.epL[i];
		cube5.eo[i] = cube5.eoL[i];
	}
	moveCube.push_back(cube5);
	//***** CUBE 6******
	CubieCube cube6 = CubieCube();
	for (int i = 0; i < 8; i++)
	{
		cube6.cp[i] = cube6.cpB[i];
		cube6.co[i] = cube6.coB[i];
	}
	for (int i = 0; i < 12; i++)
	{
		cube6.ep[i] = cube6.epB[i];
		cube6.eo[i] = cube6.eoB[i];
	}
	moveCube.push_back(cube6);

	return moveCube;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CubieCube::setURtoUL(short idx) {
	int x;
	Edge edge3[3] = { UR, UF, UL };
	int b = idx % 6; // Permutation
	int a = idx / 6; // Combination
	for (int i = 0; i < BR+1 ; i++)
		ep[i] = BR;// Use BR to invalidate all edges

	for (int j = 1, k; j < 3; j++)// generate permutation from index b
	{
		k = b % (j + 1);
		b /= j + 1;
		while (k-- > 0)
			rotateRight(edge3, 0, j);
	}
	x = 2;// generate combination and set edges
	for (int j = BR; j >= 0; j--)
		if (a - Cnk(j, x + 1) >= 0) {
			ep[j] = edge3[x];
			a -= Cnk(j, x-- + 1);
		}
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CubieCube::setUBtoDF(short idx) {
	int x;
	Edge edge3[] = { UB, DR, DF };
	int b = idx % 6; // Permutation
	int a = idx / 6; // Combination
	for (int i = 0; i < BR + 1; i++)
		ep[i] = BR;// Use BR to invalidate all edges

	for (int j = 1, k; j < 3; j++)// generate permutation from index b
	{
		k = b % (j + 1);
		b /= j + 1;
		while (k-- > 0)
			rotateRight(edge3, 0, j);
	}
	x = 2;// generate combination and set edges
	for (int j = BR; j >= 0; j--)
		if (a - Cnk(j, x + 1) >= 0) {
			ep[j] = edge3[x];
			a -= Cnk(j, x-- + 1);
		}
}

void CubieCube::setURFtoDLF(short idx) 
{
	int x;
	Corner corner6[6] = { URF, UFL, ULB, UBR, DFR, DLF };
	Corner otherCorner[2] = { DBL, DRB };
	int b = idx % 720; // Permutation
	int a = idx / 720; // Combination
	for (int i = 0; i <DRB+1; i++)
		cp[i] = DRB;// Use DRB to invalidate all corners

	for (int j = 1, k; j < 6; j++)// generate permutation from index b
	{
		k = b % (j + 1);
		b /= j + 1;
		while (k-- > 0)
			rotateRight(corner6, 0, j);
	}
	x = 5;// generate combination and set corners
	for (int j = DRB; j >= 0; j--)
		if (a - Cnk(j, x + 1) >= 0) {
			cp[j] = corner6[x];
			a -= Cnk(j, x-- + 1);
		}
	x = 0;
	for (int j = URF; j <= DRB; j++)
		if (cp[j] == DRB)
			cp[j] = otherCorner[x++];
}

void CubieCube::rotateRight(Corner arr[], int l, int r)
// Right rotation of all array elements between l and r
{
	Corner temp = arr[r];
	for (int i = r; i > l; i--)
		arr[i] = arr[i - 1];
	arr[l] = temp;
}


int CubieCube::verify() {

	int sum = 0;
	int edgeCount[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	for (int i = 0; i < BR + 1; i++)
	{
		edgeCount[ep[i]]++;
	}
		
	for (int i = 0; i < 12; i++)
	{
		if (edgeCount[i] != 1)
		{
			return -2;
		}
	}
		
			

	for (int i = 0; i < 12; i++)
	{
		sum += eo[i];
	}
		
	if (sum % 2 != 0)
	{
		return -3;
	}
		

	int cornerCount[8] = { 0,0,0,0,0,0,0,0 };
	for (int i = 0; i < DRB + 1; i++)
	{
		cornerCount[cp[i]]++;
	}
		
	for (int i = 0; i < 8; i++)
	{
		if (cornerCount[i] != 1)
		{
			return -4;// missing corners
		}
	}
		
			

	sum = 0;
	for (int i = 0; i < 8; i++)
	{
		sum += co[i];
	}
		
	if (sum % 3 != 0)
	{
		return -5;// twisted corner
	}
		

	if ((edgeParity() ^ cornerParity()) != 0)
	{
		return -6;// parity error
	}
		

	return 0;// cube ok
}

short CubieCube::edgeParity() {
	int s = 0;
	for (int i = BR; i >= UR + 1; i--)
		for (int j = i - 1; j >= UR ; j--)
			if (ep[j] > ep[i])
				s++;
	return (short)(s % 2);
}