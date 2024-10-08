int main()
{
    char			passwd[GTM_PASSPHRASE_MAX], hex_out[GTM_PASSPHRASE_MAX * 2], mumps_exe[GTM_PATH_MAX], *env_ptr;
    struct stat		stat_info;
    gtm_string_t		passwd_str;
    struct sigaction	reset_term_handler, ignore_handler;
    int			sig;

    /* Since the obfuscated password depends on $USER and the inode of $gtm_dist/mumps, make sure all the pre-requisites are
     * available to this process.
     */
    if (NULL == (env_ptr = (char *)getenv(USER_ENV)))
    {
        printf(ENV_UNDEF_ERROR "\n", USER_ENV);
        exit(EXIT_FAILURE);
    }
    if (NULL == (env_ptr = (char *)getenv(GTM_DIST_ENV)))
    {
        printf(ENV_UNDEF_ERROR "\n", GTM_DIST_ENV);
        exit(EXIT_FAILURE);
    }
    SNPRINTF(mumps_exe, GTM_PATH_MAX, "%s/%s", env_ptr, "mumps");
    if (0 != stat(mumps_exe, &stat_info))
    {
        printf("Cannot stat %s\n", mumps_exe);
        exit(EXIT_FAILURE);
    }
    /* We want the process to restore the terminal settings (if they already changed by the time a signal is caught) on the more
     * conventional terminal signals, such as SIGINT and SIGTERM, and ignore the non-critical other ones. We also do not want to
     * allow putting the process in the background because the terminal settings may be unsuitable for user interaction at that
     * point, and the user may decide to "sanitize" them, which might render the entered password visible upon resumption.
     */
    reset_term_handler.sa_handler = maskpass_signal_handler;
    reset_term_handler.sa_flags = 0;
    sigfillset(&reset_term_handler.sa_mask);
    ignore_handler.sa_handler = SIG_IGN;
    ignore_handler.sa_flags = 0;
    sigemptyset(&ignore_handler.sa_mask);
    for (sig = 1; sig <= NSIG; sig++)
    {
        switch (sig)
        {
        case SIGINT:
        case SIGTERM:
            sigaction(sig, &reset_term_handler, NULL);
            break;
        case SIGSEGV:
        case SIGABRT:
        case SIGBUS:
        case SIGFPE:
        case SIGTRAP:
        case SIGKILL:
            break;
        default:
            sigaction(sig, &ignore_handler, NULL);
        }
    }
    /* Read the password (with terminal echo turned off). */
    if (-1 == gc_read_passwd(GTMCRYPT_DEFAULT_PASSWD_PROMPT, passwd, GTM_PASSPHRASE_MAX, &tty))
    {
        printf("%s\n", gtmcrypt_err_string);
        exit(EXIT_FAILURE);
    }
    /* Obfuscate the password. */
    passwd_str.address = &passwd[0];
    passwd_str.length = (int)STRLEN(passwd);
    if (-1 == gc_mask_unmask_passwd(2, &passwd_str, &passwd_str))
    {
        printf("%s\n", gtmcrypt_err_string);
        exit(EXIT_FAILURE);
    }
    /* Convert obfuscated password to a hex representation for easy viewing. */
    GC_HEX(passwd, hex_out, passwd_str.length * 2);
    printf("%s\n", hex_out);
    return 0;
}