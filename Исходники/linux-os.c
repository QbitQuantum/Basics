void
os_init(char *argv[], char *envp[])
{
    /* Conduct various version checks: do we have enough mmap(), is
     * this a sparc running 2.2, can we do threads? */
    struct utsname name;
    int major_version;
    int minor_version;
    int patch_version;
    char *p;
    uname(&name);

    p=name.release;
    major_version = atoi(p);
    minor_version = patch_version = 0;
    p=strchr(p,'.');
    if (p != NULL) {
            minor_version = atoi(++p);
            p=strchr(p,'.');
            if (p != NULL)
                    patch_version = atoi(++p);
    }

    if (major_version<2) {
        lose("linux kernel version too old: major version=%d (can't run in version < 2.0.0)\n",
             major_version);
    }
    if (!(major_version>2 || minor_version >= 4)) {
#ifdef LISP_FEATURE_SPARC
        FSHOW((stderr,"linux kernel %d.%d predates 2.4;\n enabling workarounds for SPARC kernel bugs in signal handling.\n", major_version,minor_version));
        linux_sparc_siginfo_bug = 1;
#endif
    }
#ifdef LISP_FEATURE_SB_THREAD
#if defined(LISP_FEATURE_SB_FUTEX) && !defined(LISP_FEATURE_SB_PTHREAD_FUTEX)
    futex_init();
#endif
    if(! isnptl()) {
       lose("This version of SBCL only works correctly with the NPTL threading\n"
            "library. Please use a newer glibc, use an older SBCL, or stop using\n"
            "LD_ASSUME_KERNEL\n");
    }
#endif

    /* Don't use getpagesize(), since it's not constant across Linux
     * kernel versions on some architectures (for example PPC). FIXME:
     * possibly the same should be done on other architectures too.
     */
    os_vm_page_size = BACKEND_PAGE_BYTES;

    /* KLUDGE: Disable memory randomization on new Linux kernels
     * by setting a personality flag and re-executing. (We need
     * to re-execute, since the memory maps that can conflict with
     * the SBCL spaces have already been done at this point).
     *
     * Since randomization is currently implemented only on x86 kernels,
     * don't do this trick on other platforms.
     */
#if defined(LISP_FEATURE_X86) || defined(LISP_FEATURE_X86_64)
    if ((major_version == 2
         /* Some old kernels will apparently lose unsupported personality flags
          * on exec() */
         && ((minor_version == 6 && patch_version >= 11)
             || (minor_version > 6)
             /* This is what RHEL 3 reports */
             || (minor_version == 4 && patch_version > 20)))
        || major_version >= 3)
    {
        int pers = personality(0xffffffffUL);
        /* 0x40000 aka. ADDR_NO_RANDOMIZE */
        if (!(pers & 0x40000)) {
            int retval = personality(pers | 0x40000);
            /* Allegedly some Linux kernels (the reported case was
             * "hardened Linux 2.6.7") won't set the new personality,
             * but nor will they return -1 for an error. So as a
             * workaround query the new personality...
             */
            int newpers = personality(0xffffffffUL);
            /* ... and don't re-execute if either the setting resulted
             * in an error or if the value didn't change. Otherwise
             * this might result in an infinite loop.
             */
            if (retval != -1 && newpers != pers) {
                /* Use /proc/self/exe instead of trying to figure out
                 * the executable path from PATH and argv[0], since
                 * that's unreliable. We follow the symlink instead of
                 * executing the file directly in order to prevent top
                 * from displaying the name of the process as "exe". */
                char runtime[PATH_MAX+1];
                int i = readlink("/proc/self/exe", runtime, PATH_MAX);
                if (i != -1) {
                    runtime[i] = '\0';
                    execve(runtime, argv, envp);
                }
            }
            /* Either changing the personality or execve() failed. Either
             * way we might as well continue, and hope that the random
             * memory maps are ok this time around.
             */
            fprintf(stderr, "WARNING: Couldn't re-execute SBCL with the proper personality flags (maybe /proc isn't mounted?). Trying to continue anyway.\n");
        }
    }
#ifdef LISP_FEATURE_X86
    /* Use SSE detector.  Recent versions of Linux enable SSE support
     * on SSE capable CPUs.  */
    /* FIXME: Are there any old versions that does not support SSE?  */
    fast_bzero_pointer = fast_bzero_detect;
#endif
#endif
}