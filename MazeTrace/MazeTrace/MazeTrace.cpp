// MazeTrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

enum Direction{    
    DOWN = 0, UP, LEFT, RIGHT
};

template <class tType>
tType** NewTwoDimensionArray(int nRows, int nCols)
{
    tType* OneDimensionArray = new tType[nRows * nCols];
    tType** TwoDimensionArray = new tType*[nRows];
    
    if( NULL == OneDimensionArray || NULL == TwoDimensionArray )
		printf("\n Error in creating matrix\n");
    
    for(int i = 0; i < nRows; i++)
        TwoDimensionArray[i] = &OneDimensionArray[nCols * i];
        
    return TwoDimensionArray;
}

void ConstructMaze(char** Maze)
{
    Maze[0][0] = 'S'; Maze[0][1] = 'X'; Maze[0][2] = 'X'; Maze[0][3] = 'X'; Maze[0][4] = 'X';
    Maze[1][0] = 'X'; Maze[1][1] = '-'; Maze[1][2] = '-'; Maze[1][3] = '-'; Maze[1][4] = 'X';
    Maze[2][0] = 'X'; Maze[2][1] = 'X'; Maze[2][2] = 'X'; Maze[2][3] = '-'; Maze[2][4] = '-';
    Maze[3][0] = '-'; Maze[3][1] = 'X'; Maze[3][2] = 'X'; Maze[3][3] = '-'; Maze[3][4] = '-';
    Maze[4][0] = '-'; Maze[4][1] = '-'; Maze[4][2] = '-'; Maze[4][3] = '-'; Maze[4][4] = 'C';
}

void ConstructConfusionMatrix(int** ConfusionMatrix, int nRows, int nCols)
{
   for(int i = 0; i < nRows; i++)
    for(int j = 0; j < nCols; j++)
        ConfusionMatrix[i][j] = 0;
}

void  PrintMaze(char** Maze, int nRows, int nCols)
{
	printf("\n Maze layout \n\n");

    for(int i = 0; i < nRows; i++)
    {
        for(int j = 0; j < nCols; j++)
            printf("%c\t",Maze[i][j]);
        printf("\n");
    }
}

bool CheckSafeToMove(char** Maze, int nRows, int nCols, int nRowPosition, int nColumnPosition)
{
    if(nRowPosition >= 0 && nRowPosition < nRows && nColumnPosition >= 0 && nColumnPosition < nCols && Maze[nRowPosition][nColumnPosition] != 'X')
        return true;
    else
        return false;
}

bool TraverseMaze(char** Maze, int** ConfusionMatrix, int nRowCurrent, int nColCurrent, int nRows, int nCols, Direction direction)
{
    if(true == CheckSafeToMove(Maze, nRows, nCols, nRowCurrent, nColCurrent))
    {
        ConfusionMatrix[nRowCurrent][nColCurrent] = 1;

        if(Maze[nRowCurrent][nColCurrent] == 'C')
            return true;
        else
        {
            if(direction != DOWN && TraverseMaze(Maze, ConfusionMatrix, nRowCurrent - 1, nColCurrent, nRows, nCols, UP))
                return true;
            if(direction != UP && TraverseMaze(Maze, ConfusionMatrix, nRowCurrent + 1, nColCurrent, nRows, nCols, DOWN))
                return true;
            if(direction != LEFT && TraverseMaze(Maze, ConfusionMatrix, nRowCurrent, nColCurrent + 1, nRows, nCols, RIGHT))
                return true;
            if(direction != RIGHT && TraverseMaze(Maze, ConfusionMatrix, nRowCurrent, nColCurrent - 1, nRows, nCols, LEFT))
                return true;
        }
        ConfusionMatrix[nRowCurrent][nColCurrent] = 0;
    }
    return false;
}

void  PrintConfusionMatrix(int** ConfusionMatrix, int nRows, int nCols)
{
	printf("\n Solution Matrix \n\n");

    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++)
            printf("%d\t",ConfusionMatrix[i][j]);
        printf("\n");
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nRows = 5;
	int nCols = 5;
	
	int nRowCurrent = 0;
	int nColCurrent = 0;

	char** Maze = NewTwoDimensionArray<char>(nRows, nCols);
	int** ConfusionMatrix = NewTwoDimensionArray<int>(nRows, nCols);

	ConstructMaze(Maze);   // Modify Manually
	ConstructConfusionMatrix(ConfusionMatrix, nRows, nCols);
    
    PrintMaze(Maze, nRows, nCols);
    
	if(true == TraverseMaze(Maze, ConfusionMatrix, nRowCurrent, nColCurrent, nRows, nCols, DOWN))
	    PrintConfusionMatrix(ConfusionMatrix, nRows, nCols);
	else
	{
	    printf("No path \n\n");
	    PrintConfusionMatrix(ConfusionMatrix, nRows, nCols);
	}

	scanf("%d", &nRows);

	return 0;
}