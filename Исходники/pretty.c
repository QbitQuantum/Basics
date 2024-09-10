int _cdecl main(int iArgC, LPTSTR pArgs[])
{
    CABINETSTATE cs;
    LPTSTR pArg = pArg=pArgs[1];
    BOOL fOldDontPrettyNames = cs.fDontPrettyNames;
  
    ReadCabinetState(&cs, sizeof(cs));

    if (iArgC > 1)
    {
        if (*pArg==TEXT('-') || *pArg==TEXT('/'))
            pArg++;

        if (lstrcmpi(pArg, TEXT("on"))==0)
        {
            cs.fDontPrettyNames = FALSE;
        }
        else if (lstrcmpi(pArg, TEXT("off"))==0)
        {
            cs.fDontPrettyNames = TRUE;
        }
        else if (*pArg==TEXT('?') || lstrcmpi(pArg, TEXT("help"))==0)
        {
            printf(TEXT("Syntax: pretty.exe [on/off]\n"));
            return 0;
        }

        if (cs.fDontPrettyNames != fOldDontPrettyNames)
            WriteCabinetState(&cs);
    }

    printf(TEXT("Explorer name formatting is %s\n(Any change only become effective after next login)\n"), 
                        cs.fDontPrettyNames ? TEXT("off"):TEXT("on"));

    return 0;
}