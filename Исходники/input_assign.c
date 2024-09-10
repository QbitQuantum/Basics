static int input_assign_normal(FILE *finassign, char *inassignname, int nvtxs, int *assignment)
/*
  FILE     *finassign;		input assignment file
  char     *inassignname;		name of input assignment file
  int       nvtxs;		number of vertices to output
  int    *assignment;		values to be printed 
*/

{
  extern FILE *Output_File;   /* output file or null */
  extern int CHECK_INPUT;	/* print warning messages? */
  extern int DEBUG_TRACE;	/* trace main execution path */
  int       flag;		/* logical conditional */
  int       end_flag;		/* return flag from read_int() */
  int       i, j;		/* loop counter */
  int       read_int();

  if (DEBUG_TRACE > 0) {
    printf("<Entering input_assign>\n");
  }

  /* Get the assignment vector one line at a time, checking as you go. */
  /* First read past any comments at top. */
  end_flag = 1;
  while (end_flag == 1) {
    assignment[0] = read_int(finassign, &end_flag);
  }

  if (assignment[0] < 0) {
    printf("ERROR: Entry %d in assignment file `%s' less than zero (%d)\n",
	   1, inassignname, assignment[0]);
    return (1);
  }

  if (end_flag == -1) {
    printf("ERROR: No values found in assignment file `%s'\n", inassignname);
    return (1);
  }

  flag = 0;
  if (assignment[0] > nvtxs)
    flag = assignment[1];
  for (i = 1; i < nvtxs; i++) {
    j = fscanf(finassign, "%d", &(assignment[i]));
    if (j != 1) {
      printf("ERROR: Too few values in assignment file `%s'.\n", inassignname);
      return (1);
    }
    if (assignment[i] < 0) {
      printf("ERROR: Entry %d in assignment file `%s' less than zero (%d)\n",
	     i+1, inassignname, assignment[i]);
      return (1);
    }
    if (assignment[i] > nvtxs) {	/* warn since probably an error */
      if (assignment[i] > flag)
	flag = assignment[i];
    }
  }

  if (flag && CHECK_INPUT) {
    printf("WARNING: Possible error in assignment file `%s'\n", inassignname);
    printf("         More assignment sets (%d) than vertices (%d)\n", flag, nvtxs);
    if (Output_File != NULL) {
      fprintf(Output_File,
	      "WARNING: Possible error in assignment file `%s'\n", inassignname);
      fprintf(Output_File,
	      "         More assignment sets (%d) than vertices (%d)\n", flag, nvtxs);
    }
  }

  /* Check for spurious extra stuff in file. */
  flag = FALSE;
  end_flag = 0;
  while (!flag && end_flag != -1) {
    read_int(finassign, &end_flag);
    if (!end_flag)
      flag = TRUE;
  }
  if (flag && CHECK_INPUT) {
    printf("WARNING: Possible error in assignment file `%s'\n", inassignname);
    printf("         Numerical data found after expected end of file\n");
    if (Output_File != NULL) { 
      fprintf(Output_File,
	      "WARNING: Possible error in assignment file `%s'\n", inassignname);
      fprintf(Output_File,
	      "         Numerical data found after expected end of file\n");
    }
  }
  return (0);
}