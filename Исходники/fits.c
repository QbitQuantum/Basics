str FITSloadTable(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	mvc *m = NULL;
	sql_schema *sch;
	sql_table *fits_fl, *fits_tbl, *tbl = NULL;
	sql_column *col;
	sql_subtype tpe;
	fitsfile *fptr;
	str tname = *getArgReference_str(stk, pci, 1);
	str fname;
	str msg = MAL_SUCCEED;
	oid rid = oid_nil, frid = oid_nil;
	int status = 0, cnum = 0, *fid, *hdu, hdutype, j, anynull = 0, mtype;
	int *tpcode = NULL;
	long *rep = NULL, *wid = NULL, rows; /* type long used by fits library */
	char keywrd[80], **cname, nm[FLEN_VALUE];
	ptr nilptr;

	if ((msg = getSQLContext(cntxt, mb, &m, NULL)) != MAL_SUCCEED)
		return msg;
	if ((msg = checkSQLContext(cntxt)) != MAL_SUCCEED)
		return msg;
	sch = mvc_bind_schema(m, "sys");

	fits_tbl = mvc_bind_table(m, sch, "fits_tables");
	if (fits_tbl == NULL) {
		msg = createException(MAL, "fits.loadtable", "FITS catalog is missing.\n");
		return msg;
	}

	tbl = mvc_bind_table(m, sch, tname);
	if (tbl) {
		msg = createException(MAL, "fits.loadtable", "Table %s is already created.\n", tname);
		return msg;
	}

	col = mvc_bind_column(m, fits_tbl, "name");
	rid = table_funcs.column_find_row(m->session->tr, col, tname, NULL);
	if (rid == oid_nil) {
		msg = createException(MAL, "fits.loadtable", "Table %s is unknown in FITS catalog. Attach first the containing file\n", tname);
		return msg;
	}

	/* Open FITS file and move to the table HDU */
	col = mvc_bind_column(m, fits_tbl, "file_id");
	fid = (int*)table_funcs.column_find_value(m->session->tr, col, rid);

	fits_fl = mvc_bind_table(m, sch, "fits_files");
	col = mvc_bind_column(m, fits_fl, "id");
	frid = table_funcs.column_find_row(m->session->tr, col, (void *)fid, NULL);
	GDKfree(fid);
	col = mvc_bind_column(m, fits_fl, "name");
	fname = (char *)table_funcs.column_find_value(m->session->tr, col, frid);
	if (fits_open_file(&fptr, fname, READONLY, &status)) {
		msg = createException(MAL, "fits.loadtable", "Missing FITS file %s.\n", fname);
		GDKfree(fname);
		return msg;
	}
	GDKfree(fname);

	col = mvc_bind_column(m, fits_tbl, "hdu");
	hdu = (int*)table_funcs.column_find_value(m->session->tr, col, rid);
	fits_movabs_hdu(fptr, *hdu, &hdutype, &status);
	if (hdutype != ASCII_TBL && hdutype != BINARY_TBL) {
		msg = createException(MAL, "fits.loadtable", "HDU %d is not a table.\n", *hdu);
		GDKfree(hdu);
		fits_close_file(fptr, &status);
		return msg;
	}
	GDKfree(hdu);

	/* create a SQL table to hold the FITS table */
	/*	col = mvc_bind_column(m, fits_tbl, "columns");
	   cnum = *(int*) table_funcs.column_find_value(m->session->tr, col, rid); */
	fits_get_num_cols(fptr, &cnum, &status);
	tbl = mvc_create_table(m, sch, tname, tt_table, 0, SQL_PERSIST, 0, cnum);

	tpcode = (int *)GDKzalloc(sizeof(int) * cnum);
	rep = (long *)GDKzalloc(sizeof(long) * cnum);
	wid = (long *)GDKzalloc(sizeof(long) * cnum);
	cname = (char **)GDKzalloc(sizeof(char *) * cnum);

	for (j = 1; j <= cnum; j++) {
		/*		fits_get_acolparms(fptr, j, cname, &tbcol, tunit, tform, &tscal, &tzero, tnull, tdisp, &status); */
		snprintf(keywrd, 80, "TTYPE%d", j);
		fits_read_key(fptr, TSTRING, keywrd, nm, NULL, &status);
		if (status) {
			snprintf(nm, FLEN_VALUE, "column_%d", j);
			status = 0;
		}
		cname[j - 1] = toLower(nm);
		fits_get_coltype(fptr, j, &tpcode[j - 1], &rep[j - 1], &wid[j - 1], &status);
		fits2subtype(&tpe, tpcode[j - 1], rep[j - 1], wid[j - 1]);

		/*		fprintf(stderr,"#%d %ld %ld - M: %s\n", tpcode[j-1], rep[j-1], wid[j-1], tpe.type->sqlname); */

		mvc_create_column(m, tbl, cname[j - 1], &tpe);
	}

	/* data load */
	fits_get_num_rows(fptr, &rows, &status);
	fprintf(stderr,"#Loading %ld rows in table %s\n", rows, tname);
	for (j = 1; j <= cnum; j++) {
		BAT *tmp = NULL;
		int time0 = GDKms();
		mtype = fits2mtype(tpcode[j - 1]);
		nilptr = ATOMnilptr(mtype);
		col = mvc_bind_column(m, tbl, cname[j - 1]);

		tmp = BATnew(TYPE_void, mtype, rows, TRANSIENT);
		if ( tmp == NULL){
			GDKfree(tpcode);
			GDKfree(rep);
			GDKfree(wid);
			GDKfree(cname);
			throw(MAL,"fits.load", MAL_MALLOC_FAIL);
		}
		BATseqbase(tmp, 0);
		if (mtype != TYPE_str) {
			fits_read_col(fptr, tpcode[j - 1], j, 1, 1, rows, nilptr, (void *)BUNtloc(bat_iterator(tmp), BUNfirst(tmp)), &anynull, &status);
			BATsetcount(tmp, rows);
			tmp->tsorted = 0;
			tmp->trevsorted = 0;
		} else {
/*			char *v = GDKzalloc(wid[j-1]);*/
			/* type long demanded by "rows", i.e., by fits library */
			long bsize = 50, batch = bsize, k, i;
			int tm0, tloadtm = 0, tattachtm = 0;
			char **v = (char **) GDKzalloc(sizeof(char *) * bsize);
			for(i = 0; i < bsize; i++)
				v[i] = GDKzalloc(wid[j-1]);
			for(i = 0; i < rows; i += batch) {
				batch = rows - i < bsize ? rows - i: bsize;
				tm0 = GDKms();
				fits_read_col(fptr, tpcode[j - 1], j, 1 + i, 1, batch, nilptr, (void *)v, &anynull, &status);
				tloadtm += GDKms() - tm0;
				tm0 = GDKms();
				for(k = 0; k < batch ; k++)
					BUNappend(tmp, v[k], TRUE);
				tattachtm += GDKms() - tm0;
			}
			for(i = 0; i < bsize ; i++)
				GDKfree(v[i]);
			GDKfree(v);
			fprintf(stderr,"#String column load %d ms, BUNappend %d ms\n", tloadtm, tattachtm);
		}

		if (status) {
			char buf[FLEN_ERRMSG + 1];
			fits_read_errmsg(buf);
			msg = createException(MAL, "fits.loadtable", "Cannot load column %s of %s table: %s.\n", cname[j - 1], tname, buf);
			break;
		}
		fprintf(stderr,"#Column %s loaded for %d ms\t", cname[j-1], GDKms() - time0);
		store_funcs.append_col(m->session->tr, col, tmp, TYPE_bat);
		fprintf(stderr,"#Total %d ms\n", GDKms() - time0);
		BBPunfix(tmp->batCacheid);
	}

	GDKfree(tpcode);
	GDKfree(rep);
	GDKfree(wid);
	GDKfree(cname);

	fits_close_file(fptr, &status);
	return msg;
}