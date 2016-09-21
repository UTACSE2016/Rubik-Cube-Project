#include "FaceCube.h"
#include "cubeDefs.h"
#include <iostream>
#include <string>
#include <sstream>
#include "CubieCube.h"
#include <stdint.h>
using namespace std;

FaceCube::FaceCube(string cubeString)
{
	for (size_t i = 0; i < cubeString.length(); i++)
	{
		char substring = cubeString[i];
		
		switch (substring)
		{
			case 'U':
				faceletArray[i] = Color::U;
				break;
			case 'R':
				faceletArray[i] = Color::R;
				break;
			case 'F':
				faceletArray[i] = Color::F;
				break;
			case 'D':
				faceletArray[i] = Color::D;
				break;
			case 'L':
				faceletArray[i] = Color::L;
				break;
			case 'B':
				faceletArray[i] = Color::B;
				break;
		}




	}
}

CubieCube FaceCube::toCubieCube()
{
	int ori;
	CubieCube ccRet = CubieCube();
	ccRet.setupMoveCube();
	for (int i = 0; i < 8; i++)
	{
		ccRet.cp[i] = URF; // invalidate corners
	}
	for (int i = 0; i < 12; i++)
	{
		ccRet.ep[i] = UR; // invalidate edges aswell
	}

	Color col1, col2;
	for (int i = 0; i < DRB+1; i++)
	{
		for (ori = 0; ori < 3; ori++)
		{
			if (faceletArray[cornerFacelet[i][ori]] == U || faceletArray[cornerFacelet[i][ori]] == D)
				break;
		}
			
		col1 = faceletArray[cornerFacelet[i][(ori + 1) % 3]];
		col2 = faceletArray[cornerFacelet[i][(ori + 2) % 3]];
		

		for (int j = 0; j < DRB + 1; j++)
		{
			// in cornerposition i we have cornercubie j
			if (col1 == cornerColor[j][1] && col2 == cornerColor[j][2])
			{
				ccRet.cp[i] = (Corner)j;
				ccRet.co[i] = (char)(ori % 3);
				break;
			}
		}
	}
	for (int i = 0; i < BR + 1; i++)
	{
		for (int j = 0; j < BR + 1; j++)
		{
			if(faceletArray[edgeFacelet[i][0]] == edgeColor[j][0]
				&& faceletArray[edgeFacelet[i][1]] == edgeColor[j][1])
			{
				ccRet.ep[i] = (Edge)j;
				ccRet.eo[i] = 0;
				break;
			}
			if (faceletArray[edgeFacelet[i][0]] == edgeColor[j][1]
				&& faceletArray[edgeFacelet[i][1]] == edgeColor[j][0])
			{
				ccRet.ep[i] = (Edge)j;
				ccRet.eo[i] = 1;
				break;
			}
		}
	}

	return ccRet;
}

void FaceCube::printFaceletArray()
{
	for (int i = 0; i < 54; i++)
	{
		int currentEnum = (int)faceletArray[i];
		switch (currentEnum)
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



