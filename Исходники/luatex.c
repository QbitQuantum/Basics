main (int ac, string *av)
#endif
{
#  ifdef __EMX__
    _wildcard(&ac, &av);
    _response(&ac, &av);
#  endif

#  ifdef WIN32
#    ifdef _MSC_VER
    _set_invalid_parameter_handler(myInvalidParameterHandler);
#    endif
    av[0] = kpse_program_basename (av[0]);
    _setmaxstdio(2048);
/*
    We choose to crash for fatal errors:

    SetErrorMode (SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
*/
    setmode(fileno(stdin), _O_BINARY);
#  endif

    lua_initialize(ac, av);

#  ifdef WIN32
    if (ac > 1) {
        char *pp;
        if ((strlen(av[ac-1]) > 2) && isalpha(av[ac-1][0]) && (av[ac-1][1] == ':') && (av[ac-1][2] == '\\')) {
            for (pp=av[ac-1]+2; *pp; pp++) {
            if (IS_KANJI(pp)) {
                pp++;
                continue;
            }
            if (*pp == '\\')
                *pp = '/';
            }
        }
    }
#  endif

    /*
        Call the real main program.
    */
    main_body();

    return EXIT_SUCCESS;
}