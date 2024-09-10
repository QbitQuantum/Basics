BOOL VMQuery(HANDLE hProcess, LPCVOID pvAddress, PVMQUERY pVMQ) {

   if (gs_dwAllocGran == 0) {
      // Set allocation granularity if this is the first call
      SYSTEM_INFO sinf;
      GetSystemInfo(&sinf);
      gs_dwAllocGran = sinf.dwAllocationGranularity;
   }

   ZeroMemory(pVMQ, sizeof(*pVMQ));

   // Get the MEMORY_BASIC_INFORMATION for the passed address.
   MEMORY_BASIC_INFORMATION mbi;
   BOOL bOk = (VirtualQueryEx(hProcess, pvAddress, &mbi, sizeof(mbi)) 
      == sizeof(mbi));

   if (!bOk)
      return(bOk);   // Bad memory address; return failure

   // The MEMORY_BASIC_INFORMATION structure contains valid information.
   // Time to start setting the members of our own VMQUERY structure.

   // First, fill in the block members. We'll fill the region members later.
   switch (mbi.State) {
      case MEM_FREE:       // Free block (not reserved)
         pVMQ->pvBlkBaseAddress = NULL;
         pVMQ->BlkSize = 0;
         pVMQ->dwBlkProtection = 0;
         pVMQ->dwBlkStorage = MEM_FREE;
         break;

      case MEM_RESERVE:    // Reserved block without committed storage in it.
         pVMQ->pvBlkBaseAddress = mbi.BaseAddress;
         pVMQ->BlkSize = mbi.RegionSize;

         // For an uncommitted block, mbi.Protect is invalid. So we will 
         // show that the reserved block inherits the protection attribute 
         // of the region in which it is contained.
         pVMQ->dwBlkProtection = mbi.AllocationProtect;  
         pVMQ->dwBlkStorage = MEM_RESERVE;
         break;

      case MEM_COMMIT:     // Reserved block with committed storage in it.
         pVMQ->pvBlkBaseAddress = mbi.BaseAddress;
         pVMQ->BlkSize = mbi.RegionSize;
         pVMQ->dwBlkProtection = mbi.Protect;   
         pVMQ->dwBlkStorage = mbi.Type;
         break;

      default:
          DebugBreak();
          break;
   }

   // Now fill in the region data members.
   VMQUERY_HELP VMQHelp;
   switch (mbi.State) {
      case MEM_FREE:       // Free block (not reserved)
         pVMQ->pvRgnBaseAddress = mbi.BaseAddress;
         pVMQ->dwRgnProtection  = mbi.AllocationProtect;
         pVMQ->RgnSize          = mbi.RegionSize;
         pVMQ->dwRgnStorage     = MEM_FREE;
         pVMQ->dwRgnBlocks      = 0;
         pVMQ->dwRgnGuardBlks   = 0;
         pVMQ->bRgnIsAStack     = FALSE;
         break;

      case MEM_RESERVE:    // Reserved block without committed storage in it.
         pVMQ->pvRgnBaseAddress = mbi.AllocationBase;
         pVMQ->dwRgnProtection  = mbi.AllocationProtect;

         // Iterate through all blocks to get complete region information.         
         VMQueryHelp(hProcess, pvAddress, &VMQHelp);

         pVMQ->RgnSize          = VMQHelp.RgnSize;
         pVMQ->dwRgnStorage     = VMQHelp.dwRgnStorage;
         pVMQ->dwRgnBlocks      = VMQHelp.dwRgnBlocks;
         pVMQ->dwRgnGuardBlks   = VMQHelp.dwRgnGuardBlks;
         pVMQ->bRgnIsAStack     = VMQHelp.bRgnIsAStack;
         break;

      case MEM_COMMIT:     // Reserved block with committed storage in it.
         pVMQ->pvRgnBaseAddress = mbi.AllocationBase;
         pVMQ->dwRgnProtection  = mbi.AllocationProtect;

         // Iterate through all blocks to get complete region information.         
         VMQueryHelp(hProcess, pvAddress, &VMQHelp);

         pVMQ->RgnSize          = VMQHelp.RgnSize;
         pVMQ->dwRgnStorage     = VMQHelp.dwRgnStorage;
         pVMQ->dwRgnBlocks      = VMQHelp.dwRgnBlocks;
         pVMQ->dwRgnGuardBlks   = VMQHelp.dwRgnGuardBlks;
         pVMQ->bRgnIsAStack     = VMQHelp.bRgnIsAStack;
         break;

      default:
          DebugBreak();
          break;
   }

   return(bOk);
}