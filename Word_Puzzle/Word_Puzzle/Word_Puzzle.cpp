// Word_Puzzle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector"
#include "string.h"

using namespace std;

int KICK_START = 0;

template <class tType>
tType** TwoDimensionArray(int nRows, int nCols)
{
    tType* OneDimensionArray = new tType[nRows * nCols];
    tType** TwoDimensionArray = new tType*[nRows];
    
    if( NULL == OneDimensionArray || NULL == TwoDimensionArray )
		printf("\n Error in creating matrix\n");
   
    for(int i = 0; i < nRows; i++)
        TwoDimensionArray[i] = &OneDimensionArray[nCols * i];
        
    return TwoDimensionArray;
}

bool SafeToLook(int nRow, int nColumn, int nRowCurrent, int nColumnCurrent, int** SolutionMatrix)
{
	if ( nRowCurrent >= 0 && nRowCurrent < nRow && nColumnCurrent >= 0 && nColumnCurrent < nColumn )
		return ( SolutionMatrix[nRowCurrent][nColumnCurrent] < 0 );
	return false;
}

bool SearchWord(char** WordMatrix, int** SolutionMatrix, char* cWords, int nRow, int nColumn, int nRowCurrent, int nColumnCurrent, int nPosition)
{
	if(cWords[nPosition] == '\0')
		return true;

	if(SafeToLook(nRow, nColumn, nRowCurrent, nColumnCurrent, SolutionMatrix))	
	{	
		SolutionMatrix[nRowCurrent][nColumnCurrent] = nPosition;

		if(cWords[nPosition] == WordMatrix[nRowCurrent][nColumnCurrent])
		{
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent + 1, nColumnCurrent, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent - 1, nColumnCurrent, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent, nColumnCurrent + 1, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent, nColumnCurrent - 1, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent + 1, nColumnCurrent + 1, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent + 1, nColumnCurrent - 1, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent - 1, nColumnCurrent + 1, nPosition + 1))
					return true;
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, nRowCurrent - 1, nColumnCurrent - 1, nPosition + 1))
					return true;
		}		
		SolutionMatrix[nRowCurrent][nColumnCurrent] = -1;
	}	
	return false;
}

bool FindWord(char** WordMatrix, int** SolutionMatrix, char* cWords, int nRow, int nColumn)
{
	for(int i = 0; i < nRow; i++)
		for(int j = 0; j < nColumn; j++)
			if(SearchWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn, i, j, KICK_START))
				return true;
	return false;
}

void BuildWordMatrix(char** WordMatrix, int nRow, int nColumn)
{
	 WordMatrix[0][0] = 'W'; WordMatrix[0][1] = 'A'; WordMatrix[0][2] = 'T'; WordMatrix[0][3] = 'E'; WordMatrix[0][4] = 'R';
     WordMatrix[1][0] = 'L'; WordMatrix[1][1] = 'E'; WordMatrix[1][2] = 'Q'; WordMatrix[1][3] = 'K'; WordMatrix[1][4] = 'M';
     WordMatrix[2][0] = 'O'; WordMatrix[2][1] = 'M'; WordMatrix[2][2] = 'I'; WordMatrix[2][3] = 'Z'; WordMatrix[2][4] = 'E';
     WordMatrix[3][0] = 'N'; WordMatrix[3][1] = 'M'; WordMatrix[3][2] = 'N'; WordMatrix[3][3] = 'O'; WordMatrix[3][4] = 'L';
     WordMatrix[4][0] = 'X'; WordMatrix[4][1] = 'E'; WordMatrix[4][2] = 'P'; WordMatrix[4][3] = 'N'; WordMatrix[4][4] = 'A';
}

void BuildSolutionMatrix(int** SolutionMatrix, int nRow, int nColumn)
{
	for(int i = 0; i < nRow; i ++)
		for(int j = 0; j < nColumn; j++)
			SolutionMatrix [i][j] = -1;
}

void PrintSolutionMatrix(int** SolutionMatrix, int nRow, int nColumn)
{
	for(int i = 0; i < nRow; i ++)
	{
		for(int j = 0; j < nColumn; j++)
			printf("%d\t", SolutionMatrix [i][j] + 1);
		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nRow = 5;
	int nColumn = 5;

	char* cWords = "ZION";

	char** WordMatrix = TwoDimensionArray<char>(nRow, nColumn);
	int** SolutionMatrix = TwoDimensionArray<int>(nRow, nColumn);

	BuildWordMatrix(WordMatrix, nRow, nColumn);
	BuildSolutionMatrix(SolutionMatrix, nRow, nColumn);

	if(FindWord(WordMatrix, SolutionMatrix, cWords, nRow, nColumn))
		PrintSolutionMatrix(SolutionMatrix, nRow, nColumn);
	else
		printf("No solution");

	int x;
	scanf("%d", &x);

	return 0;
}

