int CDiskRepartition::GetVolumesLetter(PCHAR VolumeName)
{
    DWORD  CharCount = MAX_PATH + 1;
    char Names[20];
    PWCHAR NameIdx   = NULL;
    BOOL   Success   = FALSE;
    for (;;) 
    {
        Success = GetVolumePathNamesForVolumeNameA(
            VolumeName, (LPCH)Names, sizeof(Names), &CharCount
            );

        if ( Success ) 
        {
            return Names[0];
        }

        if ( GetLastError() != ERROR_MORE_DATA ) 
        {
            return -1;
        }
		else
        {
            return Names[0];
        }
    }
    return -1;
}