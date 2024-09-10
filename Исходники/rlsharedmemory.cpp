int rlSharedMemory::deleteSharedMemory()
{
#ifdef RLUNIX
    struct shmid_ds buf;
    if(status != OK) return -1;
    //rlwthread_mutex_destroy(mutex);
    flock(fdlock,LOCK_UN);
    shmctl(id, IPC_RMID, &buf);
    _size = 0;
    return 0;
#endif

#ifdef __VMS
    int ret;
    ADD add_in,add_ret;
    struct dsc$descriptor_s section_name;

    if(status != OK) return -1;
    rlwthread_mutex_destroy(mutex);
    // Fill descriptor for section name
    section_name.dsc$w_length  = strlen(name);
    section_name.dsc$a_pointer = name;
    section_name.dsc$b_dtype   = DSC$K_DTYPE_T;
    section_name.dsc$b_class   = DSC$K_CLASS_S;
    // Delete the section
    ret = sys$dgblsc(0,&section_name,0);
    if(ret != SS$_NORMAL) return -1;
    // Fill the input address
    add_in.start = (long) base_adr;
    add_in.end   = (long) base_adr + _size;
    // Free the memory
    ret = sys$deltva(&add_in,&add_ret,0);
    if(ret != SS$_NORMAL) return -1;
    // Test the section addresses
    if(add_in.start != add_ret.start || add_in.end != add_ret.end) return -1;
    return 0;
#endif

#ifdef RLWIN32
    if(status != OK) return -1;
    //rlwthread_mutex_destroy(mutex);
    UnmapViewOfFile(base_adr);
    CloseHandle((HANDLE) id);
    CloseHandle((HANDLE) shmkey);
    UnlockFile(hSharedFile,0,0,_size,0); // Changed by FMakkinga 18-03-2013
    CloseHandle(hSharedFile);           // Changed by FMakkinga 18-03-2013
    status = ~OK;
    return 0;
#endif
}