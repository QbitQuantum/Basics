void do_text_program(void)
{
    int c, d, cols, lines;
    FILE *pipe = _popen(text_program, "w");
    if (pipe)
    {
        if (verbose)
            fprintf(stderr, "%s: running %s\n", progname, text_program);

        cols = lines = 0;
        d = EOF;
        while ((c = fgetc(pipe)) != EOF)
        {
            if (c == '\r')
                continue;

            if (nyarlathotep_p)
                c = do_nyarlathotep_char(c);

            if (c == '\n')
            {
                cols = 0;
                lines++;
                if (head >= 1 && lines >= head)
                {
                    putchar(c);
                    break;
                }
            }
            else
                cols++;

            putchar(c);
            if (wrap_columns && cols % wrap_columns == 0 && cols)
                putchar('\n');

            d = c;
        }
        _pclose(pipe);
        if (d != '\n')
            putchar('\n');
    }
    else
    {
        if (verbose)
            fprintf(stderr, "%s: ERROR: cannot open '%s'\n", progname, text_program);
    }
}