/*!
  \brief VFKReaderSQLite constructor
*/
VFKReaderSQLite::VFKReaderSQLite(const char *pszFilename) : VFKReader(pszFilename)
{
    const char *pszDbNameConf;
    CPLString   pszDbName;
    CPLString   osCommand;
    VSIStatBufL sStatBuf;
    bool        bNewDb;
    
    /* open tmp SQLite DB (re-use DB file if already exists) */
    pszDbNameConf = CPLGetConfigOption("OGR_VFK_DB_NAME", NULL);
    if (pszDbNameConf) {
	pszDbName = pszDbNameConf;
    }
    else {
	pszDbName.Printf("%s.db", m_pszFilename);
    }
    
    if (CSLTestBoolean(CPLGetConfigOption("OGR_VFK_DB_SPATIAL", "YES")))
	m_bSpatial = TRUE;    /* build geometry from DB */
    else
	m_bSpatial = FALSE;   /* store also geometry in DB */
    
    bNewDb = TRUE;
    if (VSIStatL(pszDbName, &sStatBuf ) == 0) {
	if (CSLTestBoolean(CPLGetConfigOption("OGR_VFK_DB_OVERWRITE", "NO"))) {
	    bNewDb = TRUE;     /* overwrite existing DB */
	    VSIUnlink(pszDbName);
	}
	else {
	    bNewDb = FALSE;    /* re-use exising DB */
	}
    }
    else {
      	CPLError(CE_Warning, CPLE_AppDefined, 
                 "SQLite DB not found. Reading VFK data may take some time...");
    }
    CPLDebug("OGR-VFK", "New DB: %s Spatial: %s",
	     bNewDb ? "yes" : "no", m_bSpatial ? "yes" : "no");

    if (SQLITE_OK != sqlite3_open(pszDbName, &m_poDB)) {
        CPLError(CE_Failure, CPLE_AppDefined, 
                 "Creating SQLite DB failed");
    }
    else {
        char* pszErrMsg = NULL;
        sqlite3_exec(m_poDB, "PRAGMA synchronous = OFF", NULL, NULL, &pszErrMsg);
        sqlite3_free(pszErrMsg);
    }
    
    if (bNewDb) {
        /* new DB, create support metadata tables */
        osCommand = "CREATE TABLE 'vfk_blocks' "
	  "(file_name text, table_name text, num_records integer, "
	    "num_geometries integer, table_defn text)";
        ExecuteSQL(osCommand.c_str());
    }
}