int odbc_createrowset(ClipMachine* cm,SQLROWSET* rs,ClipVar* ap,ClipVar* idname,const char* gen_idSQL){
	ODBC_ROWSET* rowset = (ODBC_ROWSET*)rs;
	ODBC_STMT* stmt = rowset->stmt;
	SQLRETURN er;
	SQLSMALLINT cols;
	SQLINTEGER nullable;
	int i;

	odbc_bindpars(stmt,ap);
	if((er = SQLAllocStmt(stmt->conn->conn,&stmt->hstmt))) goto err;
	if((er = SQLPrepare(stmt->hstmt,stmt->sql,strlen(stmt->sql)))) goto err;
	rowset->rowset_item =
		_clip_store_c_item(cm,rowset,_C_ITEM_TYPE_SQL,destroy_odbc_rowset);

	if((er = SQLExecute(stmt->hstmt))) goto err;

	if((er = SQLNumResultCols(stmt->hstmt,&cols))) goto err;
	rowset->nfields = cols;
	rowset->fields = calloc(rowset->nfields,sizeof(SQLFIELD));
	rowset->id = -1;

	for(i=0;i<rowset->nfields;i++){
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_NAME,rowset->fields[i].name,MAXFIELDNAME+1,0,0)))
			goto err;
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_TYPE,0,0,0,(SQLPOINTER)&rowset->fields[i].type)))
			goto err;
		rowset->fields[i].ctype[0] = _odbc_ctype(rowset->fields[i].type);
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_LENGTH,0,0,0,(SQLPOINTER)&rowset->fields[i].buflen)))
			goto err;
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_DISPLAY_SIZE,0,0,0,(SQLPOINTER)&rowset->fields[i].len)))
			goto err;
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_SCALE,0,0,0,(SQLPOINTER)&rowset->fields[i].dec)))
			goto err;
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_UNSIGNED,0,0,0,(SQLPOINTER)&rowset->fields[i].unsign)))
			goto err;
		if((er = SQLColAttributes(stmt->hstmt,i+1,
			SQL_COLUMN_NULLABLE,0,0,0,(SQLPOINTER)&nullable)))
			goto err;
		rowset->fields[i].notnull = (nullable == SQL_NO_NULLS);
		/* silly PostgreSQL's ODBC driver */
		if(stmt->conn->postgres && (rowset->fields[i].type == SQL_NUMERIC ||
			rowset->fields[i].type == SQL_DECIMAL)){

			rowset->fields[i].dec = LOWORD(rowset->fields[i].len);
			rowset->fields[i].len = HIWORD(rowset->fields[i].len);
			rowset->fields[i].buflen = 8;
		}
		if(rowset->fields[i].type == SQL_LONGVARBINARY)
			rowset->fields[i].buflen *= 2;

		if(idname->t.type == CHARACTER_t){
			if(idname->s.str.buf && !strcasecmp(rowset->fields[i].name,idname->s.str.buf)){
				rowset->id = i;
				rowset->nids = 1;
			}
		} else if(idname->t.type == ARRAY_t){
			int j;
			for(j=0;j<idname->a.count;j++){
				ClipVar* vp = idname->a.items+j;
				if(vp->t.type == CHARACTER_t && vp->s.str.buf
					&& !strcasecmp(rowset->fields[i].name,vp->s.str.buf)){

					rowset->nids++;
					rowset->ids = realloc(rowset->ids,rowset->nids*sizeof(int));
					rowset->ids[rowset->nids-1] = i;
				}
			}
		}

		if(rowset->fields[i].type == SQL_BINARY ||
			rowset->fields[i].type == SQL_VARBINARY ||
			rowset->fields[i].type == SQL_LONGVARBINARY)
		rowset->fields[i].binary = 1;
	}
	rowset->lastrec = 0;
	rowset->data = malloc(sizeof(void*)*rowset->lastrec);
	rowset->unknownrows = 1;
	return 0;
err:
	odbc_error(cm,stmt->conn->loc,0,stmt->conn->conn,stmt->hstmt,__LINE__,er_createrowset);
	return 1;
}