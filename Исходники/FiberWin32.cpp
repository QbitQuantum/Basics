 static void MainThreadInit()
 {            
     PVOID pData = GetCurrentFiber();
     if (pData == (void*)0x1E00)  // magic
     {
         LPVOID h = ConvertThreadToFiber( &MainFiberId );
         ESS_ASSERT(h != 0);
         ESS_ASSERT( GetFiberData() == &MainFiberId );
     }
 }