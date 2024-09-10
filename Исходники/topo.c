/*
 * Read a topography file and initialize Topo and TopoData.
 * Input:  filename - name of topo file.
 * Return:  0 if error, otherwise non-zero for success.
 */
int read_topo( struct Topo *topo, char *filename )
{
   int f;
   int n;
   char id[40];

   f = open( filename, O_RDONLY );
   if (f<0) {
      printf("Topo file %s not found\n", filename );
      return 0;
   }

   /* Read topo file header */
   read_bytes( f, id, 40 );
   read_float4( f, &(topo->Topo_westlon) );
   read_float4( f, &(topo->Topo_eastlon) );
   read_float4( f, &(topo->Topo_northlat) );
   read_float4( f, &(topo->Topo_southlat) );
   read_int4( f, &(topo->Topo_rows) );
   read_int4( f, &(topo->Topo_cols) );

   if (strncmp(id,"TOPO2",5)==0) {
      /* OK */
   }
   else if (strncmp(id,"TOPO",4)==0) {
      /* OLD STYLE: bounds given as ints, convert to floats */
      int *p;
      p = (int *) &(topo->Topo_westlon);  topo->Topo_westlon = (float) *p / 100.0;
      p = (int *) &(topo->Topo_eastlon);  topo->Topo_eastlon = (float) *p / 100.0;
      p = (int *) &(topo->Topo_northlat); topo->Topo_northlat = (float) *p / 100.0;
      p = (int *) &(topo->Topo_southlat); topo->Topo_southlat = (float) *p / 100.0;
   }
   else {
      printf("%s is not a TOPO file >%s<\n", filename,id);
      close(f);
      return 0;
   }
	if(topo->TopoData)
	  free(topo->TopoData);

   topo->TopoData = (short *) malloc(topo->Topo_rows * topo->Topo_cols * sizeof(short));

   /* dtx->TopoData = (short *) allocate( dtx, dtx->Topo_rows * dtx->Topo_cols
                                       * sizeof(short) ); */
   if (!topo->TopoData) {
	  printf("ERROR: Failed to allocate space for topo data\n");
	  close(f);
	  return 0;
   }


   n = topo->Topo_rows * topo->Topo_cols;
   if (read_int2_array( f, topo->TopoData, n) < n) {
	  printf("ERROR: could not read data file or premature end of file\n");
	  free( topo->TopoData);
	  topo->TopoData = NULL;
	  close(f);
	  return 0;
   }

	close(f);
   return 1;
}