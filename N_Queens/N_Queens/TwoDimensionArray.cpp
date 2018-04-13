#include "stdafx.h"
#include "TwoDimensionArray.h"

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