void RosettaPatchInstaller( struct _r_args *args,
                            unsigned int count,
                            void * flag_byte_addr )
{
    unsigned int i;
    for ( i = 0; i < count; i++ )
    {
        // value is big-endian already, addr is native
        *(args[i].addr) = args[i].valu;
#if defined(__ppc__) || defined(__ppc64__)
        __asm__ ( "isync" );
#elif defined(__i386__)
        _mm_clflush( (void *)(args[i].addr) );
#else
#error Unsupported architecture
#endif
    }

    *((unsigned char *) flag_byte_addr) = 0xFF;
    while ( 1 );
}