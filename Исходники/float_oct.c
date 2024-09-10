void __inttooctfloatpart(long double value, char *buffer, int precision) {
  /* Set the float part value in an octal string stored in the given pointer ;
   ***************************************************************************/
 
  /** temporary final result container variable used for computing */
  char *oct_str_saved=malloc(96) ;
  memset(oct_str_saved,'\0',96) ;

  int c=0 ;
  if (value < 0) {
    /** value needed for computing */
    value=fabs(value) ;
  }
  while (c < (precision)) {
    /** loop for computing until precision is reach */
   
    char *to_oct=malloc(48) ;
    memset(to_oct,'\0',48) ;
   
    long double res_int ;
    long double res_float ;
   
    res_float=modfl(value* 8.0,&res_int) ; /** modulo float */
   
    inttooct(res_int,to_oct) ;  /** getting the octal string of the integer to add to float part */
   
    strcat(oct_str_saved,to_oct) ;
    if ( res_float == 0.0 ) {
      break ; /** reach end of octal string computing */
    }
   
    value=res_float ; /** updating value */
    c++ ;
  }
 
  sprintf(buffer,"%s",oct_str_saved) ;
  free(oct_str_saved) ;
 
}