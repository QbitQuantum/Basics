void *MakeCurrentScreenThread(void *arg)
{
    MakeCurrentScreenThreadArgs *t;
    int i;
    int ret = 0;
    GLXContext *ctxs;
    struct window_info *wi;
    int screen, offset;
    int firstScreen, numScreens;
    char *vendor;

    struct {
        GLint req;
        GLboolean saw;
        void *ret;
    } makeCurrentTestResultsParams;

    t = (MakeCurrentScreenThreadArgs *)arg;
    wi = t->wi;
    ctxs = t->ctxs;
    numScreens = t->numScreens;
    firstScreen = t->firstScreen;

    for (i = 0; i < t->iterations; i++) {
        for (offset = 0; offset < numScreens; offset++) {
            screen = (firstScreen + offset) % numScreens;
            FAILIF(!glXMakeContextCurrent(wi[screen].dpy,
                                          wi[screen].win,
                                          wi[screen].win,
                                          ctxs[screen]),
                   "Failed to make current!\n");

            // Make a call to glMakeCurrentTestResults() to get the vendor
            // string.
            makeCurrentTestResultsParams.req = GL_MC_VENDOR_STRING;
            makeCurrentTestResultsParams.saw = GL_FALSE;
            makeCurrentTestResultsParams.ret = NULL;

            pMakeCurrentTestResults(makeCurrentTestResultsParams.req,
                                    &makeCurrentTestResultsParams.saw,
                                    &makeCurrentTestResultsParams.ret);

            FAILIF(!makeCurrentTestResultsParams.saw, "Failed to dispatch!\n");
            FAILIF(!makeCurrentTestResultsParams.ret, "No vendor string!\n");

            vendor = (char *)makeCurrentTestResultsParams.ret;

            DBG_PRINTF(0, "Screen %d has vendor \"%s\"\n", screen, vendor);

            if (strcmp(vendor, t->vendorNames[screen])) {
                printError("Vendor string mismatch on screen %d: "
                           "expected \"%s\", got \"%s\"\n",
                           screen, t->vendorNames[screen], vendor);
                ret = 1;
            }

            free(vendor);


            if (!(i % 2)) {
                // Test losing current as well
                FAILIF(!glXMakeContextCurrent(wi[screen].dpy,
                                              None,
                                              None,
                                              NULL),
                       "Failed to lose current!\n");
            }
            // TODO pthread_barrier_wait(nextScreenBarrier);
        }
    }
cleanup:
    return (void *)((uintptr_t)ret);
}