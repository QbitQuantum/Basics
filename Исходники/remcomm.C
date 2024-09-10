/*------------------------------------------------------*/
void		ListToPc (char *s)
			{
			int		i;
			lib		*l;
			command *c;

#ifndef		WIN32
void		heap_start(void);
static		long	*p;
			char	cc[32];
#endif

			uchar	r[LINK_LEN],rr[16];

			switch(*s) {
				case 'l':	l=Ln;
							do	{
								l->check=null;
								l=l->next;
								}	while(l != Ln);
							c=CP;
                            if(c)
								do	{
									c->chk=null;
									c=c->next;
									}	while(c != CP);
							SetTask(CheckScreen,0,RTC_task);
							SetTask(CheckLib,0,RTC_task);
							break;

				case 's':   CheckScr=null;
							if(!CheckTask(CheckScreen,RTC_task))
								CheckScreen();
							else
								SetTask(CheckScreen,0,RTC_task);
							break;
	
				case 'o':	sprintf(r,"=o %s,%d\r\n>",LinkAddrText(LinkAddr(OBP),rr),targets_xn(OBP));
							puts_pc(r);
							break;

				case 'p':	puts_pc("=p ");
								putsLLA(OBP);
                                puts_pc("\r\n");
							break;

				case 'm':   for(i=0; _MenuCode[i]; ++i)
							{
								sprintf(r,"=m[%d] ",i);
								for(s=_MenuCode[i]; *s; ++s)
									if(*s == ' ')
										sprintf(strchr(r,0)," ");
									else
									{
/*										if(*s < ENTER)
											sprintf(strchr(r,0),"%c",*s);
										else
*/											sprintf(strchr(r,0),"%02X",*s);
									}
									sprintf(strchr(r,0),"\r\n");
								puts_pc(r);
							}
							break;

				case 't':   for(i=0; _TextCode[i]; ++i)
							{
								sprintf(r,"=t[%d] ",i);
								for(s=_TextCode[i]; *s; ++s)
									sprintf(strchr(r,0),"%02X",*s);
								sprintf(strchr(r,0),"\r\n");
								puts_pc(r);
							}
							break;

				case 'h':   for(i=0; _MenuHead[i]; ++i)
							{
								sprintf(r,"=h[%d] ",i);
								for(s=_MenuHead[i]; *s; ++s)
									sprintf(strchr(r,0),"%02X",*s);
								sprintf(strchr(r,0),"\r\n");
								puts_pc(r);
							}
							break;
#ifndef	WIN32
				case 'H':	for(p=(long *)heap_start; *p; p=(long *)labs(*p))
							{
								if(*p>0)
									sprintf(cc,"=H %08lX,%08lX,!\r\n",p,*p);
								else
									sprintf(cc,"=H %08lX,%08lX,-\r\n",p,-(*p));
								puts_pc(cc);
							}
							break;
#endif
				case 'f':	ListPar();
							break;

				case 'z':	ListZone(NULL);
							break;

				case 'v':   puts_pc(">=v");
							SysMessage(CHPC);
							break;

				case 'G':	WriteGunData(Guns,NULL);
							break;

				case 'D':	ListDatum();
							break;

				case 'e':	shaft_enable();
							break;

				default:	ReadLib(s);
							break;
				}
			}