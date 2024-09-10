DWORD ShowPrinterInfo(wchar_t *lpName,  int level, int opt, char *padding) {

   unsigned char *lpInfo;
   int i,j;
   DWORD n;
   DWORD dwSizeNeeded=0;
   char newpadding[50];

   DWORD ret;

   if (opt & OPT_UNICODE) {
      EnumPrintersW ( PRINTER_ENUM_NAME, (wchar_t* )lpName, level, NULL, 0, &dwSizeNeeded, &n );
   } else {
      EnumPrintersA ( PRINTER_ENUM_NAME, (char *)lpName, level, NULL, 0, &dwSizeNeeded, &n );
   }
   if (dwSizeNeeded==0) {    
#ifdef _DBG_
      printf ( "EnumPrintersX() Invalid. Error: %d \n",GetLastError() );
#endif
      return(-1);
   }

   lpInfo = (void *)HeapAlloc ( GetProcessHeap (), HEAP_ZERO_MEMORY, dwSizeNeeded );

   if ( lpInfo != NULL ) {
         if (opt & OPT_UNICODE) {
            ret=EnumPrintersW ( PRINTER_ENUM_NAME,(wchar_t *)lpName,level,(LPBYTE)lpInfo,dwSizeNeeded,&dwSizeNeeded,&n);
         } else {
            ret=EnumPrintersA ( PRINTER_ENUM_NAME,(char *)lpName,level,(LPBYTE)lpInfo,dwSizeNeeded,&dwSizeNeeded,&n);
         }
      if (  ret== 0 )
	   {
#ifdef _DBG_
		   printf ( "EnumPrintersX() Failed. Error: %d ( %i)\n",GetLastError(),dwSizeNeeded  );
#endif
         HeapFree ( GetProcessHeap (), 0, lpInfo );
		   return 0;
      } else {
         PRINTER_INFO_1 *dataI;
         PRINTER_INFO_2 *dataII;
         
	      for ( i=0; i < n; i++ ) {
               dataI=(PRINTER_INFO_1*)lpInfo;
             
               printf("%s",padding);
               if (opt & OPT_UNICODE) {
                  if (dataI[i].pName)  printf(" %S - ",(dataI[i].pName));
                  if (dataI[i].pDescription)  printf(" %S ",(dataI[i].pDescription));
                  //if (dataI[i].pComment)  printf(" %S - ",(dataI[i].pComment));
               } else {
                  if (dataI[i].pName)  printf(" %s - ",(dataI[i].pName));
                  if (dataI[i].pDescription)  printf(" %s ",(dataI[i].pDescription));
                  //if (dataI[i].pComment)  printf(" %s - ",(dataI[i].pComment));
               }
                  printf("\n");
              for(j=0;j<sizeof(CustomFuzzSize)/sizeof(int);j++) {
                 if (opt & OPT_UNICODE) {
                    Fuzzer( (wchar_t *) dataI[0].pName, j,opt & OPT_UNICODE);
                    ShowPrinterInfo((wchar_t*)dst,level, OPT_UNICODE, newpadding);            
                 } else {
                    Fuzzer( (wchar_t *) dataI[0].pName, j,opt & OPT_UNICODE);
                     ShowPrinterInfo((wchar_t*)dst,level, 0, newpadding);            
                 }
               }
               if (opt & RECURSIVE ) {
                  strcpy (newpadding,padding);
                  strcat(newpadding,"---");
                  newpadding[1]='+';
                  ShowPrinterInfo(dataI[i].pName,level, opt, newpadding);
               }
               printf("\n");
         }
         HeapFree ( GetProcessHeap (), 0, lpInfo );
      }
   }

   return(1);
}