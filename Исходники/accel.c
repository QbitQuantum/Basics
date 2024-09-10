/*
 * @implemented
 */
int WINAPI CopyAcceleratorTableA
(
 HACCEL hAccelSrc,
 LPACCEL lpAccelDst, /* can be NULL */
 int cAccelEntries
)
{
   int i;

   cAccelEntries = CopyAcceleratorTableW(hAccelSrc, lpAccelDst, cAccelEntries);

   if (lpAccelDst == NULL) return cAccelEntries;

   for(i = 0; i < cAccelEntries; ++ i)
   if(!(lpAccelDst[i].fVirt & FVIRTKEY))
   {
      NTSTATUS nErrCode = RtlUnicodeToMultiByteN(
         (PCHAR)&lpAccelDst[i].key,
         sizeof(lpAccelDst[i].key),
         NULL,
         (PWCHAR)&lpAccelDst[i].key,
         sizeof(lpAccelDst[i].key)
         );

      if(!NT_SUCCESS(nErrCode)) lpAccelDst[i].key = 0;
   }

   return cAccelEntries;
}