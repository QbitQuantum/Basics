int rlMailbox::read(void *buf, int maxlen, int wait)
{
  char *cbuf;
  status = OK;
  cbuf = (char *) buf;

#ifdef RLUNIX
  int len;
  unsigned char *message = new unsigned char [sizeof(long) + maxlen];
  if(wait == WAIT ) len = msgrcv(chanid,(struct msgbuf *) message, maxlen,0,0);
  else              len = msgrcv(chanid,(struct msgbuf *) message, maxlen,0,IPC_NOWAIT);
  if(len < maxlen && len >= 0) 
  {
    memcpy(buf,&message[sizeof(long)],len);
    cbuf[len] = '\0';
  }
  else
  {
    cbuf[0] = '\0';
  }
  delete [] message;
  return len;
#endif

#ifdef __VMS
  int  ret,len;
  IOSB iosb;
  if(wait == NOWAIT)
  {
    ret = sys$qiow(0,
                   (short) chanid,
                   IO$_READVBLK | IO$M_NOW,       // I/O CODE
                   &iosb,
                   0,0,
                   buf,
                   maxlen,0,0,0,0);
  }
  else
  {
    ret = sys$qiow(0,
                   (short) chanid,
                   IO$_READVBLK,                  // I/O CODE
                   &iosb,
                   0,0,
                   buf,
                   maxlen,0,0,0,0);
  }
  len = (int) iosb.msg_len;
  if(len < maxlen && len >= 0) cbuf[len] = '\0';
  if     (ret == SS$_NORMAL && iosb.iostat == SS$_NORMAL)   return len;
  else if(iosb.iostat == SS$_NORMAL)                        { status = -1; return MAILBOX_ERROR; }
  else if(ret         == SS$_NORMAL)
  {
    if(wait == NOWAIT && iosb.iostat == SS$_ENDOFFILE)      { status = -2; return MAILBOX_ERROR; }
    else                                                    { status = -3; return MAILBOX_ERROR; }
  }
                                                              status = -4; return MAILBOX_ERROR;
#endif

#ifdef RLWIN32
  HANDLE h;
  char   mbxname[1024];
  unsigned long lenRead;
  BOOL   bret,bret2;

  if(chanid == -1)
  {
    strcpy(mbxname,"\\\\.\\mailslot\\"); strcat(mbxname,name);
    h = CreateMailslot(
                 mbxname,                // pointer to string for mailslot name
                 MAX_MAILBOX,            // maximum message size
                 MAILSLOT_WAIT_FOREVER,  // milliseconds before read time-out
                 NULL);                  // pointer to security structure
    if(h == INVALID_HANDLE_VALUE) { status = GetLastError(); return MAILBOX_ERROR; }
    chanid = (int) h;

    bret2 = SetMailslotInfo((HANDLE) chanid, MAILSLOT_WAIT_FOREVER);
    if(bret2 == 0) { status = GetLastError();  return MAILBOX_ERROR; }
  }

  if(wait == NOWAIT) // begin wait
  {
    lenRead = 0;
    bret2 = SetMailslotInfo((HANDLE) chanid, 0);
    if(bret2 == 0) { status = GetLastError(); return MAILBOX_ERROR; }
    bret = ReadFile(
             (HANDLE) chanid,                        // handle of file to read
             buf,                                    // pointer to buffer
             maxlen,                                 // number of bytes to read
             &lenRead,                               // pointer to number of bytes read
             NULL                                    // pointer to structure for data
                   );
    bret2 = SetMailslotInfo((HANDLE) chanid, MAILSLOT_WAIT_FOREVER);
    if(bret2 == 0) { status = GetLastError(); return MAILBOX_ERROR; }
    if(bret == 0)  { status = GetLastError(); return MAILBOX_ERROR; }
    if((int) lenRead < maxlen && (int) lenRead >= 0) cbuf[lenRead] = '\0';
    return lenRead;
  } // end wait

  lenRead = 0;
  bret = ReadFile(
           (HANDLE) chanid,                        // handle of file to read
           buf,                                    // pointer to buffer
           maxlen,                                 // number of bytes to read
           &lenRead,                               // pointer to number of bytes read
           NULL                                    // pointer to structure for data
                 );
  if(bret == 0) { status = GetLastError(); return MAILBOX_ERROR; }
  if((int) lenRead < maxlen && (int) lenRead >= 0) cbuf[lenRead] = '\0';
  return lenRead;
#endif
}