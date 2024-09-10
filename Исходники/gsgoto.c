void    scr_label( void )
{
    condcode        cc;
    getnum_block    gn;
    labelcb     *   lb;
    char            linestr[MAX_L_AS_STR];

    scan_start += 2;                    // over dots

    while( *scan_start == ' ' ) {       // may be ...LABEL or ...      LABEL
        scan_start++;                   // over blanks
    }
    if( *scan_start == '\0'  ) {        // no label?
        scan_err = true;
        err_count++;
        g_err( err_missing_name, "" );
        if( input_cbs->fmflags & II_macro ) {
            ultoa( input_cbs->s.m->lineno, linestr, 10 );
            g_info( inf_mac_line, linestr, input_cbs->s.m->mac->name );
        } else {
            ultoa( input_cbs->s.f->lineno, linestr, 10 );
            g_info( inf_file_line, linestr, input_cbs->s.f->filename );
        }
        show_include_stack();
        return;
    } else {

        gn.argstart      = scan_start;
        gn.argstop       = scan_stop;
        gn.ignore_blanks = 0;

        cc = getnum( &gn );             // try numeric expression evaluation
        if( cc == pos ) {               // numeric linenumber

            scan_start = gn.argstart;   // start for next token

            // check if lineno from label matches actual lineno

            if( input_cbs->fmflags & II_macro ) {
                if( gn.result != input_cbs->s.m->lineno ) {
                    scan_err = true;
                    err_count++;
                    g_err( err_label_line, gn.resultstr );
                    ultoa( input_cbs->s.m->lineno, linestr, 10 );
                    g_info( inf_mac_line, linestr, input_cbs->s.m->mac->name );
                    show_include_stack();
                    return;
                }
            } else {
                if( gn.result != input_cbs->s.f->lineno ) {
                    scan_err = true;
                    err_count++;
                    g_err( err_label_line, gn.resultstr );
                    ultoa( input_cbs->s.f->lineno, linestr, 10 );
                    g_info( inf_file_line, linestr, input_cbs->s.f->filename );
                    show_include_stack();
                    return;
                }
            }

            if( input_cbs->fmflags & II_macro ) {
                  // numeric macro label no need to store
            } else {
                wng_count++;
                g_warn( wng_label_num );
                ultoa( input_cbs->s.f->lineno, linestr, 10 );
                g_info( inf_file_line, linestr, input_cbs->s.f->filename );
                show_include_stack();
            }

        } else {                        // no numeric label
            cc = getarg();
            if( cc == pos ) {           // label name specefied
                char    *   p;
                char    *   pt;
                int         len;

                p   = tok_start;
                pt  = token_buf;
                len = 0;
                while( len < arg_flen ) {   // copy to buffer
                    *pt++ = *p++;
                    len++;
                }
                *pt = '\0';
                if( len >  MAC_NAME_LENGTH ) {
                    err_count++;
                    g_err( err_sym_long, token_buf );
                    ultoa( input_cbs->s.f->lineno, linestr, 10 );
                    g_info( inf_file_line, linestr, input_cbs->s.f->filename );
                    show_include_stack();
                    token_buf[MAC_NAME_LENGTH] = '\0';
                }

                if( input_cbs->fmflags & II_macro ) {

                    cc = test_duplicate( token_buf, input_cbs->s.m->lineno );
                    if( cc == pos ) {   // ok name and lineno match
                        // nothing to do
                    } else {
                        if( cc == neg ) {   // name with different lineno
                            scan_err = true;
                            err_count++;
                            g_err( err_label_dup, token_buf );
                            ultoa( input_cbs->s.m->lineno, linestr, 10 );
                            g_info( inf_mac_line, linestr,
                                     input_cbs->s.m->mac->name );
                            show_include_stack();
                            return;
                        } else {        // new label
                            lb              = mem_alloc( sizeof( labelcb ) );
                            lb->prev        = input_cbs->s.m->mac->label_cb;
                            input_cbs->s.m->mac->label_cb = lb;
                            lb->pos         = 0;
                            lb->lineno      = input_cbs->s.m->lineno;
                            strcpy_s( lb->label_name, sizeof( lb->label_name ),
                                      token_buf );
                        }
                    }
                } else {
                    cc = test_duplicate( token_buf, input_cbs->s.f->lineno );
                    if( cc == pos ) {   // ok name and lineno match
                        // nothing to do
                    } else {
                        if( cc == neg ) {   // name with different lineno
                            scan_err = true;
                            err_count++;
                            g_err( err_label_dup, token_buf );
                            ultoa( input_cbs->s.f->lineno, linestr, 10 );
                            g_info( inf_file_line, linestr, input_cbs->s.f->filename );
                            show_include_stack();
                            return;
                        } else {        // new label

                            lb              = mem_alloc( sizeof( labelcb ) );
                            lb->prev        = input_cbs->s.f->label_cb;
                            input_cbs->s.f->label_cb = lb;
                            lb->pos         = input_cbs->s.f->pos;
                            lb->lineno      = input_cbs->s.f->lineno;
                            strcpy_s( lb->label_name, sizeof( lb->label_name ),
                                      token_buf );
                        }
                    }
                }
            } else {
                scan_err = true;
                err_count++;
                g_err( err_missing_name, "" );
                if( input_cbs->fmflags & II_macro ) {
                    ultoa( input_cbs->s.m->lineno, linestr, 10 );
                    g_info( inf_mac_line, linestr, input_cbs->s.m->mac->name );
                } else {
                    ultoa( input_cbs->s.f->lineno, linestr, 10 );
                    g_info( inf_file_line, linestr, input_cbs->s.f->filename );
                }
                show_include_stack();
                return;
            }
        }

        if( *scan_start == ' ' ) {
            scan_start++;               // skip one blank

            if( *scan_start ) {         // rest of line is not empty
                split_input( buff2, scan_start, false );// split and process next
            }
        }
        scan_restart = scan_stop + 1;
        return;
    }
}