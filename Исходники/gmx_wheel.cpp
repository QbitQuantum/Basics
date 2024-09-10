int gmx_wheel(int argc, char *argv[])
{
    const char     *desc[] = {
        "[THISMODULE] plots a helical wheel representation of your sequence.",
        "The input sequence is in the [REF].dat[ref] file where the first line contains",
        "the number of residues and each consecutive line contains a residue "
        "name."
    };
    output_env_t    oenv;
    static real     rot0  = 0;
    static gmx_bool bNum  = TRUE;
    static char    *title = NULL;
    static int      r0    = 1;
    t_pargs         pa [] = {
        { "-r0",  FALSE, etINT, {&r0},
          "The first residue number in the sequence" },
        { "-rot0", FALSE, etREAL, {&rot0},
          "Rotate around an angle initially (90 degrees makes sense)" },
        { "-T",   FALSE, etSTR, {&title},
          "Plot a title in the center of the wheel (must be shorter than 10 characters, or it will overwrite the wheel)" },
        { "-nn",  FALSE, etBOOL, {&bNum},
          "Toggle numbers" }
    };
    t_filenm        fnm[] = {
        { efDAT, "-f", NULL,  ffREAD  },
        { efEPS, "-o", NULL,  ffWRITE }
    };
#define NFILE asize(fnm)

    int    i, nres;
    char **resnm;

    if (!parse_common_args(&argc, argv, 0, NFILE, fnm, asize(pa), pa,
                           asize(desc), desc, 0, NULL, &oenv))
    {
        return 0;
    }

    for (i = 1; (i < argc); i++)
    {
        if (std::strcmp(argv[i], "-r0") == 0)
        {
            r0 = std::strtol(argv[++i], NULL, 10);
            fprintf(stderr, "First residue is %d\n", r0);
        }
        else if (std::strcmp(argv[i], "-rot0") == 0)
        {
            rot0 = strtod(argv[++i], NULL);
            fprintf(stderr, "Initial rotation is %g\n", rot0);
        }
        else if (std::strcmp(argv[i], "-T") == 0)
        {
            title = gmx_strdup(argv[++i]);
            fprintf(stderr, "Title will be '%s'\n", title);
        }
        else if (std::strcmp(argv[i], "-nn") == 0)
        {
            bNum = FALSE;
            fprintf(stderr, "No residue numbers\n");
        }
        else
        {
            gmx_fatal(FARGS, "Incorrect usage of option %s", argv[i]);
        }
    }

    nres = get_lines(ftp2fn(efDAT, NFILE, fnm), &resnm);
    if (bNum)
    {
        wheel(ftp2fn(efEPS, NFILE, fnm), nres, resnm, r0, rot0, title);
    }
    else
    {
        wheel2(ftp2fn(efEPS, NFILE, fnm), nres, resnm, rot0, title);
    }

    return 0;
}