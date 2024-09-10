/*
 * Gauss-Sidel smoother for vector:
 *
 * As GS: 
 *   1. exchange off proc data
 *   2. smooth local dof
 *
 * Assumption:
 *   1. unknow dof is vector of dim 3
 *   2. Matrix block for vector is 
 *      | a1  -b   0 |
 *      |  b  a2   0 |
 *      |  0   0  a3 |
 * 
 *  */
void 
mg_GaussSidel_vec(MAT *A, VEC *x, VEC *b, int nsmooth, void *ctx)
{
    INT i, j, k, l, n, *pc, *pc0, *pc_offp, nlocal;
    FLOAT *pd, *pd0, *pd_offp, *vx, *vb;
    size_t *ps; 
    FLOAT sum[Dim], omega = _p->smooth_damp;
#if USE_MPI
    FLOAT *offp_data = NULL;
#endif	/* USE_MPI */

    MagicCheck(VEC, x);
    MagicCheck(VEC, b);
    assert(x == NULL || x->nvec == 1);
    assert(b == NULL || b->nvec == 1);
    if (x != NULL && !x->assembled)
	phgVecAssemble(x);
    if (b != NULL && !b->assembled)
	phgVecAssemble(b);
    
    assert(A->type != PHG_DESTROYED);
    if (!A->assembled)
	phgMatAssemble(A);
    assert(A->type != PHG_MATRIX_FREE);
    phgMatPack(A);

#if USE_MPI
    if (A->cmap->nprocs > 1) {
	offp_data = phgAlloc(A->cinfo->rsize * sizeof(*offp_data));
    }
#endif	/* USE_MPI */

    if (A->cmap->nlocal != A->rmap->nlocal ||
	A->cmap->nlocal != x->map->nlocal  ||
	A->cmap->nlocal != b->map->nlocal)
	phgError(1, "%s:%d: inconsistent matrix-vector.", __FILE__,
		 __LINE__);

    if (A->cmap->nlocal % Dim != 0)
	phgError(1, "%s: assume vector dof of dim 3!\n", __FUNCTION__);

#if USE_MPI
    if (A->cmap->nprocs > 1) {
	phgMapScatterBegin(A->cinfo, x->nvec, x->data, offp_data);
	phgMapScatterEnd(A->cinfo, x->nvec, x->data, offp_data);
    }
#endif	/* USE_MPI */

    /* iteration */
    for (l = 0; l < nsmooth; l++) {
	INT i_start, i_add;

	/* multiply with local data */
	vx = x->data;
	vb = b->data;
	pc0 = A->packed_cols;
	pd0 = A->packed_data;
	ps = A->packed_ind;
	nlocal = A->rmap->nlocal;

	/*
	 * lexicographic order: low to high
	 * Note: low->high and high->low alternatively does not help.
	 * */
	if (TRUE || l % 2 == 0) {
	    i_start = 0;
	    i_add = Dim;
	} else {
	    i_start = nlocal - Dim;
	    i_add = -Dim;
	}

	//for (i = i_start; i < A->rmap->nlocal && i >= 0;  i += i_add) {
	for (i = 0; i < nlocal ;  i += Dim) {
	    INT jcol;
	    FLOAT aa[Dim][Dim], det, dx[Dim];

	    memset(aa, 0, sizeof(aa));
	    sum[0] = vb[i  ];
	    sum[1] = vb[i+1];
	    sum[2] = vb[i+2];

	    /* local data */
	    pc = pc0 + PACK_COL(ps, i);
	    pd = pd0 + PACK_DAT(ps, i);
	    for (k = 0; k < Dim; k++) {
		if ((n = *(pc++)) != 0) {
		    for (j = 0; j < n; j++) {
			jcol = *(pc++);
			if (jcol < i || jcol > i+2) {
			    sum[k] -= *(pd++) * vx[jcol];
			} else { /* offD, jcol = i,i+1,i+2 */
			    aa[k][jcol - i] = *(pd++);
			}
		    }
		}
	    }

	    /* remote data */
	    if (A->cmap->nprocs > 1) {
		pc_offp = pc0 + PACK_COL_OFFP(ps, i, nlocal);
		pd_offp = pd0 + PACK_DAT_OFFP(ps, i, nlocal);
		for (k = 0; k < Dim; k++) {
		    if ((n = *(pc_offp++)) != 0) {
			for (j = 0; j < n; j++) {
			    jcol = *(pc_offp++);
			    sum[k] -= *(pd_offp++) * offp_data[jcol];
			}
		    }
		}
	    }

	    /* solve */
	    det = (aa[0][0] * aa[1][1] - aa[0][1] * aa[1][0]);
	    assert(Fabs(det) > 1e-12);
	    det = 1. / det;
	    dx[0] = (aa[1][1] * sum[0] - aa[0][1] * sum[1]) * det - vx[i  ];
	    dx[1] = (aa[0][0] * sum[1] - aa[1][0] * sum[1]) * det - vx[i+1];
	    dx[2] = (1./aa[2][2] * sum[2]) - vx[i+2];
	    vx[i  ] += omega * dx[0];
	    vx[i+1] += omega * dx[1];
	    vx[i+2] += omega * dx[2];
	}

#if USE_MPI
	if (A->cmap->nprocs > 1) {
	    phgMapScatterBegin(A->cinfo, x->nvec, x->data, offp_data);
	    phgMapScatterEnd(A->cinfo, x->nvec, x->data, offp_data);
	}
#endif	/* USE_MPI */
    }


#if USE_MPI
    phgFree(offp_data);
#endif	/* USE_MPI */

    return;
}