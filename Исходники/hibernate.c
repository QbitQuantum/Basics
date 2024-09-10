int __cdecl main(int argc,char **argv)
{
    int i, now = 0;

    for(i = 1; i < argc; i++){
        if(!_stricmp(argv[i],"now"))
            now = 1;
    }

    if(now == 0){
        show_help();
        return EXIT_SUCCESS;
    }

    printf("Hibernate for Windows - a command line tool for Windows hibernation.\n");
    printf("Copyright (c) UltraDefrag Development Team, 2009-2013.\n\n");
    
    if(winx_init_library() < 0){
        fprintf(stderr,"Initialization failed!\n");
        return EXIT_FAILURE;
    }

    if(winx_enable_privilege(SE_SHUTDOWN_PRIVILEGE) < 0){
        fprintf(stderr,"Cannot enable shutdown privilege!\n"
            "Use DbgView program to get more information.\n");
        return EXIT_FAILURE;
    }

    /* hibernate, request permission from apps and drivers */
    if(!SetSuspendState(TRUE,FALSE,FALSE)){
        letrace("cannot hibernate the computer");
        fprintf(stderr,"Cannot hibernate the computer!\n"
            "Use DbgView program to get more information.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}