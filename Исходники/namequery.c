/****************************************************************************
interpret a node status response
****************************************************************************/
static void _interpret_node_status(char *p, char *master,char *rname)
{
  int numnames = CVAL(p,0);
  DEBUG(1,("received %d names\n",numnames));

  if (rname) *rname = 0;
  if (master) *master = 0;

  p += 1;
  while (numnames--)
    {
      char qname[17];
      int type;
      fstring flags;
      int i;
      *flags = 0;
      StrnCpy(qname,p,15);
      type = CVAL(p,15);
      p += 16;

      fstrcat(flags, (p[0] & 0x80) ? "<GROUP> " : "        ");
      if ((p[0] & 0x60) == 0x00) fstrcat(flags,"B ");
      if ((p[0] & 0x60) == 0x20) fstrcat(flags,"P ");
      if ((p[0] & 0x60) == 0x40) fstrcat(flags,"M ");
      if ((p[0] & 0x60) == 0x60) fstrcat(flags,"H ");
      if (p[0] & 0x10) fstrcat(flags,"<DEREGISTERING> ");
      if (p[0] & 0x08) fstrcat(flags,"<CONFLICT> ");
      if (p[0] & 0x04) fstrcat(flags,"<ACTIVE> ");
      if (p[0] & 0x02) fstrcat(flags,"<PERMANENT> ");

      if (master && !*master && type == 0x1d) {
	StrnCpy(master,qname,15);
	trim_string(master,NULL," ");
      }

      if (rname && !*rname && type == 0x20 && !(p[0]&0x80)) {
	StrnCpy(rname,qname,15);
	trim_string(rname,NULL," ");
      }
      
      for (i = strlen( qname) ; --i >= 0 ; ) {
	if (!isprint((int)qname[i])) qname[i] = '.';
      }
      DEBUG(1,("\t%-15s <%02x> - %s\n",qname,type,flags));
      p+=2;
    }
  DEBUG(1,("num_good_sends=%d num_good_receives=%d\n",
	       IVAL(p,20),IVAL(p,24)));
}