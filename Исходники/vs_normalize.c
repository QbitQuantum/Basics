vs_cursor *vsc_normalize (vs_cursor *source){
  vs_cursor *normalized;
  vs_rowset *rowset;
  dimension *dims,*dim ;
  vector *v, *view_v, *compare, *final;
  t_uuid id;
  long max,i,dimval,c;
  normalized = vsc_createcursor();

		printf( "Normalize: %ld vectors\r\n",source->count); 
  vsc_reset (source) ;
 // view = vsc_create_view(source);
  printf("Normalizing: %ld vectors\r\n",source->count);
  c=0;
  while ( !vsc_eof (source) ){
    c++;
    v = vsc_readnext(source);

  // printf("   Vector %ld of %ld : has %ld ",c,source->count, v->dimensioncount);


    compare = vs_createvector(NullGuid(),0);
    
    max = v->dimensioncount;
    dims= v->dimensions;

    rowset = vsr_createrowset(source,v);
    vsr_reset(rowset);
    while (!vsr_eof (rowset)){
      view_v = vsr_readnext(rowset);
      if (!IsEqualGuid(v->vectorid,view_v->vectorid)){
          for (i=0;i<max;i++){
            dimval = (long)dims + (long)(i * sizeof(dimension));
            dim = (dimension *)(dimval);
            id = dim->dimensionid;
            if (vsc_normalize_hasdimension(view_v,id)){
              vsc_normalize_incriment_dimension(compare,id);
            }
          }
      }
    }
    //now we have compare, holding some dimensions with values>1 matching our vector.
    //we need to clean out any dimensions in our vector that don't have corresponding values
    final = vsc_normalize_vector(v,compare);
   //  printf("  ending at %ld \r\n",compare->dimensioncount);
    if(final!=NULL){
      vsc_rawloadvector(normalized,final);
    }
    vsr_destroyrowset(&rowset);
    vs_destroyvector(&compare);
  }