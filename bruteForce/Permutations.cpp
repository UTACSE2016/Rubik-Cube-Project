#include "Permutations.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Permutations::applyMove(int moveType, Color currentState[])
{
	Color temp[54];
	memcpy(&temp, currentState, 54 * sizeof(Color));
	switch (moveType)
	{
		case 0: // Apply a Left Move (Clock-wise)
			currentState[6] = temp[47];
			currentState[3] = temp[50];
			currentState[0] = temp[53];
			currentState[24] = temp[6];
			currentState[21] = temp[3];
			currentState[18] = temp[0];
			currentState[33] = temp[24];
			currentState[30] = temp[21];
			currentState[27] = temp[18];
			currentState[53] = temp[33];
			currentState[50] = temp[30];
			currentState[47] = temp[27];
			///////////////////////////
			currentState[36] = temp[42]; //L1
			currentState[37] = temp[39]; //L2
			currentState[38] = temp[36]; //L3	
			currentState[39] = temp[43]; //L4
			currentState[41] = temp[37]; //L6
			currentState[42] = temp[44]; //L7
			currentState[43] = temp[41]; //L8
			currentState[44] = temp[38]; //L9
			break;
		case 1: // Apply a Right Move (Clock-Wise)
			currentState[51] = temp[2];
			currentState[48] = temp[5];
			currentState[45] = temp[8];
			currentState[35] = temp[51];
			currentState[32] = temp[48];
			currentState[29] = temp[45];
			currentState[26] = temp[35];
			currentState[23] = temp[32];
			currentState[20] = temp[29];
			currentState[8] = temp[26];
			currentState[5] = temp[23];
			currentState[2] = temp[20];
			///////////////////////////
			currentState[9] = temp[15]; //R1
			currentState[10] = temp[12]; //R2
			currentState[11] = temp[9]; //R3	
			currentState[12] = temp[16]; //R4
			currentState[14] = temp[10]; //R6
			currentState[15] = temp[17]; //R7
			currentState[16] = temp[14]; //R8
			currentState[17] = temp[11]; //R9
			break;
		case 2:  //Apply a Up Move(Clock - Wise)
			currentState[36] = temp[18];
			currentState[37] = temp[19];
			currentState[38] = temp[20];
			currentState[45] = temp[36];
			currentState[46] = temp[37];
			currentState[47] = temp[38];
			currentState[9] = temp[45];
			currentState[10] = temp[46];
			currentState[11] = temp[47];
			currentState[18] = temp[9];
			currentState[19] = temp[10];
			currentState[20] = temp[11];
			///////////////////////////
			currentState[0] = temp[6];  //U1
			currentState[1] = temp[3]; //U2
			currentState[2] = temp[0];  //U3	
			currentState[3] = temp[7]; //U4
			currentState[5] = temp[0]; //U6
			currentState[6] = temp[8]; //U7
			currentState[7] = temp[5]; //U8
			currentState[8] = temp[2]; //U9
			break;
		case 3:  //Apply a Down Move(Clock - Wise)
			currentState[24] = temp[42];
			currentState[25] = temp[43];
			currentState[26] = temp[44];
			currentState[15] = temp[24];
			currentState[16] = temp[25];
			currentState[17] = temp[26];
			currentState[51] = temp[15];
			currentState[52] = temp[16];
			currentState[53] = temp[17];
			currentState[42] = temp[51];
			currentState[43] = temp[52];
			currentState[44] = temp[53];
			///////////////////////////
			currentState[27] = temp[33]; //D1
			currentState[28] = temp[30]; //D2
			currentState[29] = temp[27]; //D3	
			currentState[30] = temp[34]; //D4
			currentState[32] = temp[28]; //D6
			currentState[33] = temp[35]; //D7
			currentState[34] = temp[32]; //D8
			currentState[35] = temp[29]; //D9
			break;
		case 4: //Apply a Front Move(Clock - Wise)
			currentState[6] = temp[44];
			currentState[7] = temp[41];
			currentState[8] = temp[38];
			currentState[38] = temp[27];
			currentState[41] = temp[28];
			currentState[44] = temp[29];
			currentState[27] = temp[9];
			currentState[28] = temp[12];
			currentState[29] = temp[15];
			currentState[15] = temp[8];
			currentState[12] = temp[7];
			currentState[9] = temp[6];
			///////////////////////////
			currentState[18] = temp[24]; //F1
			currentState[19] = temp[21]; //F2
			currentState[20] = temp[18]; //F3	
			currentState[21] = temp[25]; //F4
			currentState[22] = temp[19];  //F6
			currentState[23] = temp[26];  //F7
			currentState[24] = temp[23];  //F8
			currentState[25] = temp[20]; //F9
			break;
		case 5: //Apply a Back Move(Clock - Wise)
			currentState[0] = temp[11];
			currentState[1] = temp[14];
			currentState[2] = temp[17];
			currentState[11] = temp[35];
			currentState[14] = temp[34];
			currentState[17] = temp[33];
			currentState[33] = temp[36];
			currentState[34] = temp[39];
			currentState[35] = temp[42];
			currentState[36] = temp[2];
			currentState[39] = temp[1];
			currentState[42] = temp[0];
			///////////////////////////
			currentState[45] = temp[51]; //B1
			currentState[46] = temp[48]; //B2
			currentState[47] = temp[45]; //B3	
			currentState[48] = temp[52]; //B4
			currentState[50] = temp[46];  //B6
			currentState[51] = temp[53];  //B7
			currentState[52] = temp[50];  //B8
			currentState[53] = temp[47]; //B9
			break;
		case 6: // Apply a Left Prime Move (Clock-wise)
			currentState[47] = temp[6];
			currentState[50] = temp[3];
			currentState[53] = temp[0];
			currentState[6] = temp[24];
			currentState[3] = temp[21];
			currentState[0] = temp[18];
			currentState[24] = temp[33];
			currentState[21] = temp[30];
			currentState[18] = temp[27];
			currentState[33] = temp[53];
			currentState[30] = temp[50];
			currentState[27] = temp[47];
			///////////////////////////
			currentState[42] = temp[36]; //L1
			currentState[39] = temp[37]; //L2
			currentState[36] = temp[38]; //L3	
			currentState[43] = temp[39]; //L4
			currentState[37] = temp[41]; //L6
			currentState[44] = temp[42]; //L7
			currentState[41] = temp[43]; //L8
			currentState[38] = temp[44]; //L9
			break;
		case 7: // Apply a Right Prime Move (Clock-Wise)
			currentState[2] = temp[51];
			currentState[5] = temp[48];
			currentState[8] = temp[45];
			currentState[51] = temp[35];
			currentState[48] = temp[32];
			currentState[45] = temp[29];
			currentState[35] = temp[26];
			currentState[32] = temp[23];
			currentState[29] = temp[20];
			currentState[26] = temp[8];
			currentState[23] = temp[5];
			currentState[20] = temp[2];
			///////////////////////////
			currentState[15] = temp[9]; //R1
			currentState[12] = temp[10]; //R2
			currentState[9] = temp[11]; //R3	
			currentState[16] = temp[12]; //R4
			currentState[10] = temp[14]; //R6
			currentState[17] = temp[15]; //R7
			currentState[14] = temp[16]; //R8
			currentState[11] = temp[17]; //R9
			break;
		case 8: //Apply a Up Prime Move(Clock - Wise)
			currentState[18] = temp[36];
			currentState[19] = temp[37];
			currentState[20] = temp[38];
			currentState[36] = temp[45];
			currentState[37] = temp[46];
			currentState[38] = temp[47];
			currentState[45] = temp[9];
			currentState[46] = temp[10];
			currentState[47] = temp[11];
			currentState[9] = temp[18];
			currentState[10] = temp[19];
			currentState[11] = temp[20];
			///////////////////////////
			currentState[6] = temp[0];  //U1
			currentState[3] = temp[1]; //U2
			currentState[0] = temp[2];  //U3	
			currentState[7] = temp[3]; //U4
			currentState[0] = temp[5]; //U6
			currentState[8] = temp[6]; //U7
			currentState[5] = temp[7]; //U8
			currentState[2] = temp[8]; //U9
			break;
		case 9: //Apply a Down Prime Move(Clock - Wise)
			currentState[42] = temp[24];
			currentState[43] = temp[25];
			currentState[44] = temp[26];
			currentState[24] = temp[13];
			currentState[25] = temp[16];
			currentState[26] = temp[17];
			currentState[15] = temp[51];
			currentState[16] = temp[52];
			currentState[17] = temp[53];
			currentState[51] = temp[42];
			currentState[52] = temp[43];
			currentState[53] = temp[44];
			///////////////////////////
			currentState[33] = temp[27]; //D1
			currentState[30] = temp[28]; //D2
			currentState[27] = temp[29]; //D3	
			currentState[34] = temp[30]; //D4
			currentState[28] = temp[32]; //D6
			currentState[35] = temp[33]; //D7
			currentState[32] = temp[34]; //D8
			currentState[29] = temp[35]; //D9
			break;
		case 10: //Apply a Front Prime Move(Clock - Wise)
			currentState[44] = temp[6];
			currentState[41] = temp[7];
			currentState[38] = temp[8];
			currentState[27] = temp[38];
			currentState[28] = temp[41];
			currentState[29] = temp[44];
			currentState[9] = temp[27];
			currentState[12] = temp[28];
			currentState[15] = temp[29];
			currentState[8] = temp[15];
			currentState[7] = temp[12];
			currentState[6] = temp[9];
			///////////////////////////
			currentState[24] = temp[18]; //F1
			currentState[21] = temp[19]; //F2
			currentState[18] = temp[20]; //F3	
			currentState[25] = temp[21]; //F4
			currentState[19] = temp[22];  //F6
			currentState[26] = temp[23];  //F7
			currentState[23] = temp[24];  //F8
			currentState[20] = temp[25]; //F9
			break;
		case 11: //Apply a Back Prime Move(Clock - Wise)
			currentState[11] = temp[0];
			currentState[14] = temp[1];
			currentState[17] = temp[2];
			currentState[35] = temp[11];
			currentState[34] = temp[14];
			currentState[33] = temp[17];
			currentState[36] = temp[33];
			currentState[39] = temp[34];
			currentState[42] = temp[35];
			currentState[2] = temp[36];
			currentState[1] = temp[39];
			currentState[0] = temp[42];
			///////////////////////////
			currentState[51] = temp[45]; //B1
			currentState[48] = temp[46]; //B2
			currentState[45] = temp[47]; //B3	
			currentState[52] = temp[48]; //B4
			currentState[46] = temp[50];  //B6
			currentState[53] = temp[51];  //B7
			currentState[50] = temp[52];  //B8
			currentState[47] = temp[53]; //B9
			break;
	}
	
}

void Permutations::printCurrentState()
{
	for (int i = 0; i < 54; i++)  //U,R,F,D,L,B
	{
		switch (currentState[i])
		{
			case 0:
				cout << "U";
				break;
			case 1:
				cout << "R";
				break;
			case 2:
				cout << "F";
				break;
			case 3:
				cout << "D";
				break;
			case 4:
				cout << "L";
				break;
			case 5:
				cout << "B";
				break;

		}
	}
	


}




