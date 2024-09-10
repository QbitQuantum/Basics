/* compute intersection of two convex polyhedrons */
TRI* cvi (double *va, int nva, double *pa, int npa, double *vb, int nvb, double *pb, int npb, CVIKIND kind, int *m, double **pv, int *nv)
{
  double e [6], p [3], q [3], eps, d, *nl, *pt, *nn, *yy;
  PFV *pfv, *v, *w, *z;
  int i, j, k, n;
  TRI *tri, *t;

  /* initialize */
  eps = GEOMETRIC_EPSILON;
  tri = t = NULL;
  pfv = NULL;
  yy = NULL;

  /* compute closest points */
  d = gjk (va, nva, vb, nvb, p, q);
  if (d > GEOMETRIC_EPSILON) { *m = 0; return NULL; }

  /* push 'p' deeper inside only if regularized intersection is sought */
  if (kind == REGULARIZED && !refine_point (pa, npa, pb, npb, p, &eps)) { *m = 0; return NULL; }

  /* vertices extents for a later sanity check */
  vertices_extents (va, nva, vb, nvb, eps, e);

  /* translate base points of planes so that
   * p = q = 0; compute new normals 'yy' */
  ERRMEM (yy = malloc (sizeof (double [3]) * (npa+npb)));
  for (i = 0, nl = pa, pt = pa + 3, nn = yy;
       i < npa; i ++, nl += 6, pt += 6, nn += 3)
  {
    SUB (pt, p, q); /* q => translated point of current plane */
    d = - DOT (nl, q); /* d => zero offset */
    if (d > -GEOMETRIC_EPSILON) d = -eps; /* regularisation (tiny swelling) */
    DIV (nl, -d, nn);  /* <nn, x> <= 1 (yy stores vertices of polar polygon) */
  }
  for (i = 0, nl = pb, pt = pb + 3; i < npb;
       i ++, nl += 6, pt += 6, nn += 3)
  {
    SUB (pt, p, q);
    d = - DOT (nl, q);
    if (d > -GEOMETRIC_EPSILON) d = -eps; /* regularisation (tiny swelling) */
    DIV (nl, -d, nn);
  }

  /* compute and polarise convex
   * hull of new normals 'yy' */
  if (!(tri = hull (yy, npa+npb, &i))) goto error; /* tri = cv (polar (a) U polar (b)) */
  if (!(pfv = TRI_Polarise (tri, i, &j))) goto error; /* pfv = polar (tri) => pfv = a * b */

  /* normals in 'pfv' point to 'yy'; triangulate
   * polar faces and set 'a' or 'b' flags */

  /* count all face vertices */
  for (k = n = 0; k < j; k ++)
  {
    v = &pfv [k]; n ++;
    for (w = v->n; w != v; w = w->n) n ++;
  }
  /* there is (number of face vertices - 2) triangles per face,
   * hence there is n - j * 2 triangles in total; vertex
   * memory in 'pfv' is placed after n PFV items */
#if GEOMDEBUG
  ASSERT_DEBUG (n - j*2 > 3, "Inconsitent polar faces => too few vertices in some faces");
#else
  if (n - j*2 <= 3) goto error;
#endif
  ERRMEM (tri = realloc (tri, sizeof (TRI) * (n-j*2) + sizeof (double [3]) * i)); /* allocate space for triangles and vertices */
  pt = (double*) (tri + (n - j*2)); /* this is where output vertices begin */
  nn = (double*) (pfv + n); /* this is where coords begin in 'pfv' block */
  memcpy (pt, nn, sizeof (double [3]) * i); /* copy vertex data */
  if (pv) *pv = pt;
  if (nv) *nv = i;

  /* shift point coords to the old 'zero' */
  for (k = 0, nl = pt; k < i; k ++, nl += 3)
  { 
    ADD (nl, p, nl); /* 'nl' used as a point */

    if (nl[0] < e [0] || nl[1] < e [1] || nl[2] < e [2] ||
	nl[0] > e [3] || nl[1] > e [4] || nl[2] > e [5])
    {
#if GEOMDEBUG
      printf ("CVI HAS GONE INSANE FOR THE INPUT:\n"), dump_input (va, nva, pa, npa, vb, nvb, pb, npb);
#endif
      goto error;
    }
  }

  for (k = 0, t = tri; k < j; k ++)
  {
    v = &pfv [k]; /* fixed vertex 'v' */
    for (w = v->n, z = w->n; z != v; w = w->n, z = z->n, t ++) /* remaining vertices 'w' & 'z' */
    {
      COPY (v->nl, t->out); /* copy normal */
      NORMALIZE (t->out);
      t->ver [0] = pt + (v->coord - nn); /* map vertices */
      t->ver [1] = pt + (w->coord - nn);
      t->ver [2] = pt + (z->coord - nn);
      t->flg = ((v->nl - yy) / 3) + 1; /* first 'npa' entries in 'yy' come from 'a' => positive 1-based index in 'a' */
      if (t->flg > npa) t->flg = -(t->flg - npa); /* last 'npb' ones come from 'b' => negative 1-based index in 'b' */
    }
  }

  goto done;

error:
  if (tri) free (tri);
  tri = t = NULL;

done:
  free (yy);
  free (pfv);

  (*m) = (t - tri);
  return tri;
}