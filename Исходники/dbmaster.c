static	void
_CheckDBG(
	char		*name,
	DBG_Struct	*dbg,
	char		*red_name)
{
	DBG_Struct	*red_dbg;
	char *src_port, *dsc_port;
	char *dbg_dbname = "", *red_dbg_dbname = "";
	char	*dbname;
ENTER_FUNC;		
	if		(  dbg->redirect  !=  NULL  ) {
		red_dbg = dbg->redirect;
		if ( strcmp(red_dbg->name, red_name ) == 0 ){
			src_port = StrDup(StringPort(GetDB_Port(dbg,DB_UPDATE)));
			dsc_port = StrDup(StringPort(GetDB_Port(red_dbg,DB_UPDATE)));
			if		(  ( dbname = GetDB_DBname(dbg,DB_UPDATE) )  !=  NULL  ) {
				dbg_dbname = dbname;
			}
			if		(  ( dbname = GetDB_DBname(red_dbg,DB_UPDATE) )  !=  NULL  ) {
				red_dbg_dbname = dbname;
			}
			if ( ( strcmp(dbg->type, red_dbg->type ) == 0 )
				 && ( strcmp(dbg_dbname, red_dbg_dbname ) == 0 )
				 && ( strcmp(src_port, dsc_port) == 0 ) ) {
				Error("The connection destination is same DB");
			}
			xfree(src_port);
			xfree(dsc_port);
		}
	}
LEAVE_FUNC;
}