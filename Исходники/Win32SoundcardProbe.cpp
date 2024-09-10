/*----------------------------------------------------------------------
|    main
+---------------------------------------------------------------------*/
int
main(int argc, char** argv)
{
    bool no_pcm = false;
    if (argc >= 2 && !strcmp(argv[1], "--no-pcm")) no_pcm = true;

    printf("------- Win32 Soundcard Probe ------ built " __DATE__ "\n");
    unsigned int num_devs = waveOutGetNumDevs(); 
    printf("Found %d devices\n", num_devs);
    for (unsigned int i=0; i<num_devs; i++) {
        ProbeDevice(i, no_pcm);
    }

}