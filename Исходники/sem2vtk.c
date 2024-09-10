static void read_data (FILE *fp)
/* ------------------------------------------------------------------------- *
 * Read in data files.  If NZ > 1, it is assumed that data are in the file
 * in plane-by-plane order.  For each plane, the ordering of data varies
 * depending on whether the file is in ASCII or binary format: for ASCII, the
 * fields are in column order, element-by-element (row-major), whereas for
 * binary formats the fields are written in the file sequentially.
 *
 * Automatic conversion between little- and big-endian binary formats.
 * ------------------------------------------------------------------------- */
{
  int  i, m, n, nplane;
  int  nr_chk, ns_chk, nz_chk, nel_chk;
  char buf[STR_MAX], *c;
  
  /* -- Read the header down to the field list, check size of input. */

  for (n = 0; n < 3; n++) fgets(buf, STR_MAX, fp);

  if (sscanf (buf, "%d%d%d%d", &nr_chk, &ns_chk, &nz_chk, &nel_chk) != 4) {
    fputs ("error while reading mesh\n", stderr);
    exit  (EXIT_FAILURE);
  }

  if (nr != nr_chk || ns != ns_chk || nel != nel_chk) {
    fputs ("2D structure of mesh and field file do not agree\n", stderr);
    exit (EXIT_FAILURE);
  }

  for (n = 3; n < 9; n++) fgets(buf, STR_MAX, fp);

  /* -- Read the list of fields. */

  n       = 0;
  c       = buf;
  nfields = 0;
  while (n++ < 25 && nfields < MAXFIELDS) 
    if (isalnum(*c++)) type[nfields++] = *(c-1);

  if (nfields > MAXFIELDS) {
    fprintf(stderr, "sem2tec: a maximum of %d fields may be converted.\n", 
	    MAXFIELDS);
    exit(EXIT_FAILURE);
  }

  /* -- Allocate memory. */

  nplane = nr * ns * nel;
  for (n = 0; n < nfields; n++)
    data[n] = (double*) malloc (nzp * nplane * sizeof (double));

  /* -- Check the format. */

  c = fgets(buf, STR_MAX, fp); 
  while (isspace(*c)) c++;

  switch (tolower(*c)) {                     /* ASCII or binary read? */

  case 'a':
    for (m = 0; m < nz; m++)
      for (i = 0; i < nplane; i++)
	for (n = 0; n < nfields; n++)
	  if (fscanf(fp, "%lf", data[n] + m * nplane + i) < 0) {
	    fputs("sem2tec: field file (ASCII) read error\n", stderr);
	    exit (EXIT_FAILURE);
	  }
    break;

  case 'b': {
    int swab, machine  = iformat();

    swab = (strstr (buf, "little") && machine == 0 ||
	    strstr (buf, "big"   ) && machine == 1  ) ? 1 : 0;

    for (n = 0; n < nfields; n++) {
      if (fread (data[n], sizeof(double), nz * nplane, fp) != nz * nplane) {
 fputs("sem2tec: field file (binary) read error\n", stderr);
	  exit (EXIT_FAILURE);
      }
      if (swab) dbrev (nz * nplane, data[n], 1, data[n], 1);
    }
    break;
  }

  default:
    fprintf (stderr, "sem2tec: unknown format flag: '%c'\n", *c);
    exit    (EXIT_FAILURE);
    break;
  }
}