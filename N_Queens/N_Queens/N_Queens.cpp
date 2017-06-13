// N_Queens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "TwoDimensionArray.h"

enum BoardOccupance
{
	BLOCK = -1,
	ALLOW = 0,
	UNBLOCK = 1
};

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

bool Placeable(int** SolutionMatrix, int nPlaced, int nColumn)
{
	return (SolutionMatrix[nPlaced][nColumn] == ALLOW)? true : false;
}

void SetSolutionMatrix(int** SolutionMatrix, int nPlaced, int nColumn, int nQueens, BoardOccupance eValue)
{
	SolutionMatrix[nPlaced][nColumn] += eValue;

	// Row
	for(int i = 0; i < nQueens; i++)
		if(i != nPlaced)
			SolutionMatrix[i][nColumn] += eValue;
		else
			continue;

	// Column
	for(int i = 0; i < nQueens; i++)
		if(i != nColumn)
			SolutionMatrix[nPlaced][i] += eValue;
		else
			continue;

	// Main Diagonal
	int nCurrentRow = nPlaced + 1;
	int nCurrentColumn = nColumn + 1;

	while(nCurrentRow < nQueens && nCurrentColumn < nQueens)
	{
		SolutionMatrix[nCurrentRow][nCurrentColumn] += eValue;
		
		nCurrentRow++;
		nCurrentColumn++;
	}

	nCurrentRow = nPlaced - 1;
	nCurrentColumn = nColumn - 1;

	while(nCurrentRow >= 0 && nCurrentColumn >= 0)
	{
		SolutionMatrix[nCurrentRow][nCurrentColumn] += eValue;
		
		nCurrentRow--;
		nCurrentColumn--;
	}

	// Secondary Diagonal

	nCurrentRow = nPlaced + 1;
	nCurrentColumn = nColumn - 1;

	while(nCurrentRow < nQueens && nCurrentColumn >= 0)
	{
		SolutionMatrix[nCurrentRow][nCurrentColumn] += eValue;
		
		nCurrentRow++;
		nCurrentColumn--;
	}

	nCurrentRow = nPlaced - 1;
	nCurrentColumn = nColumn + 1;

	while(nCurrentRow >= 0 && nCurrentColumn < nQueens)
	{
		SolutionMatrix[nCurrentRow][nCurrentColumn] += eValue;
		
		nCurrentRow--;
		nCurrentColumn++;
	}
}

void PrintSolutionMatrix(int** SolutionMatrix, int nQueens)
{
	for(int i = 0; i < nQueens; i++)
	{
		for(int j = 0; j < nQueens; j++)
			printf("%d\t", SolutionMatrix[i][j]);
		printf("\n");
	}

	printf("\n\n");
}

bool PlaceQueen(char** Board, int** SolutionMatrix, int nQueens, int nPlaced)
{
	if(nQueens == nPlaced)
		return true;

	for(int nCol = 0; nCol < nQueens; nCol++)
	{		
		if(Placeable(SolutionMatrix, nPlaced, nCol))
		{
			Board[nPlaced][nCol] = 'Q';
			SetSolutionMatrix(SolutionMatrix, nPlaced, nCol, nQueens, BLOCK);

		//	PrintSolutionMatrix(SolutionMatrix, nQueens);

			if(PlaceQueen(Board, SolutionMatrix, nQueens, nPlaced + 1))
				return true;
			else
			{
				Board[nPlaced][nCol] = '_';
				SetSolutionMatrix(SolutionMatrix, nPlaced, nCol, nQueens, UNBLOCK);
			}
		}
	}
	return false;
}

void ConstructBoard(char** Board, int nQueens)
{	
	for(int i = 0; i < nQueens; i++)
		for(int j = 0; j < nQueens; j++)
			Board[i][j] = '_';
}

void ConstructSolutionMatrix(int** SolutionMatrix, int nQueens)
{
	for(int i = 0; i < nQueens; i++)
		for(int j = 0; j < nQueens; j++)
			SolutionMatrix[i][j] = ALLOW;
}

void PrintBoard(char** Board, int nQueens)
{
	for(int i = 0; i < nQueens; i++)
	{
		for(int j = 0; j < nQueens; j++)
			printf("%c\t", Board[i][j]);
		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nQueens = 20;
	int nPlaced = 0;

	char** Board = TwoDimensionArray<char>(nQueens, nQueens);
	int** SolutionMatrix = TwoDimensionArray<int>(nQueens, nQueens);

	ConstructBoard(Board, nQueens);
	ConstructSolutionMatrix(SolutionMatrix, nQueens);

	if(PlaceQueen(Board, SolutionMatrix, nQueens, nPlaced))
		PrintBoard(Board, nQueens);
	else
		printf("\n No Solution");

	int x;
	scanf("%d", &x);

	return 0;
}

