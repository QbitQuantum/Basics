BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
   if (fdwReason == DLL_PROCESS_ATTACH)
   {
       // Save instance handle for later access in other functions.

       g_hinstDLL = hinstDLL;

       // Create a buffer for holding the Windows directory path.

       char szPath [150]; // Probably only 140 is needed, but why not be safe?

       // Retrieve the path of the Windows directory.

       GetWindowsDirectory (szPath, 128);

       // Obtain number of characters copied into the buffer.

       int iLen = lstrlen (szPath);

       // Path ends in a backslash character if the directory is the root.
       // Otherwise, path does not end in backslash. In that case, we must
       // append a backslash character to the path.

       if (iLen != 0 && szPath [iLen-1] != '\\')
           lstrcat (szPath, "\\");

       // Append TWAIN_32.DLL to the path. This is the 32-bit TWAIN DLL that
       // we need to communicate with.

	   lstrcat (szPath, "TWAIN_32.DLL");

       // If the TWAIN_32.DLL file exists in the path (which is determined by
       // opening and closing that file), attempt to load TWAIN_32.DLL into
       // the calling process's address space.

       OFSTRUCT ofs;
       if (OpenFile (szPath, &ofs, OF_EXIST) != -1)
           g_hLib = LoadLibrary (szPath);

       // Report failure if TWAIN_32.DLL cannot be loaded and terminate the
       // JTWAIN DLL.

       if (g_hLib == 0)
       {
           MessageBox (0, "Unable to open TWAIN_32.DLL", "JTWAIN", MB_OK);
           return FALSE;
       }

       // Attempt to retrieve DSM_Entry() function address.

       g_pDSM_Entry = (DSMENTRYPROC) GetProcAddress (g_hLib, "DSM_Entry");

       // Report failure if DSM_Entry() function not found in TWAIN_32.DLL
       // and terminate the JTWAIN DLL.

       if (g_pDSM_Entry == 0)
       {
           MessageBox (0, "Unable to fetch DSM_Entry address", "JTWAIN", 
                       MB_OK);
           return FALSE;
       }

       // Initialize g_AppID. This structure is passed to DSM_Entry() in each
       // function call.

       g_AppID.Id = 0;
       g_AppID.Version.MajorNum = 1;
       g_AppID.Version.MinorNum = 0;
       g_AppID.Version.Language = TWLG_ENGLISH_USA;
       g_AppID.Version.Country = TWCY_USA;

       lstrcpy (g_AppID.Version.Info, "JTWAIN 1.0");

       g_AppID.ProtocolMajor = TWON_PROTOCOLMAJOR;
       g_AppID.ProtocolMinor = TWON_PROTOCOLMINOR;
       g_AppID.SupportedGroups = DG_CONTROL | DG_IMAGE;

       lstrcpy (g_AppID.Manufacturer, "Jeff Friesen");
       lstrcpy (g_AppID.ProductFamily, "Java-based Image Capture");
       lstrcpy (g_AppID.ProductName, "JTWAIN");
   }
   else
   if (fdwReason == DLL_PROCESS_DETACH)
   {
       // If the TWAIN_32.DLL library was loaded, remove it from memory.

       if (g_hLib != 0)
           FreeLibrary (g_hLib);
   }

   return TRUE;
}