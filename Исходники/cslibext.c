int
CSDPSInit(
    Display *dpy,
    int *numberType,		/* RETURN */
    char **floatingName)	/* RETURN */
{
    register Display *agent;
    register xCAPConnReplyPrefix *p;
    register char *c;
    DPSCAPData my;
    xCAPConnSetupReq setup;
    union {
        xCAPConnSuccess good;
        xCAPConnFailed bad;
    } reply;
    XExtData *extData;
    XExtCodes *codes;
    int indian;
    int rest;
    Window clientWindow;
    char fullDisplayName[MAXHOSTNAMELEN+10];

    if (gCSDPS == NULL)
        DPSCAPStartUp();

    /* To fix dps-nx #68, Motif too slow on HP */
    if ((c = getenv("DPSNXGCMODE")) != 0)
        {
	gNXSyncGCMode = atoi(c);
	if (gNXSyncGCMode < DPSNXSYNCGCMODE_FLUSH
	  || gNXSyncGCMode > DPSNXSYNCGCMODE_DELAYED)
	    gNXSyncGCMode = DPSNXSYNCGCMODE_DEFAULT;
	}

    /* We may have already called this routine via XDPSExtensionPresent,
       so don't do it again! */

    if ((codes = XDPSLGetCodes(dpy))
        && (agent = XDPSLGetShunt(dpy))
        && agent != dpy
	&& codes->major_opcode == DPSXOPCODEBASE)
        return(DPSCAPSUCCESS);

    /* Try to create a window for ClientMessage communication */

    clientWindow = XCreateSimpleWindow(
      dpy,
      DefaultRootWindow(dpy),
      0, 0,
      1, 1,
      0,
      BlackPixel(dpy, DefaultScreen(dpy)),
      WhitePixel(dpy, DefaultScreen(dpy)));
    if (clientWindow == None)
        return(DPSCAPFAILED);

    /* Try to open a connection to an agent */

    if ((extData = DPSCAPOpenAgent(dpy, fullDisplayName)) == NULL)
        {
        XDestroyWindow(dpy, clientWindow);
        return(DPSCAPFAILED);
        }

    /* DPSCAPOpenAgent only partially fills in extData, so finish it */

    codes = XAddExtension(dpy);
    codes->major_opcode = DPSXOPCODEBASE;
    codes->first_event = 0;  /* REQUIRED */
    codes->first_error = FirstExtensionError;
    extData->number = codes->extension;
    extData->free_private = DPSCAPDestroy;
    my = (DPSCAPData) extData->private_data;
    my->codes = codes;
    agent = my->agent;
    /* +++ Is this all we have to do here? */

    /* Send opening handshake */

    indian = 1;
    if (*(char *) &indian)
        setup.byteorder = 'l';
    else
    	setup.byteorder = 'B';
    setup.dpscapVersion = DPSCAPPROTOVERSION;
    setup.flags = DPSCAPNONEFLAG;
    setup.libraryversion = DPSPROTOCOLVERSION;
    setup.authProtoNameLength = 0;
    setup.authProtoDataLength = 0;
    setup.displayStringLength = strlen(fullDisplayName);
    setup.nodeStringLength = 0;
    setup.transportStringLength = 0;
    setup.display = 0;
    setup.screen = 0;
    setup.reserved = 0;
    setup.clientWindow = clientWindow;

#ifndef DPSLNKL
    DPSCAPWrite(agent, (char *)&setup, sizeof(xCAPConnSetupReq), dpscap_nopad,dpscap_insert);
    DPSCAPWrite(agent, fullDisplayName, setup.displayStringLength, dpscap_pad, dpscap_append);
    N_XFlush(agent);
#else /* DPSLNKL */
    if (CSDPSConfirmDisplay(agent, dpy, &setup, &reply, fullDisplayName) == 1)
        {
	p = (xCAPConnReplyPrefix *)&reply.good;
        goto skip_read;
	}
    /* Read normal reply */
#endif /* DPSLNKL */

    /* Read common reply prefix */

    p = (xCAPConnReplyPrefix *)&reply.good;
    N_XRead(agent, (char *)p, (long)sizeof(xCAPConnReplyPrefix));
#ifdef DPSLNKL
skip_read:
#endif
    if (!p->success)
        {
	char mbuf[512];
        /* read the rest */
        c = (char *)&reply.bad.serverVersion;
        N_XRead(agent, c, sz_xCAPConnFailed - sz_xCAPConnReplyPrefix);
	sprintf(mbuf, "DPS NX: connection to \"%s\" refused by agent.", DisplayString(agent));
	DPSWarnProc(NULL, mbuf);
        c = (char *)Xmalloc(reply.bad.reasonLength);
        if (!c) return(DPSCAPFAILED);
        N_XReadPad(agent, c, (long)reply.bad.reasonLength);
	if (!reply.bad.reasonLength)
	    sprintf(mbuf, "DPS NX: (no reason given)\n");
	else
            {
	    strcpy(mbuf, "DPS NX: ");
	    strncat(mbuf, c, reply.bad.reasonLength);
	    mbuf[reply.bad.reasonLength+7] = '\0';
	    }
	DPSWarnProc(NULL, mbuf);
        Xfree(c);
        DPSCAPDestroy(extData);
        Xfree(extData);
        XDestroyWindow(dpy, clientWindow);
        return(DPSCAPFAILED);
        }

    /* read the rest of the fixed length reply */
    c = (char *)&reply.good.serverVersion;
    rest = sizeof(xCAPConnSuccess) - sizeof(xCAPConnReplyPrefix);
    N_XRead(agent, c, rest);

    /* verify */

    if (reply.good.serverVersion < DPSPROTOCOLVERSION)
        {
	/* Fine, we downgrade the client */
	char qbuf[256];
	sprintf(qbuf, "NX: server version %ld older than expected %d, client will downgrade", (long)reply.good.serverVersion, DPSPROTOCOLVERSION);
	DPSWarnProc(NULL, qbuf);
	}
    my->dpscapVersion = reply.good.dpscapVersion;
    if (my->dpscapVersion < DPSCAPPROTOVERSION)
        {
	/* Fine, we downgrade the client */
	char kbuf[256];
	sprintf(kbuf, "NX: agent version %d older than expected %d, client will downgrade", my->dpscapVersion, DPSCAPPROTOVERSION);
	DPSWarnProc(NULL, kbuf);
#ifdef XXX
        /* Saving this code as a reminder about what needs to be
	   cleaned up if we exit here */
        DPSCAPDestroy(extData);
        Xfree(extData);
        XDestroyWindow(clientWindow);
        return(DPSCAPFAILED);
#endif
	}

    if (numberType)
        *numberType = reply.good.preferredNumberFormat;

    /* read additional data */

    c = (char *)Xmalloc(reply.good.floatingNameLength + 1);
    N_XReadPad(agent, c, reply.good.floatingNameLength);
    c[reply.good.floatingNameLength] = 0;
    if (floatingName)
	*floatingName = c;
    else
	Xfree(c);

    /* set library extension data */

    XDPSLSetVersion(agent, reply.good.serverVersion);
    XDPSLSetVersion(dpy, reply.good.serverVersion);
    XDPSLSetShunt(dpy, agent);
    XDPSLSetCodes(dpy, codes);
    if (XDPSLGetSyncMask(dpy) == DPSCAP_SYNCMASK_NONE)
        XDPSLSetSyncMask(dpy, DPSCAP_SYNCMASK_DFLT);
    my->agentWindow = reply.good.agentWindow;
    XDPSLSetGCFlushMode(dpy, XDPSNX_GC_UPDATES_SLOW); /* default */

    /* Hook my extension data on the dpy */

    my->extData = extData;
    XAddToExtensionList(CSDPSHeadOfDpyExt(dpy), extData);
    (void) XESetCloseDisplay(dpy, codes->extension, DPSCAPCloseDisplayProc);
    (void) XESetCopyGC(dpy, codes->extension, DPSCAPCopyGCProc);
    (void) XESetFreeGC(dpy, codes->extension, DPSCAPFreeGCProc);
    (void) XESetFlushGC(dpy, codes->extension, DPSCAPFlushGCProc);
    XDPSLSetClientMessageHandler(dpy);

    /* Chain my data on global list */

    my->next = gCSDPS->head;
    gCSDPS->head = my;

#ifdef MAHALO
    /* Set function that is called after every Xlib protocol proc */
    XDPSLSetAfterProc(dpy);

    /* All CSDPS protocol is auto-flushed */
    (void) XSetAfterFunction(agent, DPSCAPFlushAfterProc);
#endif /* MAHALO */

    /* set agent arguments, if needed */
    /* must follow setting of ShuntMap at least, so safest to
       do here when everything has been setup */
    XDPSLUpdateAgentArgs(dpy);

    return(DPSCAPSUCCESS);
}