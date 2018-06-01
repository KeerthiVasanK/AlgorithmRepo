// PrefixMatching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

char* pString = NULL;
int* pValueMap = NULL;

int nPrefixMarker = 0;
int nCurrentPosition = 0;

template <class tType>
tType* NewOneDimensionArray(int nSize)
{
    tType* OneDimensionArray = new tType[nSize];    
    
    if( NULL == OneDimensionArray )
		printf("\n Error in creating Array\n");
        
    return OneDimensionArray;
}

void ComparePrefix()
{

	if(pString[nCurrentPosition] == pString[nPrefixMarker])
	{	
		pValueMap[nCurrentPosition] = nPrefixMarker + 1;
		nPrefixMarker++;
		return;
	}

	if((pString[nCurrentPosition] != pString[nPrefixMarker]) && nPrefixMarker != 0)
	{
		nPrefixMarker = pValueMap[nPrefixMarker - 1];
		ComparePrefix();
		return;
	}
	
	if((pString[nCurrentPosition] != pString[nPrefixMarker]) && nPrefixMarker == 0)
	{
		pValueMap[nCurrentPosition] = 0;
		return;
	}

}

void SubStringMatching(int nStringLength)
{
	nCurrentPosition = 1;

	pValueMap[nPrefixMarker] = 0;

	for(; nCurrentPosition < nStringLength; nCurrentPosition++)
	{
		ComparePrefix();
	}
}

void ReadString(int nSize)
{
	printf("\n Enter array:\t");
	scanf("%s", pString);

	pString[nSize] = '\0';

	for(int i = 0; i < nSize; i++)
		pValueMap[i] = 0;
}

void PrintSubStringMap(int nSize)
{
	for(int i = 0; i < nSize; i++)
		printf("%d", pValueMap[i]);
}

int _tmain(int argc, _TCHAR* argv[])
{

	int nSize;

	printf("\n Enter array size: \t");
	scanf("%d", &nSize);

	pString = NewOneDimensionArray<char>(nSize + 1);
	pValueMap = NewOneDimensionArray<int>(nSize);

	ReadString(nSize);

	SubStringMatching(nSize);

	PrintSubStringMap(nSize);

	int x;
	scanf("%d", &x);
	return 0;
}

