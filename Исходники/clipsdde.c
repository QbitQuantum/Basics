void ShutDownDDE ( void )
{  extern HSZ hszService, hszItem, hszComplete, hszBatch, hszLoad;
   extern HCONV hConvApp; /* What does this do? -- Apparently Unused */
   extern DWORD idInst;

   if ( hConvApp != NULL)
   {  DdeDisconnect ( hConvApp );
      hConvApp = NULL;
   }
   DdeNameService (idInst, hszService, (HSZ)NULL, DNS_UNREGISTER );
   DdeFreeStringHandle ( idInst, hszService );
   DdeFreeStringHandle ( idInst, hszCommand );
   DdeFreeStringHandle ( idInst, hszResult    );
}