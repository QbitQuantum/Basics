/* load a single input file */
static int load_file( const char *input_name, const char *output_name )
{
    int ret;

    /* Run the preprocessor on the input */
    if(!no_preprocess)
    {
        FILE *output;
        int ret, fd;
        char *name;

        /*
         * Preprocess the input to a temp-file, or stdout if
         * no output was given.
         */

        if (preprocess_only)
        {
            if (output_name)
            {
                if (!(output = fopen( output_name, "w" )))
                    fatal_perror( "Could not open %s for writing", output_name );
                ret = wpp_parse( input_name, output );
                fclose( output );
            }
            else ret = wpp_parse( input_name, stdout );

            if (ret) return ret;
            output_name = NULL;
            exit(0);
        }

        if (output_name && output_name[0]) name = strmake( "%s.XXXXXX", output_name );
        else name = xstrdup( "wrc.XXXXXX" );

        if ((fd = mkstemps( name, 0 )) == -1)
            error("Could not generate a temp name from %s\n", name);

        temp_name = name;
        if (!(output = fdopen(fd, "wt")))
            error("Could not open fd %s for writing\n", name);

        ret = wpp_parse( input_name, output );
        fclose( output );
        if (ret) return ret;
        input_name = name;
    }

    /* Reset the language */
    currentlanguage = dup_language( defaultlanguage );
    check_utf8 = 1;

    /* Go from .rc to .res */
    chat("Starting parse\n");

    if(!(parser_in = fopen(input_name, "rb")))
        fatal_perror("Could not open %s for input", input_name);

    ret = parser_parse();
    fclose(parser_in);
    parser_lex_destroy();
    if (temp_name)
    {
        unlink( temp_name );
        temp_name = NULL;
    }
    free( currentlanguage );
    return ret;
}