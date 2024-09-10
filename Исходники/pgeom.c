void setup_domain (struct geom *g) {
  /* - double pass setup; PORE regios determine global 
       inter-layer spacing dz 
  */
  
  int i;
  double l_pore=0;  /* total length of pore region, center-center */
  int    q_pore;   /* number of gaps between layers */
  int    q_check, nborders, lastborder;
  double dz, dA;
  double z1, z2;
  enum domaintypes lastdtype;
  struct domain *dom;

  dA = 0.0;                /* distance between two atoms ('bond length') */
  q_check = 0;             /* internal topology check */
  nborders = 0;            /* number of interfaces between different domains */
  lastdtype = g->domain[0]->type;

  /* first pass:
     total length of pore region and global dz
     also check correct topology: MOUTH -> PORE -> MOUTH
  */
  for (i = 0; i < g->ndomains; i++) {
    dom = g->domain[i];

    if (dom->type != lastdtype) {
      nborders++;           /* increase nborders for each change M<->P */
      lastborder = i - 1;   /* last PORE region before second MOUTH */
    };
    lastdtype   = dom->type;

    if ( dom->type == PORE) {
      l_pore += dom->l;
      dA      = max(dA, 2 * dom->species->radius);
      mesg (SUB2, "setup_domain(): l_pore = %6.3f  2*rA = %4.2f", l_pore, dA);
    };
  };

  /* if nborders != 2 => error!! */
  if ( nborders != 2 ) {
    fatal_error (2,
    "setup_domain (): Fatal error. Topology of model is incorrect. It should\n"
    "                 have been MOUTH->PORE->MOUTH with 2 borders, but there\n"
    "                 were %d borders in %d domains", nborders, g->ndomains);
  };

  q_pore = (int) l_pore/dA;  
  if ( q_pore < 1 ) {
    fatal_error (2,
		 "setup_domain (): Fatal error. Number of layers in the PORE is not positive\n"
		 "                 (q_pore = %d). (l_pore=%4.2f) < (2*rA=%4.2f)\n",
		 q_pore, l_pore, dA);
  };

  dz = l_pore/q_pore;
  /* second pass:
     number of layers q per domain and z coordinates of lower and upper layer
  */
  z2 = -dz;

  for (i = 0; i < g->ndomains; i++) {
    dom = g->domain[i];
    if ( dom->type == PORE) 
      {
	dom->q   = round (dom->l / dz);
	q_check += dom->q;
	dom->dz  = dz;           /* rather pointless to store dz separately 
				  but I still used the old strucs */
      } 
    else 
      {
	dom->q   = round (dom->l / dA);
	dom->dz  = dz;           /* pointless ... */
      };

    if (dom->q < 0) {
      fatal_error (2,
		   "setup_domain (): Fatal error. Number of layers in domain %d "
		   "is not positive\n"
		   "                 (q = %d). Probably (l=%4.2f) < (2*rA=%4.2f)\n",
		   i,dom->q, dom->l, dA);
    };

    z1 = z2 + dz;
    z2 = z1 + (dom->q - 1) * dz;

    dom->z1 = z1;
    dom->z2 = z2;

  };  

  assert (q_check == q_pore);
  return;
};