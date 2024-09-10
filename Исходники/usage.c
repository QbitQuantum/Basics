/*=export_func  optionUsage
 * private:
 *
 * what:  Print usage text
 * arg:   + tOptions * + opts + program options descriptor +
 * arg:   + int        + exitCode + exit code for calling exit(3) +
 *
 * doc:
 *  This routine will print usage in both GNU-standard and AutoOpts-expanded
 *  formats.  The descriptor specifies the default, but AUTOOPTS_USAGE will
 *  over-ride this, providing the value of it is set to either "gnu" or
 *  "autoopts".  This routine will @strong{not} return.
 *
 *  If "exitCode" is "AO_EXIT_REQ_USAGE" (normally 64), then output will to
 *  to stdout and the actual exit code will be "EXIT_SUCCESS".
=*/
void
optionUsage(tOptions * opts, int usage_exit_code)
{
    int exit_code = (usage_exit_code == AO_EXIT_REQ_USAGE)
        ? EXIT_SUCCESS : usage_exit_code;

    displayEnum = false;
    set_usage_flags(opts, NULL);

    /*
     *  Paged usage will preset option_usage_fp to an output file.
     *  If it hasn't already been set, then set it to standard output
     *  on successful exit (help was requested), otherwise error out.
     *
     *  Test the version before obtaining pzFullUsage or pzShortUsage.
     *  These fields do not exist before revision 30.
     */
    {
        char const * pz;

        if (exit_code == EXIT_SUCCESS) {
            pz = (opts->structVersion >= 30 * 4096)
                ? opts->pzFullUsage : NULL;

            if (option_usage_fp == NULL)
                option_usage_fp = print_exit ? stderr : stdout;

        } else {
            pz = (opts->structVersion >= 30 * 4096)
                ? opts->pzShortUsage : NULL;

            if (option_usage_fp == NULL)
                option_usage_fp = stderr;
        }

        if (((opts->fOptSet & OPTPROC_COMPUTE) == 0) && (pz != NULL)) {
            if ((opts->fOptSet & OPTPROC_TRANSLATE) != 0)
                optionPrintParagraphs(pz, true, option_usage_fp);
            else
                fputs(pz, option_usage_fp);
            goto flush_and_exit;
        }
    }

    fprintf(option_usage_fp, opts->pzUsageTitle, opts->pzProgName);

    if ((exit_code == EXIT_SUCCESS) ||
        (! skip_misuse_usage(opts)))

        print_usage_details(opts, usage_exit_code);
    else
        print_offer_usage(opts);
    
 flush_and_exit:
    fflush(option_usage_fp);
    if (ferror(option_usage_fp) != 0)
        fserr_exit(opts->pzProgName, zwriting, (option_usage_fp == stdout)
                   ? zstdout_name : zstderr_name);

    option_exits(exit_code);
}