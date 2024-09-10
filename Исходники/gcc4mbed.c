/* CRT initialization code called from Reset_Handler after it calls SystemInit() */
extern "C" __attribute__ ((section(".mbed_init"))) void __main(void)
{
    unsigned long*  pulDest;
    unsigned long*  pulSrc;
    int             ExitCode;

    /* Copy the data segment initializers from flash to SRAM in ROM mode if needed */
    if (&_sidata != &_sdata)	// only if needed
    {
        pulSrc = &_sidata;
        for(pulDest = &_sdata; pulDest < &_edata; ) 
        {
            *(pulDest++) = *(pulSrc++);
        }
    }

    /* Copy the .fastcode code from ROM to SRAM if needed */
    if (&_sifastcode != &_sfastcode) 
    {
        pulSrc = &_sifastcode;
        for(pulDest = &_sfastcode; pulDest < &_efastcode; ) 
        {
            *(pulDest++) = *(pulSrc++);
        }
    }

    /* Zero fill the bss segment. */
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    /* Initialize stdin/stdout/stderr file handles. */
    if (!MRI_SEMIHOST_STDIO && !GCC4MBED_DELAYED_STDIO_INIT)
    {
        __GCC4MBEDOpenStandardHandles();
    }
    
    if (MRI_ENABLE)
    {
        __mriInit(MRI_INIT_PARAMETERS);
        if (MRI_BREAK_ON_INIT)
        {
            __debugbreak();
        }
    }

    /* Initialize static constructors. */
     __libc_init_array();

    /* Call the application's entry point. */
    ExitCode = main();
    
    /* Call exit */
    exit(ExitCode);
}