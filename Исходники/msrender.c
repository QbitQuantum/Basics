void slice_elbow (struct msscene *ms, struct surface *current_surface, double fine_pixel, struct face *fac)
{
	char message[MAXLINE];
	struct leaf *lf;
	struct circle *lfcir, *torcir;
	struct arc *torarc;
	struct vertex *torvtx[2];
	int i, j, k, nfocus, atmnum;
	double anginc, bigrad;
	double atmcen[3], ccens[2][3], cradii[2];
	double focus[3], vect[3], z_axis[3], base[3];
	struct variety *vty;
	double *foci;
    struct cept *ex;
	
	vty = fac -> vty;
	atmnum = vty -> atmnum[0];
	if (debug >= 2) {
		sprintf (message,"render elbow face for atom %5d", atmnum);
		inform(message);
	}
	for (k = 0; k < 3; k++)
		atmcen[k] = *(current_surface -> atom_centers + 3 * (atmnum - 1) + k);
	for (j = 0; j < 2; j++)
		cradii[j] = vty -> radii[1];
	for (j = 0; j < 2; j++)
		for (k = 0; k < 3; k++) {
			ccens[j][k] = vty -> ccens[j][k];
		}
	bigrad = distance (atmcen, ccens[0]) + cradii[0];
	for (k = 0; k < 3; k++) {
		if (atmcen[k] + bigrad < ms -> window[0][k]) return;
		if (atmcen[k] - bigrad > ms -> window[1][k]) return;
	}
	/* leaf circle */
	lfcir = allocate_circle ();
	if (lfcir == NULL) {
		ex = new_cept (MEMORY_ERROR,  ALLOCATION,  FATAL_SEVERITY);
		add_object (ex, CIRCLE, "leaf circle");
		add_function (ex, "slice_elbow");
		add_source (ex, "msrender.c");
		return;
	}
	/* leaf */
	lf = allocate_leaf ();
	if (lf == NULL) {
		add_object (tail_cept, LEAF, "leaf");
		add_function (tail_cept, "slice_sphere");
		return;
	}
	/* torus circle radius, center, axis */
	torcir = new_circle (vty -> center, vty -> radii[0], vty -> axis);
	if (torcir == NULL) {
		add_object (tail_cept, CIRCLE, "torus circle");
		add_function (tail_cept, "slice_elbow");
		return;
	}
	/* torus arc */
	torarc = allocate_arc ();
	if (torarc == NULL) {
		add_object (tail_cept, ARC, "torus arc");
		add_function (tail_cept, "slice_elbow");
		add_source (tail_cept, "msrender.c");
		return;
	}
	for (j = 0; j < 2; j++) {
		torvtx[j] = allocate_vertex ();
		if (error()) {
			add_object (tail_cept, VERTEX, "torus vertex");
			add_function (tail_cept, "slice_elbow");
			add_source (tail_cept, "msrender.c");
			return;
		}
	}
	/* set up leaf fields */
	for (k = 0; k < MAXPA; k++)
		lf -> atmnum[k] = vty -> atmnum[k];
	lf -> cir = lfcir;
	lf -> shape = CONVEX;		/* to avoid reversing normal vector */
	lf -> type = vty -> type;
	lf -> fac = fac;
	lf -> cep = 0;
	lf -> clip_ep = 0;
	lf -> side = OUTSIDE;
	lf -> comp = fac -> comp;
	lf -> input_hue = fac -> input_hue;
	for (j = 0; j < 2; j++)
		lf -> where[j] = ACCESSIBLE;

	/* setup torus central circle for subdivision */
	anginc = fine_pixel / ((vty -> radii[0] + cradii[0]));
	torcir -> radius = vty -> radii[0];
	for (k = 0; k < 3; k++) {
		torcir -> center[k] = vty -> center[k];
		torcir -> axis[k] = vty -> axis[k];
	}
	torarc -> cir = torcir;
	for (j = 0; j < 2; j++) {
		torarc -> vtx[j] = torvtx[j];
		for (k = 0; k < 3; k++)
			torvtx[j] -> center[k] = ccens[j][k];
	}
	foci = (double *) NULL;
	nfocus = render_sub_arc (torarc, &foci, anginc);
	if (nfocus < 2) {
		ex = new_cept (LOGIC_ERROR, MSUNDERFLOW, FATAL_SEVERITY);
        add_function (ex, "slice_elbow");
        add_source (ex, "msrender.c");
        add_long (ex, "number of foci", (long) nfocus);
		return;
	}

	/* create leaves */
	for (i = 0; i < nfocus; i++) {
		for (k = 0; k < 3; k++) {
			focus[k] = (*(foci + 3 * i + k));
			lfcir -> center[k] = focus[k];
			lf -> focus[k] = focus[k];
		}
		lfcir -> radius = cradii[0];
		/* compute tangent to torus central circle */
		for (k = 0; k < 3; k++)
			vect[k] = focus[k] - vty -> center[k];
		cross (vty -> axis, vect, lfcir -> axis);
		normalize (lfcir -> axis);
		for (k = 0; k < 3; k++)
			z_axis[k] = ((k == 2) ? 1.0 : 0.0);
		cross (lfcir -> axis, z_axis, base);
		if (norm (base) <= 0.0) {
			continue;
		}
		normalize (base);
		for (k = 0; k < 3; k++) {
			lf -> ends[0][k] = lfcir -> center[k] - lfcir -> radius * base[k];
			lf -> ends[1][k] = lfcir -> center[k] + lfcir -> radius * base[k];
		}
		/* clip and render leaf */
		clip_leaf (ms, current_surface, fine_pixel, lf);
		if (error()) return;
	}
	free_doubles (foci, 0, VERTS);
	free_leaf (lf);
	free_arc (torarc);
	free_circle (torcir);
	free_circle (lfcir);
	for (j = 0; j < 2; j++)
		free_vertex (torvtx[j]);
}