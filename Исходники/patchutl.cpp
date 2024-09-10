bool
ihiMapAssign(
    PIHI_MAP    *ioMap,
    LPCSTR  inKey,
    LPVOID      inValue)
/*++

Routine Description:

    This routine creates a new MAP entry and inserts it into the existing
    map supplied in ioMap. We pass the address of the MAP head such that
    when we insert the first item, we modify the head itself to point to it.

Returns:

    false - if memory allocation for new map failed
    true - in all other cases

--*/
{
    //IHU_DBG_ASSERT(ioMap);

    IHI_MAP *tempMap = new IHI_MAP;

    if (tempMap == NULL)
    {
        return false;
    }

    memset(tempMap, 0, sizeof(IHI_MAP));

    StringCchCopyA(
                tempMap->Key,
                MAX_PATH,
                inKey);

    tempMap->Value = inValue;

    tempMap->Next = NULL;

    if (*ioMap)
    {
        PIHI_MAP pCurrent = *ioMap;

        while(pCurrent->Next)
        {
            pCurrent = pCurrent->Next;
        }

        pCurrent->Next  = tempMap;
    }
    else
    {
        *ioMap = tempMap;
    }

    return true;
}