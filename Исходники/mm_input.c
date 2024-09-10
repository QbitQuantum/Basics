int
readMMHeader(
	     SCOTCH_Num * vertnbr,
	     SCOTCH_Num * edgenbr,
FILE * const stream)
{
  int c;
  SCOTCH_Num vertnum0, vertnum1;
  int symmetric = 0;
  char firstline[1024];
  int pos = 0;

  memSet(firstline, '\0', 1024);
  fgets(firstline, 16, stream);

  if (strcmp(firstline, "%%MatrixMarket "))
    return (-1);

  while (((c = fgetc(stream)) != '\n') && (c != EOF)) {
    firstline[pos++] = toupper(c);
    if (pos == 1024)
      return (-1);
  }
  firstline[pos] = '\0';

  if (strstr(firstline, "SYMMETRIC"))
    symmetric = 1;

  while ((c = fgetc(stream)) == '%') {
    if (skipLine(stream) != 0)
      return (-1);                                /* End of file reached */
  }
  ungetc (c, stream);

  if (intLoad (stream, &vertnum0) != 1) {         /* Read row number */
    return (-1);
  }
  if (intLoad (stream, &vertnum1) != 1) {         /* Read col number */
    return (-1);
  }
  if (vertnum0 != vertnum1) {                     /* Non square matrix */
      return (-1);
  }
  *vertnbr = vertnum1;
  if (intLoad (stream, edgenbr) != 1) { /* Read edge number */
    return (-1);
  }
  *edgenbr -= *vertnbr;           /* No loop in graph */
  return (symmetric);
}