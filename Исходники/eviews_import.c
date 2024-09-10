int wf1_get_data (const char *fname, DATASET *dset,
		  gretlopt opt, PRN *prn)
{
    FILE *fp;
    DATASET *newset = NULL;
    unsigned offset;
    int nvread, ftype;
    int err = 0;

    fp = gretl_fopen(fname, "rb");
    if (fp == NULL) {
	return E_FOPEN;
    }

    ftype = wf1_check_file_type(fp);
    
    if (ftype < 0) {
	fclose(fp);
	pputs(prn, "This file does not seem to be an EViews workfile\n");
	return E_DATA;
    }

    if (ftype == 1) {
	pputs(prn, "EViews 7+ file: expect problems!\n");
    }

    newset = datainfo_new();
    if (newset == NULL) {
	pputs(prn, _("Out of memory\n"));
	fclose(fp);
	return E_ALLOC;
    }

    err = parse_wf1_header(fp, ftype, newset, &offset);
    if (err) {
	pputs(prn, _("Error reading workfile header\n"));
	free_datainfo(newset);
	fclose(fp);
	return err;
    }

    err = start_new_Z(newset, 0);
    if (err) {
	pputs(prn, _("Out of memory\n"));
	free_datainfo(newset);
	fclose(fp);
	return E_ALLOC;
    }	

    err = read_wf1_variables(fp, ftype, offset, newset, &nvread, prn);

    if (err) {
	destroy_dataset(newset);
    } else {
	int merge = (dset->Z != NULL);
	int nvtarg = newset->v - 1;

	if (nvread < nvtarg) {
	    dataset_drop_last_variables(newset, nvtarg - nvread);
	}

	if (fix_varname_duplicates(newset)) {
	    pputs(prn, _("warning: some variable names were duplicated\n"));
	}

	err = merge_or_replace_data(dset, &newset, opt, prn);

	if (!err && !merge) {
	    dataset_add_import_info(dset, fname, GRETL_WF1);
	}
    }

    fclose(fp);

    return err;
}  