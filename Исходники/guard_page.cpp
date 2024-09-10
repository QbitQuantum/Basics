void main(void)
 {  
    // local variables LPVOID lpvAddr; DWORD cbSize; BOOL vLock; LPVOID commit;  
    // amount of memory we'll allocate cbSize = 512;  
    // try to allocate some memory 

    lpvAddr = VirtualAlloc(NULL,cbSize,MEM_RESERVE,PAGE_NOACCESS);  
    // failed ...
	if(lpvAddr == NULL) 
	  fprintf(stdout,"VirtualAlloc failed on RESERVE with %ld\n", GetLastError());

	// try to commit the allocated memory 
	commit = VirtualAlloc(NULL,cbSize,MEM_COMMIT,PAGE_READONLY|PAGE_GUARD); 

	// failed ...
	if(commit == NULL) 
		fprintf(stderr,"VirtualAlloc failed on COMMIT with %ld\n", GetLastError()); 
	else					// success!
		fprintf(stderr,"Committed %lu bytes at address %lp\n", cbSize,commit);
		
	// try to lock the committed memory 
	vLock = VirtualLock(commit,cbSize);
	
	// failed ...
	
	if(!vLock) 
		fprintf(stderr,"Cannot lock at %lp, error = %lu\n", commit,GetLastError()); 
	else					// success!
		fprintf(stderr,"Lock Achieved at %lp\n",commit);  

	// try to lock the committed memory again
	vLock = VirtualLock(commit,cbSize);
	  
	// failed ... 
	if(!vLock) 
		fprintf(stderr,"Cannot get 2nd lock at %lp, error = %lu\n", commit,GetLastError());
	else  // success!
		fprintf(stderr,"2nd Lock Achieved at %lp\n",commit);
}