ptri2d
read_tri2d(const char *name)
{

  FILE     *in;
  ptri2d    t2;
  real(*x)[2];
  uint(*e)[2];
  uint(*t)[3];
  uint     *xb;
  uint     *eb;
  uint      i;

  uint      vertices, edges, triangles;
  uint      items;
  char      buf[80], *res;

  in = fopen(name, "r");
  if (!in) {
    (void) fprintf(stderr, "Could not open file \"%s\" for reading\n", name);
    return 0;
  }

  res = fgets(buf, BUFSIZE, in);
  assert(res != NULL);
  while (!feof(in) && buf[0] == '#') {
    res = fgets(buf, 80, in);
    assert(res != NULL);
  }
  items = sscanf(buf, "%u %u %u", &vertices, &edges, &triangles);
  if (items != 3) {
    (void) fprintf(stderr, "Could not get sizes from file \"%s\"\n", name);
    (void) fclose(in);
    return 0;
  }

  t2 = new_tri2d(vertices, edges, triangles);
  x = t2->x;
  e = t2->e;
  t = t2->t;
  xb = t2->xb;
  eb = t2->eb;

  /*vertices */
  for (i = 0; i < vertices; i++) {
    res = fgets(buf, 80, in);
    assert(res != NULL);
    while (!feof(in) && buf[0] == '#') {
      res = fgets(buf, 80, in);
      assert(res != NULL);
    }
    items = sscanf(buf, "%" SCANF_PREFIX "f %" SCANF_PREFIX "f %u", x[i],
		   x[i] + 1, xb + i);
    if (items != 3) {
      (void) fprintf(stderr, "Could not read vertex %u from file \"%s\"\n", i,
		     name);
      del_tri2d(t2);
      (void) fclose(in);
      return 0;
    }
  }
  /*edges */
  for (i = 0; i < edges; i++) {
    res = fgets(buf, 80, in);
    assert(res != NULL);
    while (!feof(in) && buf[0] == '#') {
      res = fgets(buf, 80, in);
      assert(res != NULL);
    }
    items = sscanf(buf, "%u %u %u", e[i], e[i] + 1, eb + i);
    if (items != 3) {
      (void) fprintf(stderr, "Could not read edge %u from file \"%s\"\n", i,
		     name);
      del_tri2d(t2);
      (void) fclose(in);
      return 0;
    }
  }
  /*triangles */
  for (i = 0; i < triangles; i++) {
    res = fgets(buf, 80, in);
    assert(res != NULL);
    while (!feof(in) && buf[0] == '#') {
      res = fgets(buf, 80, in);
      assert(res != NULL);
    }
    items = sscanf(buf, "%u %u %u", t[i], t[i] + 1, t[i] + 2);
    if (items != 3) {
      (void) fprintf(stderr, "Could not read triangle %u from file \"%s\"\n",
		     i, name);
      del_tri2d(t2);
      (void) fclose(in);
      return 0;
    }
  }

  (void) fclose(in);

  return t2;
}