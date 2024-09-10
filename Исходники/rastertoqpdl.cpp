int main(int argc, char **argv)
{
    const char *jobid, *user, *title, *options, *ppdFile, *file;
    unsigned long copies;
    Request request;
    PPDFile ppd;


    // Check the given arguments
    if (argc != 6 && argc != 7) {
        fprintf(stderr, _("Usage: %s job-id user title copies options "
            "[file]\n"), argv[0]);
        return 1;
    }
    jobid = argv[1];
    user = argv[2];
    title = argv[3];
    options = argv[5];
    file = argc == 7 ? argv[6] : NULL;
    copies = strtol(argv[4], (char **)NULL, 10);
    ppdFile = getenv("PPD");


    // Get more information on the SpliX environment (for debugging)
    DEBUGMSG(_("SpliX filter V. %s by Aurélien Croc (AP²C)"), VERSION);
    DEBUGMSG(_("More information at: http://splix.ap2c.org"));
    DEBUGMSG(_("Compiled with: Threads=%s (#=%u, Cache=%u), JBIG=%s, "
        "BlackOptim=%s"), opt_threads ? _("enabled") : _("disabled"), 
        THREADS, CACHESIZE, opt_jbig ? _("enabled") : _("disabled"), 
        opt_blackoptim ? _("enabled") : _("disabled"));

    // Open the given file
    if (file && !freopen(file, "r", stdin)) {
        ERRORMSG(_("Cannot open file %s"), file);
        return errno;
    }

    // Open the PPD file
    if (!ppd.open(ppdFile, PPDVERSION, options))
        return 1;

    // Load the request
    if (!request.loadRequest(&ppd, jobid, user, title, copies))
        return 2;

#ifndef DISABLE_THREADS
    if (!initializeCache())
        return 3;
#endif /* DISABLE_THREADS */

    // Render the request
    if (!render(request)) {
        uninitializeCache();
        return 4;
    }

#ifndef DISABLE_THREADS
    if (!uninitializeCache())
        return 5;
#endif /* DISABLE_THREADS */

    return 0;
}