#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    PElement* newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (idx >= pArr->ArrSize)
    {

// Extend Array
        if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        realloc(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    pArr->delFunc((pArr->pElemArr)[idx]);
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
    if (pArr == NULL || idx < 0 || idx >= pArr->ArrSize)
        return NULL;
    return pArr->pElemArr[idx];
}

int GetAdptArraySize(PAdptArray pArr)
{
    if (pArr == NULL)
        return -1;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
    int i;
    if (pArr == NULL)
        return;
    for (i = 0; i < pArr->ArrSize; ++i)
    {
        printf("%d ", *(int*)(pArr->pElemArr[i]));
    }
    printf("\n");
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}