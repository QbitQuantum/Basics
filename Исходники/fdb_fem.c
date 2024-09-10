/* Makes command separated string for possible displacement/force * types */
char *fdbFemStrSuppForcTypListInt(char *dtype)
{
  long restypes[270];
  long len = 270 ;
  long restypes_ret[270];
  long len_ret = 0 ;
  ldiv_t divval ;
  ldiv_t divval2 ;
  long type ;
  long i, j, k ;

  for (i=0; i<len; i++) 
  { 
    restypes[i] = 0 ; 
    restypes_ret[i] = 0 ; 
  }
  len_ret = 0 ;


  for (i=0; i<len; i++)
  {
    restypes[i] = 0 ;

    for (j=0; j<fdbInputTabLenAll(ETYPE); j++ ) /* type=0 is not used */
    {
      type = fdbInputGetInt(ETYPE,ETYPE_TYPE, j) ;
      if ((type<=0) || (type >=fdbElementTypeLen)) { break ; }
      
      for (k=0; k<fdbElementType[type].ndofs; k++)
      {
        divval  = ldiv(i+1,KNOWN_DOFS);
        divval2 = ldiv(fdbElementType[type].ndof[k],KNOWN_DOFS);

        if (
            (divval.rem == fdbElementType[type].ndof[k])
          ||
          ((divval2.quot >= 1) && (divval2.rem == 0) && (divval.rem == 0))
           )
        {
          restypes[i] = 1 ;
          break ;
        }
      }
      if (restypes[i] == 1) {break;}
    }
  }

  for (i=0; i<len; i++)
  {
    if (restypes[i] == 1)
    {
      restypes_ret[len_ret] = (i+1) ;
      len_ret++ ;
    }
  }

  if (len_ret < 1) { return(" ") ; } 

  return(ciListVarsListedCSV(dtype, restypes_ret, len_ret)) ;
}