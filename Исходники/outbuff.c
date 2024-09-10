void ob_flush( void )
{

    if( fwrite( buffout.text, sizeof( uint8_t ), buffout.current, out_file_fp ) < buffout.current ) {
        xx_simple_err_c( err_write_out_file, out_file );
        return;
    }
    buffout.current = 0;
#ifdef __UNIX__
    if( fprintf_s( out_file_fp, "\n" ) < strlen( "\n" ) ) {
        xx_simple_err_c( err_write_out_file, out_file );
        return;
    }
#else
    if( fprintf_s( out_file_fp, "\r\n" ) < strlen( "\r\n" ) ) {
        xx_simple_err_c( err_write_out_file, out_file );
        return;
    }
#endif
    return;
}