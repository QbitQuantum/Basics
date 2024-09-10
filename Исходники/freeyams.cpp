void mesh3_to_yams_pSurfMesh (const Mesh3 &Th3, int memory, int choix,
                              yams_pSurfMesh meshyams) {
	/*
	 * Mesh3  :: maillage initiale
	 * memory :: memoire pour yams
	 * choix  :: option du remaillage
	 * ref    ::
	 */
	int k;
	int npinit, neinit;

	meshyams->dim = 3;
	meshyams->npfixe = Th3.nv;
	meshyams->nefixe = Th3.nbe;
	meshyams->ntet = Th3.nt;
	meshyams->nafixe = 0;	// Edges
	meshyams->nvfixe = 0;	// Normals
	meshyams->ntfixe = 0;	// Tangents
	npinit = meshyams->npfixe;
	neinit = meshyams->nefixe;
	// cette fonction change la taille des tableaux en fonctions des options : choix, memory, sm->type
	zaldy1(meshyams->nefixe, meshyams->npfixe, meshyams->nvfixe, memory, meshyams, choix);

	yams_pPoint ppt;

	for (k = 1; k <= npinit; k++) {
		ppt = &meshyams->point[k];
		ppt->c[0] = Th3.vertices[k - 1].x;
		ppt->c[1] = Th3.vertices[k - 1].y;
		ppt->c[2] = Th3.vertices[k - 1].z;
		ppt->ref = Th3.vertices[k - 1].lab & 0x7fff;

		ppt->tag = M_UNUSED;
		ppt->color = 0;
		ppt->size = -1.;
		ppt->tge = 0;
		ppt->geom = M_CURVE;
	}

	meshyams->npfixe = npinit;

	/* read mesh triangles */
	yams_pTriangle ptriangle;

	for (k = 1; k <= neinit; k++) {
		const Triangle3 &K(Th3.be(k - 1));
		ptriangle = &meshyams->tria[k];
		ptriangle->v[0] = Th3.operator () (K[0]) + 1;
		ptriangle->v[1] = Th3.operator () (K[1]) + 1;
		ptriangle->v[2] = Th3.operator () (K[2]) + 1;
		ptriangle->ref = K.lab & 0x7fff;
	}

	/* tetrahedra */
	if (meshyams->ntet) {
		yams_pTetra ptetra;
		meshyams->tetra = (yams_Tetra *)calloc((meshyams->ntet + 1), sizeof(yams_Tetra));
		assert(meshyams->tetra);

		for (k = 1; k <= meshyams->ntet; k++) {
			const Tet &K(Th3.elements[k - 1]);
			ptetra = &meshyams->tetra[k];
			ptetra->v[0] = Th3.operator () (K[0]) + 1;
			ptetra->v[1] = Th3.operator () (K[1]) + 1;
			ptetra->v[2] = Th3.operator () (K[2]) + 1;
			ptetra->v[3] = Th3.operator () (K[3]) + 1;
			ptetra->ref = K.lab & 0x7fff;
		}
	}

	meshyams->ne = meshyams->nefixe;
	meshyams->np = meshyams->npfixe;
}