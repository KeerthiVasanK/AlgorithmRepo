// Least Distance Pairs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <map>
#include <utility>

#define SAME_POINT_DISTANCE 1000

class CartesianPoint
{ 
  public:

	int nXCoordinate;
	int nYCoordinate;

	CartesianPoint();
	CartesianPoint(int nXCoordinate, int nYCoordinate);
	double	EucledianDistance(CartesianPoint& point);
};

CartesianPoint::CartesianPoint(int nXCoordinate, int nYCoordinate)
{
	this->nXCoordinate = nXCoordinate;
	this->nYCoordinate = nYCoordinate;
}

double CartesianPoint::EucledianDistance(CartesianPoint &point)
{
	double dX1 = this->nXCoordinate;
	double dY1 = this->nYCoordinate;

	double dX2 = point.nXCoordinate;
	double dY2 = point.nYCoordinate;

    return pow( pow(dX1 - dX2, 2) + pow(dY1 - dY2, 2), 0.5);
}

std::map<int, CartesianPoint> ListOfPoints;

double** DistanceTable;
bool* MappedCoordinates;
int** PairedCoordinates;

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

void ComputeDistances(int nNumberOfPoints)
{

   for(int i = 0; i < nNumberOfPoints; i++)
	   for(int j = 0; j < nNumberOfPoints; j++)
		   if(i != j)
		   {
			   CartesianPoint& first = ListOfPoints.find(i)->second;
			   CartesianPoint& second = ListOfPoints.find(j)->second;

			   DistanceTable[i][j] = first.EucledianDistance(second);
		   }
		   else
		   {
               DistanceTable[i][j] = SAME_POINT_DISTANCE;
		   }

}

int FindUnpairedClosestNeighbour(int nCurrentPoint, int nNumberOfPoints)
{
	double dMinimunDistance = (double) SAME_POINT_DISTANCE;
	int nClosestNeighbour = -1;

	for(int i = 0; i < nNumberOfPoints; i++)
	{
		if((DistanceTable[nCurrentPoint][i] < dMinimunDistance) && (MappedCoordinates[i] == false))
		{
			nClosestNeighbour = i;
			dMinimunDistance = DistanceTable[nCurrentPoint][i];
		}
	}

	return nClosestNeighbour;
}

void PairCoordinates(int nNumberOfPoints)
{	
	PairedCoordinates = TwoDimensionArray<int>(nNumberOfPoints/2, 2);

	int nPaired = 0;

	do
	{
		for(int i = 0; i < nNumberOfPoints; i++)
		{
			for(int j = 0; j< nNumberOfPoints; j++)
			{
				if(i != j && (MappedCoordinates[i] == false && MappedCoordinates[j] == false))
				{
					if(FindUnpairedClosestNeighbour(i, nNumberOfPoints) == j && FindUnpairedClosestNeighbour(j, nNumberOfPoints) == i)
					{
						MappedCoordinates[i] = true;
						MappedCoordinates[j] = true;

						PairedCoordinates[nPaired / 2][0] = i;
						PairedCoordinates[nPaired / 2][1] = j;
	
						nPaired += 2;
						break;
					}
				}
			}
		}
	}while(nPaired < nNumberOfPoints);

}

void ReadCartesianPoints(int nNumberOfPoints)
{
    for(int i = 0; i < nNumberOfPoints; i++)
	{
		int nX, nY;
		printf("\n Enter Point #%d coordinates: ", i);
        scanf("%d %d", &nX, &nY);

		std::pair<int, CartesianPoint> pair(i, CartesianPoint(nX, nY));

		ListOfPoints.insert(pair);
	}
}

void SetCoordinatesMap(int nNumberOfPoints)
{
	MappedCoordinates = new bool[nNumberOfPoints];

	for(int i = 0; i < nNumberOfPoints; i++)
		MappedCoordinates[i] = false;
}

void PrintPairedCoordinates(int nNumberOfPoints)
{
	printf("\n Result: \n");
	for(int i = 0; i < (nNumberOfPoints/2); i++)
		printf("\n(%d, %d)", PairedCoordinates[i][0], PairedCoordinates[i][1]);
}

int _tmain(int argc, _TCHAR* argv[])
{

	int nNumberOfPoints;

	printf("\n Number of Points: ");
	scanf("%d", &nNumberOfPoints);

	DistanceTable = TwoDimensionArray<double>(nNumberOfPoints, nNumberOfPoints);

	SetCoordinatesMap(nNumberOfPoints);

	ReadCartesianPoints(nNumberOfPoints);

	ComputeDistances(nNumberOfPoints);

	PairCoordinates(nNumberOfPoints);

	PrintPairedCoordinates(nNumberOfPoints);

	int x;
	scanf("%d", &x);

	return 0;
}

