static void heapdump()
{
   _HEAPINFO   hinfo;
   int         heapstatus;
   DWORD       used  = 0;
   DWORD       avail = 0;
   char        report[256];

   hinfo._pentry = NULL;
   while ((heapstatus = _heapwalk( &hinfo )) == _HEAPOK) { 
      sprintf_s(report, "%6s block at %Fp of size %4.4X\n",
               ( hinfo._useflag == _USEDENTRY ? "USED" : "FREE" ),
                 hinfo._pentry, hinfo._size);

      _RPT0(_CRT_WARN, report);

      if (hinfo._useflag == _USEDENTRY)
         used  += hinfo._size;
      else
         avail += hinfo._size;
   }

   sprintf_s(report, "------\nUsed Blocks:  %d\nAvail Blocks: %d\nTotal Blocks: %d\n", used, avail, used+avail);
   _RPT0(_CRT_WARN, report);

   switch (heapstatus) {
   case _HEAPEMPTY:
      _RPT0(_CRT_WARN,  "OK - empty heap\n" );
      break;
   case _HEAPEND:
      _RPT0(_CRT_WARN,  "OK - end of heap\n" );
      break;
   case _HEAPBADPTR:
      _RPT0(_CRT_WARN,  "ERROR - bad pointer to heap\n" );
      break;
   case _HEAPBADBEGIN:
      _RPT0(_CRT_WARN,  "ERROR - bad start of heap\n" );
      break;
   case _HEAPBADNODE:
      _RPT0(_CRT_WARN,  "ERROR - bad node in heap\n" );
      break;
   }
}