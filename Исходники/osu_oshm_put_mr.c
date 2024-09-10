int
main (int argc, char *argv[])
{
    struct pe_vars v;
    char * msg_buffer, * aligned_buffer;
    long alignment;
    int use_heap;

    /*
     * Initialize
     */
    v = init_openshmem();
    check_usage(v.me, v.npes, argc, argv);
    print_header(v.me);

    /*
     * Allocate Memory
     */
    use_heap = !strncmp(argv[1], "heap", 10);
    alignment = use_heap ? sysconf(_SC_PAGESIZE) : 4096;
    msg_buffer = allocate_memory(v.me, alignment, use_heap);
    aligned_buffer = align_memory((unsigned long)msg_buffer, alignment);
    memset(aligned_buffer, 0, MAX_MSG_SZ * ITERS_LARGE);

    /*
     * Time Put Message Rate
     */
    benchmark(v, aligned_buffer);

    /*
     * Finalize
     */
    if (use_heap) {
        shfree(msg_buffer);
    }
    
    return EXIT_SUCCESS;
}