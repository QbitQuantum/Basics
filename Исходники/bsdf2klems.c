/* Load and resample XML BSDF description using Klems basis */
static void
eval_bsdf(const char *fname)
{
	ANGLE_BASIS	*abp = get_basis(kbasis);
	SDData		bsd;
	SDError		ec;
	FVECT		vin, vout;
	SDValue		sv;
	double		sum;
	int		i, j, n;

	SDclearBSDF(&bsd, fname);		/* load BSDF file */
	if ((ec = SDloadFile(&bsd, fname)) != SDEnone)
		goto err;
	xml_prologue(&bsd);			/* pass geometry */
						/* front reflection */
	if (bsd.rf != NULL || bsd.rLambFront.cieY > .002) {
	    input_orient = 1; output_orient = 1;
	    data_prologue();
	    for (j = 0; j < abp->nangles; j++) {
	        for (i = 0; i < abp->nangles; i++) {
		    sum = 0;			/* average over patches */
		    for (n = npsamps; n-- > 0; ) {
			fo_getvec(vout, j+(n+frandom())/npsamps, abp);
			fi_getvec(vin, i+urand(n), abp);
			ec = SDevalBSDF(&sv, vout, vin, &bsd);
			if (ec != SDEnone)
				goto err;
			sum += sv.cieY;
		    }
		    printf("\t%.3e\n", sum/npsamps);
		}
		putchar('\n');			/* extra space between rows */
	    }
	    data_epilogue();
	}
						/* back reflection */
	if (bsd.rb != NULL || bsd.rLambBack.cieY > .002) {
	    input_orient = -1; output_orient = -1;
	    data_prologue();
	    for (j = 0; j < abp->nangles; j++) {
	        for (i = 0; i < abp->nangles; i++) {
		    sum = 0;			/* average over patches */
		    for (n = npsamps; n-- > 0; ) {
			bo_getvec(vout, j+(n+frandom())/npsamps, abp);
			bi_getvec(vin, i+urand(n), abp);
			ec = SDevalBSDF(&sv, vout, vin, &bsd);
			if (ec != SDEnone)
				goto err;
			sum += sv.cieY;
		    }
		    printf("\t%.3e\n", sum/npsamps);
		}
		putchar('\n');			/* extra space between rows */
	    }
	    data_epilogue();
	}
						/* front transmission */
	if (bsd.tf != NULL || bsd.tLamb.cieY > .002) {
	    input_orient = 1; output_orient = -1;
	    data_prologue();
	    for (j = 0; j < abp->nangles; j++) {
	        for (i = 0; i < abp->nangles; i++) {
		    sum = 0;			/* average over patches */
		    for (n = npsamps; n-- > 0; ) {
			bo_getvec(vout, j+(n+frandom())/npsamps, abp);
			fi_getvec(vin, i+urand(n), abp);
			ec = SDevalBSDF(&sv, vout, vin, &bsd);
			if (ec != SDEnone)
				goto err;
			sum += sv.cieY;
		    }
		    printf("\t%.3e\n", sum/npsamps);
		}
		putchar('\n');			/* extra space between rows */
	    }
	    data_epilogue();
	}
						/* back transmission */
	if ((bsd.tb != NULL) | (bsd.tf != NULL)) {
	    input_orient = -1; output_orient = 1;
	    data_prologue();
	    for (j = 0; j < abp->nangles; j++) {
	        for (i = 0; i < abp->nangles; i++) {
		    sum = 0;		/* average over patches */
		    for (n = npsamps; n-- > 0; ) {
			fo_getvec(vout, j+(n+frandom())/npsamps, abp);
			bi_getvec(vin, i+urand(n), abp);
			ec = SDevalBSDF(&sv, vout, vin, &bsd);
			if (ec != SDEnone)
				goto err;
			sum += sv.cieY;
		    }
		    printf("\t%.3e\n", sum/npsamps);
		}
		putchar('\n');			/* extra space between rows */
	    }
	    data_epilogue();
	}
	SDfreeBSDF(&bsd);			/* all done */
	return;
err:
	SDreportError(ec, stderr);
	exit(1);
}