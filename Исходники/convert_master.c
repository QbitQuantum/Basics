/* ---------------------------------------------------------------- */
void
ScheduleNameConversion(struct httpd_conn *hc)
{
    int i;
    httpd_conn *walk;
    httpd_conn *tail = NULL;
    int newSlave;

    mainStats.cs_numConvBlocks++;

    SetSelectHandler(hc->hc_fd, NULL, SSH_NOTHING);

    hc->hc_next = NULL;
    hc->hc_siblings = NULL;

    /* try to join with current reader */
    for (i = 0; i < numActiveConvSlaves; i++) {
        if (helperInfo[i].hi_hc &&
                (!strcmp(helperInfo[i].hi_hc->hc_stripped, hc->hc_stripped))) {
            hc->hc_siblings = helperInfo[i].hi_hc->hc_siblings;
            helperInfo[i].hi_hc->hc_siblings = hc;
            return;
        }
    }

    /* get free spot if one's open */
    for (i = 0; i < numActiveConvSlaves; i++) {
        if (!helperInfo[i].hi_hc) {
            AddCurrentReader(hc, i);
            return;
        }
    }

    /* try to join with waiting list */
    for (walk = waitingList; walk; walk = walk->hc_next) {
        if (!strcmp(hc->hc_stripped, walk->hc_stripped)) {
            hc->hc_siblings = walk->hc_siblings;
            walk->hc_siblings = hc;
            return;
        }
        tail = walk;
    }

    /* create a new slave if we've got free spots
       and if the timing works */

    newSlave = FALSE;
    if (!numActiveConvSlaves)
        newSlave = TRUE;
    else if (numActiveConvSlaves >= maxConvHelp)
        newSlave = FALSE;		/* basically a no-op, but easy to read */
    else if (slaveDelayTime) {
        if (timeWaitListStarted.tv_sec &&
                (DiffTime(&timeWaitListStarted, &globalTimeOfDay) >= slaveDelayTime))
            newSlave = TRUE;
    }
    else
        newSlave = TRUE;

    if (newSlave) {
        timeWaitListStarted = globalTimeOfDay;

        i = numActiveConvSlaves;
        helperInfo[i].hi_fd = CreateGenericSlave(convSlaveName);
        if (helperInfo[i].hi_fd >= 0) {
            numActiveConvSlaves++;
            AddCurrentReader(hc, i);
            return;
        }
        else {
            fprintf(stderr, "failed in lazy fork for %s\n", convSlaveName);
            if (!numActiveConvSlaves)
                exit(-1);
        }
    }

    /* go to end of list */
    if (tail)
        tail->hc_next = hc;
    else {
        waitingList = hc;
        timeWaitListStarted = globalTimeOfDay;
    }
}