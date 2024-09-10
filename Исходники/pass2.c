void write_string_table( void )
{
    long t = 0;

    if( string_table_index > 4 )
      t = string_table_index;

    fseek( obj_fd, 0L, 2 );
    FWRITE( &t, sizeof(long), 1, obj_fd );
#ifdef MSDOS
    FWRITE( &string_table[4], sizeof(char), (size_t) (string_table_index - 4), obj_fd );
#else
    FWRITE( &string_table[4], sizeof(char), (string_table_index - 4), obj_fd );
#endif
}