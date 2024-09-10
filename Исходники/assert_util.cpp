    NOINLINE_DECL void verifyFailed(const char *msg, const char *file, unsigned line) {
        assertionCount.condrollover( ++assertionCount.regular );
        problem() << "Assertion failure " << msg << ' ' << file << ' ' << dec << line << endl;
        logContext();
        setLastError(0,msg && *msg ? msg : "assertion failure");
        stringstream temp;
        temp << "assertion " << file << ":" << line;
        AssertionException e(temp.str(),0);
        breakpoint();
#if defined(_DEBUG) || defined(_DURABLEDEFAULTON) || defined(_DURABLEDEFAULTOFF)
        // this is so we notice in buildbot
        log() << "\n\n***aborting after verify() failure as this is a debug/test build\n\n" << endl;
        abort();
#endif
        throw e;
    }