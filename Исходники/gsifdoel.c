void    scr_el( void )
{
    ifcb    *   cb = input_cbs->if_cb;
    char        linestr[MAX_L_AS_STR];

    scan_err = false;
    cb->if_flags[cb->if_level].iflast = false;
    cb->if_flags[cb->if_level].ifcwte = false;

    if( !(cb->if_flags[cb->if_level].iftrue
          || cb->if_flags[cb->if_level].iffalse)

        || cb->if_flags[cb->if_level].ifthen
        || cb->if_flags[cb->if_level].ifelse
        || cb->if_flags[cb->if_level].ifdo ) {

        scan_err = true;
        g_err( err_if_else );
        if( input_cbs->fmflags & II_macro ) {
            ultoa( input_cbs->s.m->lineno, linestr, 10 );
            g_info( inf_mac_line, linestr, input_cbs->s.m->mac->name );
        } else {
            ultoa( input_cbs->s.f->lineno, linestr, 10 );
            g_info( inf_file_line, linestr, input_cbs->s.f->filename );
        }
        show_ifcb( "else", cb );
        show_include_stack();
        err_count++;
        return;
    }
    cb->if_flags[cb->if_level].ifelse = true;
    ProcFlags.keep_ifstate = true;
    if( input_cbs->fmflags & II_research && GlobalFlags.firstpass ) {
        show_ifcb( "else", cb );
    }
    garginit();                         // find end of control word

    while( *scan_start == ' ' ) {
        scan_start++;
    }

    if( *scan_start ) {                 // rest of line is not empty split
        split_input( buff2, scan_start, false );// and process next
    }
    scan_restart = scan_stop + 1;
    return;
}