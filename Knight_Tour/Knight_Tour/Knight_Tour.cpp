// Knight_Tour.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int	ALLOW = -1;

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

bool KnightMovable(int** SolutionMatrix, int nRowPosition, int nColumnPosition, int nBoardSpan)
{
	if(nRowPosition >= 0 && nRowPosition < nBoardSpan && nColumnPosition >= 0 && nColumnPosition < nBoardSpan)
		return SolutionMatrix[nRowPosition][nColumnPosition] == ALLOW;
	else
		return false;
}

void TrackMove(int** SolutionMatrix, int nRowPosition, int nColumnPosition, int nValue)
{
	SolutionMatrix[nRowPosition][nColumnPosition] = nValue;
}

bool KnightTour(int** SolutionMatrix, int nBoardSpan, int nRowPosition, int nColumnPosition, int nMove)
{
//	printf("\n Move - %d", nMove);

	if(nMove == (nBoardSpan * nBoardSpan))
		return true;

	if(KnightMovable(SolutionMatrix, nRowPosition, nColumnPosition, nBoardSpan))
	{
		TrackMove(SolutionMatrix, nRowPosition, nColumnPosition, nMove);

		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition + 2, nColumnPosition + 1, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition + 1, nColumnPosition + 2, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition - 1, nColumnPosition + 2, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition - 2, nColumnPosition + 1, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition - 2, nColumnPosition - 1, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition - 1, nColumnPosition - 2, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition + 1, nColumnPosition - 2, nMove + 1))
			return true;
		if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition + 2, nColumnPosition - 1, nMove + 1))
			return true;

		TrackMove(SolutionMatrix, nRowPosition, nColumnPosition, ALLOW);
	}	
	return false;
}

void ConstructSolutionMatrix(int** SolutionMatrix, int nBoardSpan)
{
	for(int i = 0; i < nBoardSpan; i++)
		for(int j = 0; j < nBoardSpan; j++)
			SolutionMatrix[i][j] = ALLOW;	
}

void PrintSolutionMatrix(int** SolutionMatrix, int nBoardSpan)
{
	printf("\n");
	for(int i = 0; i < nBoardSpan; i++)
	{
		for(int j = 0; j < nBoardSpan; j++)
			printf("%d\t", SolutionMatrix[i][j]);
		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{	
	int nBoardSpan = 8;
	int nMove = 0;

	int nRowPosition = 0;
	int nColumnPosition = 0;

	int** SolutionMatrix = TwoDimensionArray<int>(nBoardSpan, nBoardSpan);

	ConstructSolutionMatrix(SolutionMatrix, nBoardSpan);

	if(KnightTour(SolutionMatrix, nBoardSpan, nRowPosition, nColumnPosition, 0))
		PrintSolutionMatrix(SolutionMatrix, nBoardSpan);
	else
		printf("No Solution");

	int x;
	scanf("%d", &x);

	return 0;
}