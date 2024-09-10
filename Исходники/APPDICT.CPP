void TAppDictionary::FreeTable(TAppDictionaryEntry *pTable)
{
    HANDLE hMem =
#ifdef STRICT	
	    LocalHandle((void NEAR*)FP_OFF(pTable));
#else
	    LocalHandle(FP_OFF(pTable));
#endif
    if (LocalUnlock(hMem))
        LocalFree(hMem);
}