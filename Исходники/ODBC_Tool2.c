// --------------------------------------------------------------------------------
// ODBCTableList
// Crea una lista delle tabelle di un dbase
// --------------------------------------------------------------------------------
SINT ODBCTableList(CHAR *lpLibrary,CHAR *lpName,CHAR *lpType)
{
	ARMaker(WS_OPEN,NULL);
	if (!EhOdbc.hStmt) goto FINE;
    // Carica il driver 
	//win_open(EHWP_SCREENCENTER,50,232,59,-1,3,ON,"Lettura delle Tabelle");
	mouse_graph(0,0,"CLEX");

	ODBCCloseCursor();
	if (lpLibrary) 
	{
		if (!*lpLibrary) lpLibrary=NULL;
	}
	// Chiedo l'elenco delle tabelle
//	EhOdbc.sqlLastError=SQLTables(EhOdbc.hStmt, lpLibrary, SQL_NTS, NULL, 0, "%", SQL_NTS, NULL, 0);
	EhOdbc.sqlLastError=SQLTables(EhOdbc.hStmt, 
								  NULL, 0, // Catalogo
								  //"",SQL_NTS,
								  lpLibrary, lpLibrary?SQL_NTS:0, //Schema
								  lpName, (lpName?SQL_NTS:0), // Nome della tabella
								  lpType, lpType?SQL_NTS:0); // Tipo della tabella

	if (EhOdbc.sqlLastError!=SQL_SUCCESS) 
	{if (!EhOdbc.fNoErrorView) ODBCError("ODBCTableList()::SQLTables()"); 
	 goto FINE;
	}

	ODBCDoDictionary(); // Creo il dizionario del risultato
	while (!ODBCNext())
	{  
		//dispx("[%s] %s     <        ",ODBCFldPtr("TABLE_TYPE"),ODBCFldPtr("TABLE_NAME")); mouse_input();
		if (!strcmp(ODBCFldPtr("TABLE_TYPE"),lpType))
			//!strcmp(ODBCFldPtr("TABLE_TYPE"),"SYSTEM TABLE"))
			{	
				ARMaker(WS_ADD,ODBCFldPtr("TABLE_NAME"));
			}
	} 

	ODBCCloseCursor();
FINE:
	//win_close();
	MouseCursorDefault();
	return ARMaker(WS_CLOSE,"ODBCSource");
}