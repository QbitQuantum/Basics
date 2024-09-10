void __inttobinfloatpart(long double value, char *buffer, int precision) {
  /* Set the float part value in an binary string stored in the given pointer ;
   ***************************************************************************/
 
  /** temporary final result container variable used for computing */
  char *bin_str_saved=malloc(96) ;
  memset(bin_str_saved,'\0',96) ;
 
  int c=0 ;
  if (value < 0) {
    /** value needed for computing */
    value=fabs(value) ;
  }
  while (c < precision) {
    /** loop for computing until precision is reach */
   
    long double res_int ;
    long double res_float ;
   
    res_float=modfl(value * 2.0,&res_int) ; /** modulo float */
   
   
    if ( res_int  == 0) {
      strcat(bin_str_saved,"0") ; /** getting the binary string component as the integer to add to float part */
    }
    else if ( res_int  == 1 ) {
      strcat(bin_str_saved,"1") ; /** getting the binary string component as the integer to add to float part */
    }
    else {
      return ;
    }
   
    if ( res_float == 0.0 ) {
      break ; /** reach end of binary float string computing */
    }
   
    value=res_float ;
   
    c++ ;
  }
 
  c=sprintf(buffer,"%s",bin_str_saved) ;
  buffer[c]='\0' ;
  free(bin_str_saved) ;
}