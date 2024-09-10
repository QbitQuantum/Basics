DWORD WINAPI SimpleThreadHandler(PVOID pvParam) {
  
   WaitForSingleObject((HANDLE) pvParam, INFINITE);   

   return(0);
}