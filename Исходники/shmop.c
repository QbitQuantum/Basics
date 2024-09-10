/*
  SYSTEM CALL: shmat();                                                          

  PROTOTYPE: int shmat ( int shmid, char *shmaddr, int shmflg);
    RETURNS: address at which segment was attached to the process, or
             -1 on error: errno = EINVAL (Invalid IPC ID value or attach address passed)
                                  ENOMEM (Not enough memory to attach segment)
                                  EACCES (Permission denied)
  NOTES:
If the addr argument is zero (0), the kernel tries to find an unmapped region. 
This is the recommended method. 
An address can be specified, but is typically only used to facilitate proprietary hardware 
or to resolve conflicts with other apps. 
The SHM_RND flag can be OR'd into the flag argument to force a passed address to be page aligned (rounds down to the nearest page size).
In addition, if the SHM_RDONLY flag is OR'd in with the flag argument, then the shared memory segment will be mapped in, but marked as readonly.

This call is perhaps the simplest to use. 
Consider this wrapper function, which is passed a valid IPC identifier for a segment, and returns the address that the segment was attached to:

char *attach_segment( int shmid )
{
        return(shmat(shmid, 0, 0));
}
Once a segment has been properly attached, and a process has a pointer to the start of that segment, 
reading and writing to the segment become as easy as simply referencing or dereferencing the pointer! 
Be careful not to lose the value of the original pointer! If this happens, you will have no way of accessing the base (start) of the segment.
*/
TSRM_API void *shmat(int shmid, const void *shmaddr, int shmflg) {	//void *shmat(int key, const void *shmaddr, int flags) {
	shm_pair *shm;
	if ((shm = shm_get(GET_IF_EXISTS_BY_KEY, shmid, NULL)) == NULL)	return (void*)-1;
	
	if (!shm->segment) {
		return (void*)-1;
	}

	shm->descriptor->shm_atime = time(NULL);
	shm->descriptor->shm_lpid  = getpid();
	shm->descriptor->shm_nattch++;

	shm->addr = MapViewOfFileEx(shm->segment, FILE_MAP_ALL_ACCESS, 0, 0, 0, NULL);

	return shm->addr;
}