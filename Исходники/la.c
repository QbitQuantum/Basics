double G_vector_norm_maxval(vec_struct * vc, int vflag)
{
    doublereal xval, *startpt, *curpt;
    double cellval;
    int ncells, incr;

    if (!vc->is_init)
	G_fatal_error(_("Matrix is not initialised"));

    if (vc->type == ROWVEC_) {
	ncells = (integer) vc->cols;
	incr = (integer) vc->ldim;
	if (vc->v_indx < 0)
	    startpt = vc->vals;
	else
	    startpt = vc->vals + vc->v_indx;
    }
    else {
	ncells = (integer) vc->rows;
	incr = 1;
	if (vc->v_indx < 0)
	    startpt = vc->vals;
	else
	    startpt = vc->vals + vc->v_indx * vc->ldim;
    }

    xval = *startpt;
    curpt = startpt;

    while (ncells > 0) {
	if (curpt != startpt) {
	    switch (vflag) {

	    case MAX_POS:
		{
		    if (*curpt > xval)
			xval = *curpt;
		    break;
		}

	    case MAX_NEG:
		{
		    if (*curpt < xval)
			xval = *curpt;
		    break;
		}

	    case MAX_ABS:
		{
		    cellval = (double)(*curpt);
		    if (hypot(cellval, cellval) > (double)xval)
			xval = *curpt;
		}
	    }			/* switch */
	}			/* if(curpt != startpt) */

	curpt += incr;
	ncells--;
    }

    return (double)xval;
}