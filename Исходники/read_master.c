/* ---------------------------------------------------------------- */
void
ScheduleAsyncRead(struct httpd_conn *hc, int startByte, int length)
{
  int i;
  httpd_conn *walk;
  httpd_conn *tail = NULL;
  int newSlave;

  mainStats.cs_numReadBlocks++;

  SetSelectHandler(hc->hc_fd, NULL, SSH_NOTHING);

  /* although we store start and length, we can assume
     that if it has the same start, it has the same length */

  hc->hc_asyncReadLen = length;
  hc->hc_asyncByteRead = startByte;
  hc->hc_next = NULL;
  hc->hc_siblings = NULL;

  /* we can compare the actual cache entry, since all connections
     for the same file should share the same entry */

  /* try to join with current reader */
  for (i = 0; i < numActiveReadSlaves; i++) {
    if (helperInfo[i].hi_hc && 
	helperInfo[i].hi_hc->hc_asyncByteRead == startByte &&
	helperInfo[i].hi_hc->hc_cacheEnt == hc->hc_cacheEnt) {
      hc->hc_siblings = helperInfo[i].hi_hc->hc_siblings;
      helperInfo[i].hi_hc->hc_siblings = hc;
      return;
    }
  }

  /* get free spot if one's open */
  for (i = 0; i < numActiveReadSlaves; i++) {
    if (!helperInfo[i].hi_hc) {
      AddCurrentReader(hc, i);
      return;
    }
  }

  /* try to join with waiting list */
  for (walk = waitingList; walk; walk = walk->hc_next) {
    if (walk->hc_asyncByteRead == startByte &&
	walk->hc_cacheEnt == hc->hc_cacheEnt) {
      hc->hc_siblings = walk->hc_siblings;
      walk->hc_siblings = hc;
      return;
    }
    tail = walk;
  }

  /* create a new slave if we've got free spots 
     and if the timing works */

  newSlave = FALSE;
  if (!numActiveReadSlaves) 
    newSlave = TRUE;
  else if (numActiveReadSlaves >= maxReadHelp)
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

    i = numActiveReadSlaves;
    helperInfo[i].hi_fd = CreateGenericSlave(readSlaveName);
    if (helperInfo[i].hi_fd >= 0) {
      numActiveReadSlaves++;
      AddCurrentReader(hc, i);
      return;
    }
    else {
      fprintf(stderr, "failed in lazy fork for %s\n", readSlaveName);
      if (!numActiveReadSlaves)
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