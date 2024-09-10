void extract_init(struct SigSet *S)
{
    int m;
    int i;
    int b1, b2;
    int nbands;
    double *lambda;
    struct ClassSig *C;
    struct SubSig *SubS;

    nbands = S->nbands;
    /* allocate scratch memory */
    lambda = (double *)G_malloc(nbands * sizeof(double));

    /* invert matrix and compute constant for each subclass */

    /* for each class */
    for (m = 0; m < S->nclasses; m++) {
	C = &(S->ClassSig[m]);

	/* for each subclass */
	for (i = 0; i < C->nsubclasses; i++) {
	    SubS = &(C->SubSig[i]);

	    /* Test for symetric  matrix */
	    for (b1 = 0; b1 < nbands; b1++)
		for (b2 = 0; b2 < nbands; b2++) {
		    if (SubS->R[b1][b2] != SubS->R[b2][b1])
			G_warning(_("Nonsymetric covariance for class %d subclass %d"),
				  m + 1, i + 1);

		    SubS->Rinv[b1][b2] = SubS->R[b1][b2];
		}

	    /* Test for positive definite matrix */
	    eigen(SubS->Rinv, NULL, lambda, nbands);
	    for (b1 = 0; b1 < nbands; b1++) {
		if (lambda[b1] <= 0.0)
		    G_warning(_("Nonpositive eigenvalues for class %d subclass %d"),
			      m + 1, i + 1);
	    }

	    /* Precomputes the cnst */
	    SubS->cnst = (-nbands / 2.0) * log(2 * PI);
	    for (b1 = 0; b1 < nbands; b1++) {
		SubS->cnst += -0.5 * log(lambda[b1]);
	    }

	    /* Precomputes the inverse of tex->R */
	    invert(SubS->Rinv, nbands);
	}
    }
    G_free((char *)lambda);
}