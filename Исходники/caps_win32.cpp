int caps_loadtrack (uae_u16 *mfmbuf, uae_u16 *tracktiming, int drv, int track, int *tracklength, int *multirev, int *gapoffset, int *nextrev, bool sametrack)
{
    int len;
    struct CapsTrackInfoT2 ci;
    CapsRevolutionInfo  pinfo;

    if (tracktiming)
        *tracktiming = 0;

    if (nextrev && pCAPSSetRevolution) {
        if (sametrack) {
            pCAPSSetRevolution(caps_cont[drv], *nextrev);
#if LOG_REVOLUTION
            write_log(_T("%03d set rev = %d\n"), track, *nextrev);
#endif
        } else {
            pCAPSSetRevolution(caps_cont[drv], 0);
#if LOG_REVOLUTION
            write_log(_T("%03d clear rev\n"), track, *nextrev);
#endif
        }
    }

    if (!load (&ci, drv, track, true, sametrack != true))
        return 0;

    if (pCAPSGetInfo) {
        if (nextrev)
            *nextrev = 0;
        pCAPSGetInfo(&pinfo, caps_cont[drv], track / 2, track & 1, cgiitRevolution, 0);
#if LOG_REVOLUTION
        write_log(_T("%03d get next rev = %d\n"), track, pinfo.next);
#endif
        if (nextrev && sametrack && pinfo.max > 0)
            *nextrev = pinfo.next;
    }

    *multirev = (ci.type & CTIT_FLAG_FLAKEY) ? 1 : 0;
    if (oldlib) {
        len = ci.tracklen * 8;
        *gapoffset = ci.overlap >= 0 ? ci.overlap * 8 : -1;
    } else {
        len = ci.tracklen;
        *gapoffset = ci.overlap >= 0 ? ci.overlap : -1;
    }
    //write_log (_T("%d %d %d %d\n"), track, len, ci.tracklen, ci.overlap);
    *tracklength = len;
    mfmcopy (mfmbuf, ci.trackbuf, len);
#if 0
    {
        FILE *f=fopen("c:\\1.txt","wb");
        fwrite (ci.trackbuf, len, 1, f);
        fclose (f);
    }
#endif
#if CAPS_TRACKTIMING
    if (ci.timelen > 0 && tracktiming) {
        for (int i = 0; i < ci.timelen; i++)
            tracktiming[i] = (uae_u16)ci.timebuf[i];
    }
#endif
#if 0
    write_log (_T("caps: drive:%d track:%d len:%d multi:%d timing:%d type:%d overlap:%d\n"),
               drv, track, len, *multirev, ci.timelen, type, ci.overlap);
#endif
    return 1;
}