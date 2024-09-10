void from_ncgm(FILE *ifile, char *rname)
{
  FILE *output_file;
  int i,pict_count=0;
  fpos_t *pict_start;
  char *pnum, *output_name;

  int line_count = 0;

/*
 *  Determine how many pictures are in the file.
 */
  while (fgets(line, LINEL, ifile) != (char *) NULL) {
    if (!strncmp(" h",line,2) || !strncmp("h ",line,2)) {
      pict_count++;
    }
  }

/*
 *  Simply report the picture count and exit if requested.
 */
  if (count_only) {
    printf("For PostScript file %s:\n"  
           "  Number of pictures = %d\n", rname, pict_count);
    fclose(ifile);
    exit(4);
  }

/*
 *  Record the position numbers of where the pictures start.
 */
  pict_start = (fpos_t *) calloc(pict_count+1,sizeof(fpos_t));
  if ( pict_start == (fpos_t *) NULL ) {
    printf("Error in getting memory for file position pointers\n");
    exit(19);
  }
  pict_count = 1;
  if (fseek(ifile,0L,SEEK_SET)) {
    printf("Error in repositioning the input file to the start\n");
    exit(9);
  }
  while (fgets(line, LINEL, ifile)) {
    line_count++;
    if (!strncmp(" h",line,2) || !strncmp("h ",line,2)) {
      if (fgetpos(ifile, pict_start+pict_count)) {
        printf("Error return from fgetpos.\n");
        exit(20);
      }
      pict_count++;
    }
    else if (!strncmp("/o {",line,4)) {
      if (fgetpos(ifile, pict_start)) {
        printf("Error return from fgetpos.\n");
        exit(20);
      }
    }
  }

/*
 *  pict_count is actually one larger than the total number
 *  of pictures, since we searched for picture end flags and
 *  added in where the first picture started.
 */
  pict_count--;

  pnum = (char *) calloc(5,sizeof(char));
  output_name = (char *) calloc(strlen(rname)+1+4+4,sizeof(char));

/*
 *  Loop through the pictures.
 */
  for (i = 0; i < pict_count; i++) {

/*
 *  Create the output file name.
 */
    sprintf(pnum,"%04d",i+1);
    strcpy(output_name,"\0");
    strcat(output_name,rname);
    strcat(output_name,pnum);
    strcat(output_name,".ps");

/*
 *  Open the output file.
 */
    output_file = fopen(output_name,"w");
    if (output_file == (FILE *) NULL) {
       printf("Cannot open output file %s\n",output_name);
       exit(5);
    }
/*
 *  Write out the header, the prolog, and the color table.
 */
    begin_picture(output_file);
    fflush(output_file);

/*
 *  Write out the picture body, pict_start+i is the start
 *  position for picture i.
 *  
 */
    picture_body(ifile, output_file, pict_start+i);
    fflush(output_file);

/*
 *  Write out the picture termination.
 */
    end_picture(output_file);
    fflush(output_file);

/*
 *  Close the output file.
 */
    fclose(output_file);
  }

/*
 *  Free memory.
 */
  free(pict_start);
  free(pnum);
  free(output_name);

/*
 *  Close the input file.
 */
  fclose(ifile);
}