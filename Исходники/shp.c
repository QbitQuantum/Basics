/* attach a single shp file given its name, fill in shp catalog tables */
str
SHPattach(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	mvc *m = NULL;
	sql_schema *sch = NULL;
	sql_table *fls = NULL, *shps = NULL, *shps_dbf = NULL;
	sql_column *col;
	str msg = MAL_SUCCEED;
	str fname = *(str*)getArgReference(stk, pci, 1);
	/* SHP-level descriptor */
	char buf[BUFSIZ], temp_buf[BUFSIZ], *s=buf;
	int  i=0, shpid = 0;
	oid fid, rid = oid_nil;
	GDALWConnection shp_conn;
	GDALWConnection * shp_conn_ptr = NULL;
	GDALWSimpleFieldDef * field_definitions;
	GDALWSpatialInfo spatial_info;

	char *nameToLowerCase = NULL;

	if((msg = getSQLContext(cntxt, mb, &m, NULL)) != MAL_SUCCEED)
		return msg;
	if((msg = checkSQLContext(cntxt)) != MAL_SUCCEED)
		return msg;

	if(!(sch = mvc_bind_schema(m, "sys")))
		return createException(MAL, "shp.attach", SQLSTATE(38000) "Schema sys missing\n");

	fls = mvc_bind_table(m, sch, "files");
	shps = mvc_bind_table(m, sch, "shapefiles");
	shps_dbf = mvc_bind_table(m, sch, "shapefiles_dbf");
	if (fls == NULL || shps == NULL || shps_dbf == NULL )
		return createException(MAL, "shp.attach", SQLSTATE(38000) "Catalog table missing\n");

	if ((shp_conn_ptr = GDALWConnect((char *) fname)) == NULL) {
		return createException(MAL, "shp.attach", SQLSTATE(38000) "Missing shape file %s\n", fname);
	}
	shp_conn = *shp_conn_ptr;

	/* check if the file is already attached */
	col = mvc_bind_column(m, fls, "path");
	rid = table_funcs.column_find_row(m->session->tr, col, fname, NULL);
	if (!is_oid_nil(rid)) {
		GDALWClose(shp_conn_ptr);
		return createException(MAL, "shp.attach", SQLSTATE(38000) "File %s already attached\n", fname);
	}

	/* add row in the files(id, path) catalog table */
	col = mvc_bind_column(m, fls, "id");
	fid = store_funcs.count_col(m->session->tr, col, 1) + 1;
	snprintf(buf, BUFSIZ, INSFILE, (int)fid, fname);
	if ( ( msg = SQLstatementIntern(cntxt, &s,"shp.attach",TRUE,FALSE,NULL)) != MAL_SUCCEED)
		goto finish;


	/*if (shp_conn.layer == NULL || shp_conn.source == NULL || shp_conn.handler == NULL || shp_conn.driver == NULL) {
		msg = createException(MAL, "shp.attach", SQLSTATE(38000) "lol-1\n");
									return msg;
	}*/

	/* add row in the shapefiles catalog table (e.g. the name of the table that will store tha data of the shapefile) */
	spatial_info = GDALWGetSpatialInfo(shp_conn);
	col = mvc_bind_column(m, shps, "shapefileid");
	shpid = store_funcs.count_col(m->session->tr, col, 1) + 1;
	nameToLowerCase = toLower(shp_conn.layername);
	snprintf(buf, BUFSIZ, INSSHP, shpid, (int)fid, spatial_info.epsg, nameToLowerCase);
	GDKfree(nameToLowerCase);
	if ( ( msg = SQLstatementIntern(cntxt, &s,"shp.attach",TRUE,FALSE,NULL)) != MAL_SUCCEED)
			goto finish;

	/* add information about the fields of the shape file 
 	* one row for each field with info (shapefile_id, field_name, field_type) */
	field_definitions = GDALWGetSimpleFieldDefinitions(shp_conn);
	if (field_definitions == NULL) {
		GDALWClose(&shp_conn);
		return createException(MAL, "shp.attach", SQLSTATE(HY001) MAL_MALLOC_FAIL);
	}
	for (i=0 ; i<shp_conn.numFieldDefinitions ; i++) {
		snprintf(buf, BUFSIZ, INSSHPDBF, shpid, field_definitions[i].fieldName, field_definitions[i].fieldType);
		if ( ( msg = SQLstatementIntern(cntxt, &s,"shp.attach",TRUE,FALSE,NULL)) != MAL_SUCCEED)
			goto fin;
	}

	/* create the table that will store the data of the shape file */
	temp_buf[0]='\0';
	for (i=0 ; i<shp_conn.numFieldDefinitions ; i++) {
		nameToLowerCase = toLower(field_definitions[i].fieldName);
		if (strcmp(field_definitions[i].fieldType, "Integer") == 0) {
			sprintf(temp_buf + strlen(temp_buf), "\"%s\" INT, ", nameToLowerCase);
		} else if (strcmp(field_definitions[i].fieldType, "Real") == 0) {
			sprintf(temp_buf + strlen(temp_buf), "\"%s\" FLOAT, ", nameToLowerCase);
#if 0
		} else if (strcmp(field_definitions[i].fieldType, "Date") == 0) {
			sprintf(temp_buf + strlen(temp_buf), "\"%s\" STRING, ", nameToLowerCase);
#endif
        	} else 
			sprintf(temp_buf + strlen(temp_buf), "\"%s\" STRING, ", nameToLowerCase);
		GDKfree(nameToLowerCase);
	}

	sprintf(temp_buf + strlen(temp_buf), "geom GEOMETRY ");
	snprintf(buf, BUFSIZ, CRTTBL, shp_conn.layername, temp_buf);

	if ( ( msg = SQLstatementIntern(cntxt, &s,"shp.import",TRUE,FALSE,NULL)) != MAL_SUCCEED)
		goto fin;

fin:
	free(field_definitions);
finish:
	/* if (msg != MAL_SUCCEED){
	   snprintf(buf, BUFSIZ,"ROLLBACK;");
	   SQLstatementIntern(cntxt,&s,"geotiff.attach",TRUE,FALSE));
	   }*/
	GDALWClose(&shp_conn);
	return msg;
}