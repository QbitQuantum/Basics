/* clean up dll libraries when exiting kappa */ 
void KppDLLExit(void)
{
    short i;
    kppDLLTABLE FAR *kppDLLTable;
    
#ifndef MAC
    kppDLLTable = (kppDLLTABLE FAR *) GLOBALLOCK(hdlkppDLLTable);
    for (i = 0; i <= lib_table_index; i++)
        if (kppDLLTable[i].LibHandle)
            FreeLibrary(kppDLLTable[i].LibHandle);
        
    GLOBALUNLOCK(hdlkppDLLTable);
    GLOBALFREE(hdlkppDLLTable);
#endif    
}