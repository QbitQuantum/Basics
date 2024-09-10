/* dirdcl: recenoce un declarador directo */
void dirdcl( void ){
  int type;

  if( tokentype == '(' ){            /* ( dcl )   */
    dcl();
    if( tokentype != ')' )
      printf( "error: falta )\n" );
  } else if( tokentype == NAME )     /* nombre de variable */
    strcpy( name, token );
  else
    printf( "error: nombre o (dcl) esperado\n" );

  while( ( type = gettoken() ) == PARENS || type == BRACKETS )
    if( type == PARENS )
      strcat( out, " funcion que regresa" );
    else {
      strcat( out, " arreglo" );
      strcat( out, token );
      strcat( out, " de" );
    }
}