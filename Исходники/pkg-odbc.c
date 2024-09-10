svalue_t *
f_sql_fetch( svalue_t * argv, int argc )
{
#if ODBC_DEBUG & DEBUG_FUNC
   printf( "call f_sql_fetch( )\n" );
#endif
   int       id, method = 0;
   hDBC      * handle;

   SQLRETURN ret;
   
   STORE_DOUBLE_USED;

   switch( argc ) {
      case 2 :
         TYPE_TEST2( argv, T_NUMBER );
         method = argv->u.number;
         free_svalue( argv );
         argv--;
      case 1 :
         TYPE_TEST1( argv, T_NUMBER );
         id = argv->u.number;
         free_svalue( argv );
         break;
      default:
         errorf( "Too many arguments to sql_fetch().\n" );
         return( NULL );
   }
   
   if ( !(handle = get_db_connection_by_id( id )) ) {
      errorf( "Illegal handle for database.\n" );

      return( NULL );
   }

   if ( !handle->hStmt ) {
      put_number( argv, 0 );
      return( argv );
   }

   //printf( "\nFetching ....\n" );
   ret = SQLFetch( handle->hStmt );
   if ( ret == SQL_NO_DATA ) {
      //printf( "NO_DATA\n" );

      put_number( argv, 0 );
      return( argv );
      
   } else if ( !SQL_SUCCEEDED( ret ) ) {
       put_number( argv, 0 );
       return( argv );
   }

   if ( !handle->columns ) {
      put_number( argv, 0 );
      return( argv );
   }
   
   if ( !method ) { //fetch as array
      put_array( argv, fetch_into_vector( handle ) );
   } else { //fetch as mapping 
      put_mapping( argv, fetch_into_mapping( handle ) );
   }
   
#if ODBC_DEBUG & DEBUG_FUNC
   printf( "ret f_sql_fetch( )\n" );
#endif
   return( argv );
}