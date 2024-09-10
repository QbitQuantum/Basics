void floattohexfloat(long double int_to_hex,char *hex_str) {
  /* Convert an float value in an hexadecimal string stored in the given pointer;
   ******************************************************************************/
  long double int_part=0.0 ;
  long double float_part=0.0 ;
  _Bool is_negativ = false ;
  if (int_to_hex < 0) {
    int_to_hex=fabs(int_to_hex) ;
    is_negativ=true ;
  }
  
  float_part=modfl(int_to_hex,&int_part) ; /** modulo float */
  
  /** variables for splitting in integer and float part */
  char *int_part_str_hex=malloc(129) ;
  char *float_part_str_hex=malloc(129) ;
  memset(int_part_str_hex,'\0',129) ;
  memset(float_part_str_hex,'\0',129) ;
  
  /** Perform splitting in integer and float part */
  inttohex((long long) int_part,int_part_str_hex) ;
  inttohexfloatpart(float_part,float_part_str_hex,128) ;

  /** result binar string variable (pointer given as argument) */
  memset(hex_str,'\0',129) ;
  
  if ((is_negativ) && (int_part_str_hex[0] != '-')) {
    /** Case value to convert in binfloat string is negativ */
    strcpy(hex_str,"-") ;
  }
  
  /** Assemble final binar string */
  strcat(hex_str,int_part_str_hex) ;
  strcat(hex_str,".") ;
  strcat(hex_str,float_part_str_hex) ;
  
}