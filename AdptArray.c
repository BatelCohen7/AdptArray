#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;

//creating a new array 
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
    return pArr;
}

// This func change the element at index in array to the element that the user want
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    if (pArr == NULL || index < 0)
        return FAIL;

    if (idx >= pArr->ArrSize)
    {

        // Extend Array
        PElement* newpElemArr = (PElement*)realloc(pArr->pElemArr, (idx + 1) * sizeof(PElement));
        if (newpElemArr == NULL)
            return FAIL;
        //memset(&newpElemArr[pArr->ArrSize], 0, (idx - pArr->ArrSize + 1) * sizeof(PElement));
        pArr->pElemArr = newpElemArr;
        
        for (int i = pArr->ArrSize; i <= idx; i++) {
            pArr->pElemArr[i] = NULL;
        }
        
    }

    // Delete Previous Elem
    if (pArr->pElemArr[idx] != NULL) {
        pArr->delFunc(pArr->pElemArr[idx]);
    }
    pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);

    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

// This func is getting a copy of element by the index in the array
PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
    if (pArr == NULL || idx < 0 || idx >= pArr->ArrSize || pArr->pElemArr[idx] == NULL)
        return NULL;
        
    return pArr->copyFunc(pArr->pElemArr[idx]);
}

// return the size of the array
int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
        return -1;
        
    return pArr->ArrSize;
}

// print the array
void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
        return;
    for (int i = 0; i < pArr->ArrSize; ++i)
    {
        if (pArr->pElemArr[i] != NULL) {
        	pArr->printFunc(pArr->pElemArr[i]);
        	printf("\n");
        }
    }
    
}

// delete the array and its elements
void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
		
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL) {
        		pArr->delFunc(pArr->pElemArr[i]);
        	}
	}
	free(pArr->pElemArr);
	free(pArr);
}
