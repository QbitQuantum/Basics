chat_query_user(char *cbuf)
{
  ACCOUNT acct;
  char buf[80];
  int in_now = 0;
  while (*cbuf && !isspace(*cbuf)) cbuf++;
  while (*cbuf && isspace(*cbuf)) cbuf++;
  strip_trailing_space(cbuf);
  if (!HasPerm(C_QUERY)) {
    printchatline("*** You do not have permission to query");
    return 0;
  }
  if (*cbuf == '\0') {
    printchatline("*** You must specify a userid to query");
    return 0;
  }
  if (bbs_query(cbuf, &acct) != S_OK) {
    sprintf(buf, "*** Userid '%s' not found", cbuf);
    printchatline(buf);
    return 0;
  }     
  bbs_enum_users(20, 0, acct.userid, _query_if_logged_in, &in_now);
  printchatline("***");
  sprintf(buf, "*** %s (%s):", acct.userid, acct.username);
  printchatline(buf);
  if (acct.lastlogin == 0)
    strcpy(buf, "*** Never logged in.");
  else sprintf(buf, "*** %s from %s %s %s", 
               in_now ? "Logged in" : "Last login", 
               acct.fromhost, in_now ? "since" : "at", 
               Ctime((time_t *)&acct.lastlogin));
  printchatline(buf);
  if (acct.realname[0] != '\0') {
    sprintf(buf, "*** Real name: %s", acct.realname);
    printchatline(buf);
  }
  return 0;
}