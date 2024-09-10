int rpmcliVerify(rpmts ts, QVA_t qva, char * const * argv)
{
    rpmVSFlags vsflags, ovsflags;
    int ec = 0;
    FD_t scriptFd = fdDup(STDOUT_FILENO);

    /* 
     * Open the DB + indices explicitly before possible chroot,
     * otherwises BDB is going to be unhappy...
     */
    rpmtsOpenDB(ts, O_RDONLY);
    rpmdbOpenAll(rpmtsGetRdb(ts));
    if (rpmChrootSet(rpmtsRootDir(ts)) || rpmChrootIn()) {
	ec = 1;
	goto exit;
    }

    if (qva->qva_showPackage == NULL)
        qva->qva_showPackage = showVerifyPackage;

    vsflags = rpmExpandNumeric("%{?_vsflags_verify}");
    vsflags |= rpmcliVSFlags;
    vsflags &= ~RPMVSF_NEEDPAYLOAD;

    rpmtsSetScriptFd(ts, scriptFd);
    ovsflags = rpmtsSetVSFlags(ts, vsflags);
    ec = rpmcliArgIter(ts, qva, argv);
    rpmtsSetVSFlags(ts, ovsflags);
    rpmtsSetScriptFd(ts, NULL);

    if (qva->qva_showPackage == showVerifyPackage)
        qva->qva_showPackage = NULL;

    rpmtsEmpty(ts);

    if (rpmChrootOut() || rpmChrootSet(NULL))
	ec = 1;

exit:
    Fclose(scriptFd);

    return ec;
}