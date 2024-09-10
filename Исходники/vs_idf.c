double vs_term_freqency(vector *v, t_uuid dimensionid){
  int max,i,val;
  double term_total, document_total;
  dimension *dim,*dims; 
  t_uuid  v_dimensionid;
  vs_value value;

  dim = vs_getvalue(v,dimensionid);
  term_total=0;
  if(dim!=NULL){
    value = dim->value; 
    term_total = value.floatvalue;
  }
  document_total = 0;
  max = v->dimensioncount;
  i=0;  
  dims = v->dimensions; 
  while (i<max){
    val = (int)dims + (int)(i * sizeof(dimension));
    dim = (dimension *)(val);
    v_dimensionid = dim->dimensionid;
    value = dim->value;
    if(!IsEqualGuid(dimensionid,v_dimensionid)){
        document_total+=value.floatvalue;
    }
    i++;
  }
 if(document_total==0){
   return 0;
 } 
  return (term_total / document_total );
}