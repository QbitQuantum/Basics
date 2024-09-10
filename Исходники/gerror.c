void g_suicide( void )
{
    out_msg( "\n\nWGML suicide\n\n" );
    if( GlobalFlags.research ) {        // TBD

        print_macro_dict( macro_dict, true );

        if( tag_dict != NULL ) {
            print_tag_dict( tag_dict );
        }
        print_single_funcs_research();
        print_multi_funcs_research();

        if( global_dict != NULL ) {
            print_sym_dict( global_dict );
        }
        print_sym_dict( sys_dict );
    }
    out_msg( "\n\nWGML suicide\n\n" );
    flushall();                         // TBD
    fcloseall();                        // TBD
    if( environment ) {
        longjmp( *environment, 1 );
    }
    my_exit( 16 );
}