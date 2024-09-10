static void write_joined_vtk(const char *out_name){
  FILE *fp_out;
  int nxt, nyt, nzt; /* Total number of grid cells in each dir. */
  int nxp, nyp, nzp;
  int i, j, k;
  double ox, oy, oz, dx, dy, dz;
  char type[128], variable[128], format[128];
  char t_type[128], t_variable[128], t_format[128]; /* Temporary versions */
  int retval;

  /* Count the total number of grid cells in each direction */
  nxt = nyt = nzt = 0;
  for(i=0; i<NGrid_x; i++)
    nxt += domain_3d[0][0][i].Nx;

  for(j=0; j<NGrid_y; j++)
    nyt += domain_3d[0][j][0].Ny;

  for(k=0; k<NGrid_z; k++)
    nzt += domain_3d[k][0][0].Nz;

  /* Initialize ox, oy, oz */
  ox = domain_3d[0][0][0].ox;
  oy = domain_3d[0][0][0].oy;
  oz = domain_3d[0][0][0].oz;

  /* Initialize dx, dy, dz */
  dx = domain_3d[0][0][0].dx;
  dy = domain_3d[0][0][0].dy;
  dz = domain_3d[0][0][0].dz;

  /* Count the number of grid cell corners */
  if(nxt >= 1 && dx > 0.0) nxp = nxt+1;
  else nxp = nxt; /* dx = 0.0 */

  if(nyt >= 1 && dy > 0.0) nyp = nyt+1;
  else nyp = nyt; /* dy = 0.0 */

  if(nzt >= 1 && dz > 0.0) nzp = nzt+1;
  else nzp = nzt; /* dz = 0.0 */

  /* Open the output file */
  if((fp_out = fopen(out_name,"w")) == NULL)
    join_error("Error opening the output file \"%s\"\n",out_name);

  /* Write out some header information */
  fprintf(fp_out,"# vtk DataFile Version 3.0\n");
  /* Save the comment field from the [0][0][0] vtk domain file */
  /* fprintf(fp_out,"Joined VTK files\n"); */
  fprintf(fp_out,"%s\n",domain_3d[0][0][0].comment);
  fprintf(fp_out,"BINARY\n");
  fprintf(fp_out,"DATASET STRUCTURED_POINTS\n");
  fprintf(fp_out,"DIMENSIONS %d %d %d\n", nxp, nyp, nzp);
  fprintf(fp_out,"ORIGIN %e %e %e\n", ox, oy, oz);
  fprintf(fp_out,"SPACING %e %e %e\n", dx, dy, dz);
  fprintf(fp_out,"CELL_DATA %d\n",nxt*nyt*nzt);

  while(1){
    for(k=0; k<NGrid_z; k++){
      for(j=0; j<NGrid_y; j++){
	for(i=0; i<NGrid_x; i++){
	  if(i == 0 && j == 0 && k == 0){
	    retval = fscanf(domain_3d[k][j][i].fp,"%s %s %s\n",
			    type, variable, format);

	    if(retval == EOF){ /* Assuming no errors, we are done... */
	      fclose(fp_out);
	      return;
	    }

	    if(strcmp(format, "float") != 0){
	      fclose(fp_out);
	      join_error("Expected \"float\" format, found \"%s\"\n",format);
	    }
	  }
	  else{
	    retval = fscanf(domain_3d[k][j][i].fp,"%s %s %s\n",
			    t_type, t_variable, t_format);

	    if(retval == EOF){ /* This shouldn't occur... */
	      fclose(fp_out);
	      fprintf(stderr,"[join_vtk_dump]: EOF returned for file \"%s\"\n",
		      domain_3d[k][j][i].fname);
	      return;
	    }

	    if(strcmp(type, t_type) != 0 ||
	       strcmp(variable, t_variable) != 0 ||
	       strcmp(format, t_format) != 0 ){
	      fclose(fp_out);
	      join_error("mismatch in input file positions\n");
	    }
	  }

	  if(strcmp(type, "SCALARS") == 0){
	    /* Read in the LOOKUP_TABLE (only default supported for now) */
	    fscanf(domain_3d[k][j][i].fp,"%s %s\n", t_type, t_format);
	    if(strcmp(t_type, "LOOKUP_TABLE") != 0 ||
	       strcmp(t_format, "default") != 0 ){
	      fclose(fp_out);
	      fprintf(stderr,"Expected \"LOOKUP_TABLE default\"\n");
	      join_error("Found \"%s %s\"\n",t_type,t_format);
	    }
	  }

	  /* Prevent leading data bytes that correspond to "white space"
	     from being consumed by the fscanf's above -- MNL 2/6/06 */
          assert(fseek(domain_3d[k][j][i].fp, -1, SEEK_CUR) == 0);
	  while (isspace(fgetc(domain_3d[k][j][i].fp)))
            assert(fseek(domain_3d[k][j][i].fp, -2, SEEK_CUR) == 0);
	  assert(fgetc(domain_3d[k][j][i].fp) == '\n');
	}
      }
    }

    printf("Reading: \"%s %s %s\"\n",type,variable,format);

    /* Now, every file should agree that we either have SCALARS or
       VECTORS data */
    fprintf(fp_out,"%s %s %s\n",type,variable,format);
    if(strcmp(type, "SCALARS") == 0){
      fprintf(fp_out,"LOOKUP_TABLE default\n");
      read_write_scalar(fp_out);
    }
    else if(strcmp(type, "VECTORS") == 0){
      read_write_vector(fp_out);
    }
    else
      join_error("Input type = \"%s\"\n",type);
  }

  return;
}