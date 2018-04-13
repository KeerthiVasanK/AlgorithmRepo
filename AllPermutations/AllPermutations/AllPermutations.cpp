// AllPermutations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
 * This implementation can accept syntactically correct sentences(with spaces and punctuatuions).
 * However, redundancy in final strings(due to repetition of alphabet) persists. This has to be eliminated.
 */

/*
 * These global variables are accessed directly only for initialization. 
 */

char* pAlphabet;
char* pBuildString;
bool* pAddressBlueprint;

int GetStringLength(char* pConstructionString, int nLength)
{
    int i = 0; 
	
	while(pConstructionString[i] != '_' && i < nLength)
	{
		i++;
	}

	return i;
}

void AllPermutations(int nCallDepth, char* pAlphabet, bool* pAddressBlueprint, char* pConstructionString, int nLength)
{

	if(nLength == nCallDepth)
	{
      pConstructionString[nLength] = '\0'; 
      printf("\n %s", pConstructionString);
	  return;
	}

    for(int i = 0; i < nLength; i++)
    {
      if(pAddressBlueprint[i] == true)
	  	  continue;
   	  else
	  {
         int nCurrentPosition = GetStringLength(pConstructionString, nLength);

	  	 pAddressBlueprint[i] = true;
		 pConstructionString[nCurrentPosition] = pAlphabet[i];

		 AllPermutations(nCallDepth + 1, pAlphabet, pAddressBlueprint, pConstructionString, nLength);
		
		 pConstructionString[nCurrentPosition] = '_';   
		 pAddressBlueprint[i] = false;
	  }
   }
}

int GetValidLength(char* sInputWord)
{
	int nNumberOfCharacters = 0;
	int nNonAlphabets = 0;

  	for(int i = 0; i< 100; i++)
	{      
      if(sInputWord[i] > 90)
		  sInputWord[i] -= 32;
      
      if(0 != sInputWord[i] && !(64 < sInputWord[i] && 91 > sInputWord[i]))
	  {
         nNonAlphabets++;
	  }

      if(0 == sInputWord[i])
	  {
		  nNumberOfCharacters = i;
		  break;
	  }	
	}
  
	return nNumberOfCharacters - nNonAlphabets;
}

void PrepareAlphabet(char* sInputWord)
{
  int nIterator = 0;

  for(int i = 0; 0 != sInputWord[i]; i++)
    if(64 < sInputWord[i] && 91 > sInputWord[i])
		pAlphabet[nIterator++] = sInputWord[i];

  pAlphabet[nIterator] = '\0';
}

bool PrepareInput(int nLength, char* sInputWord)
{  
    pAlphabet = (char*) malloc(sizeof(char) * nLength);
	pBuildString = (char*) malloc(sizeof(char) * nLength);
	pAddressBlueprint = (bool*) malloc(sizeof(bool) * nLength);

	if(pAlphabet != NULL && pAddressBlueprint != NULL && pBuildString != NULL)
	{
		for(int i = 0; i < nLength; i++)
		{
			pAddressBlueprint[i] = false; 
		    pBuildString[i] = '_';
			pAlphabet[i] = '_';
		}

		pAddressBlueprint[nLength] = '\0'; 
		pBuildString[nLength] = '\0';
		pAlphabet[nLength] = '\0';
					
		PrepareAlphabet(sInputWord);

		return true;
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{

	char sInputWord[100];
	int nLength;	

	scanf("%[^\n]%*c", &sInputWord);

	nLength = GetValidLength(sInputWord);

	if(PrepareInput(nLength, sInputWord))
		AllPermutations(0, pAlphabet, pAddressBlueprint, pBuildString, nLength);

	int x;
	scanf("%d", &x);

	return 0;
}

