static Att_List *do_import_sites(struct opusftp_globals *og,char *path)
{
FuncArgs * fa;
struct site_entry *e;
int anon, acct;
BPTR cf;
char *buf;
Att_List *list=NULL;

if	(!(buf=AllocVec(TMPBUFLEN,MEMF_CLEAR)))
	{
	DisplayBeep(NULL);
	return(NULL);
	}

if	((list = Att_NewList(LISTF_POOL)))
	{
	if	((cf = Open(path, MODE_OLDFILE )))
		{
		while	( FGets( cf, buf, TMPBUFLEN ))
			{
			if	(*buf=='#' || *buf=='\n')
				continue;

			/* skip config entries */

			if	((fa = ParseArgs( CONFIG_TEMPLATE, buf )))
				{
				DisposeArgs( fa );
				continue;
				}

			/* handle addressbook stuff*/
			if	((fa = ParseArgs( ADDR_TEMPLATE, buf )))
				{

				anon = fa->FA_Arguments[A_OPT_ANON];
				acct = fa->FA_Arguments[A_OPT_ACCT];


				// skip any lines starting with '---'

				if	(fa->FA_Arguments[A_OPT_HOST] &&
					strncmp((char*)fa->FA_Arguments[A_OPT_HOST],"---",3)==0)
					{
					DisposeArgs( fa );
					continue;
					}

				if	(((anon == 0) != (acct == 0))	/* Can't be both or neither */
					&& (anon || fa->FA_Arguments[A_OPT_USER])	/* User Account must have user name */
					&& (fa->FA_Arguments[A_OPT_HOST] || fa->FA_Arguments[A_OPT_ADDR])/* Must have Hostname or Address */
					)
					{
					if	((e = AllocVec( sizeof(struct site_entry), MEMF_CLEAR )))
						{
						e->se_anon = anon;


						if	(!anon)
							{
							if	(fa->FA_Arguments[A_OPT_USER])
								stccpy( e->se_user, (char*)fa->FA_Arguments[A_OPT_USER], USERNAMELEN );

							if	(fa->FA_Arguments[A_OPT_PASS])
								stccpy( e->se_pass, (char*)fa->FA_Arguments[A_OPT_PASS], PASSWORDLEN );
							}

						/* Use Hostname or Address for the socket */
						if	(fa->FA_Arguments[A_OPT_HOST])
							stccpy( e->se_host, (char*)fa->FA_Arguments[A_OPT_HOST], HOSTNAMELEN );
						else
							stccpy( e->se_host, (char*)fa->FA_Arguments[A_OPT_ADDR], HOSTNAMELEN );

						// special port specified ?

						if	(fa->FA_Arguments[A_OPT_PORT])
							e->se_port=*(int*)fa->FA_Arguments[A_OPT_PORT];

						if	(e->se_port<=0 || e->se_port >9999)
							e->se_port=21;


						/* Use Alias, Hostname, or Address in requester */
						if	(fa->FA_Arguments[A_OPT_ALIS])
							stccpy( e->se_name, (char*)fa->FA_Arguments[A_OPT_ALIS], HOSTNAMELEN );
						else if	(fa->FA_Arguments[A_OPT_HOST])
							stccpy( e->se_name, (char*)fa->FA_Arguments[A_OPT_HOST], HOSTNAMELEN );
						else if	(fa->FA_Arguments[A_OPT_ADDR])
							stccpy( e->se_name, (char*)fa->FA_Arguments[A_OPT_ADDR], HOSTNAMELEN );

						if	(fa->FA_Arguments[A_OPT_PATH])
							stccpy( e->se_path, (char*)fa->FA_Arguments[A_OPT_PATH], PATHLEN );

						// set env to point to global default

						e->se_env=&og->og_oc.oc_env;
						e->se_has_custom_env=FALSE;



						Att_NewNode(list, e->se_name ,(ULONG)e ,ADDNODE_SORT);
						}
					}
				DisposeArgs( fa );
				}
			}
		Close(cf);
		}
	}

FreeVec(buf);

return(list);
}