int
main(int argc, char **argv)
{
    void *p;
    com_result_t r;
    int n;
    size_t s;
    IMalloc *allocator;

    (void) argc;
    (void) argv;

    com_init("com.googlecode.libcom.test-1");

    p = CoTaskMemAlloc(64);
    if(NULL == p)
    {
        fprintf(stderr, "Failed to allocate 64 bytes via CoTaskMemAlloc()\n");
        exit(EXIT_FAILURE);
    }
    if(COM_S_OK != (r = CoGetMalloc(1, &allocator)))
    {
        fprintf(stderr, "Failed to obtain reference to task allocator; result = 0x%08x\n", r);
        exit(EXIT_FAILURE);
    }
    if(1 != (n = IMalloc_DidAlloc(allocator, p)))
    {
        if(0 == n)
        {
            fprintf(stderr, "IMalloc::DidAlloc() claims task allocator was not responsible for allocated block\n");
        }
        else
        {
            fprintf(stderr, "IMalloc::DidAlloc() could not determine responsibility for allocated block\n");
        }
        exit(EXIT_FAILURE);
    }
    if(64 != (s = IMalloc_GetSize(allocator, p)))
    {
        fprintf(stderr, "IMalloc::GetSize() returned an incorrect size (%ul bytes)\n", s);
        exit(EXIT_FAILURE);
    }
    IMalloc_Free(allocator, p);
    puts("PASS");

    com_shutdown();
    return 0;
}