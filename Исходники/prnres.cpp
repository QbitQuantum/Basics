void print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
       AS_INF_EXT *aie_ptr, BITS mode, NUM house_mode,
       DATA_PACKET *dpk, char *comment )
{
 COUNT i;
 AS_INF *inf;
 AS_INF_EXT *aiep;
 char buf1[60];
 const char *report;
 NUM maxp, file = -1, aspfile = -1, hsfile = -1, midfile = -1;
 int sign, cusp, k, global = -1, table = -1, ruler;
 static char fmt8[] = { "<%s:>\x80" };

 if ( mode & ASTEROID )
	maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & TEXT ) {
    if ( mode & ASPECTS )
       aspfile = open_asp_files( ASPECT_FILE );
    file = open_files( PLANET_FILE );
    if ( mode & HOUSES )
       hsfile = open_files( HOUSE_FILE );
	if ( mode & (BASE_MID|HALF_MID|FULL_MID) )
	   midfile = open_asp_files( MIDPOINT_SIGN );
    }
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 ) {
    er_close1:
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    close_files( midfile );
    return;
    }
 if ( dpk->chart_code & RELOC_CH )
    k = CHH_RELOC;
 else
    k = CHH_TITLE;
 if ( ( report = get_report( table, global, k ) ) == NULL ) {
    goto er_close1;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
						comment, dpk, global ) ) {
    goto er_close1;
    }
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL || rpmsc == NULL ) {
    er_close2:
    close_tables( table, global );
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    close_files( midfile );
    return;
    }
 fputs("\n\n", stream );
 if ( ferror( stream ) ) {
    goto er_close2;
    }
 for ( i = 0, aiep = aie_ptr, inf = inf_ptr; i <= maxp; ++i, ++inf, ++aiep ) {
	 if ( !inf->calced )
		 continue;
	 if ( x_kb_check() )
	   break;
     print_entry( stream, inf, i, mode, file, aspfile, hsfile, midfile, aiep,
	       data->name, comment, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
 if ( mode & TEXT ) {
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    close_files( midfile );
    }
 if ( x_kb_check() )
    return;
 if ( mode & HOUSES ) {
    if ( mode & TEXT ) {
       if ( ( hsfile = open_files( SIGN_HOUSE_FILE ) ) == -1 )
	  mode &= ( 0xffff ^ TEXT );
       }
    if ( mode & HOUSES )
       out_do_house_cusps(stream,data->name, comment, "",
					table, global, house_cusps, CH__HOUSE_HEAD );
 if ( ( report = get_report( table, global, CH__HS_SGN_HED ) ) == NULL ) {
    er_close3:
    close_tables( table, global );
    close_files( hsfile );
    return;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 if ( ( report = get_report( table, global, CH__HOUSE_SIGN ) ) == NULL ) {
    goto er_close3;
    }
 if ( ( rphs = strdup( report )) == NULL )
    goto er_close3;
 for ( i = 1; i <= 12; ++i ) {
     if ( x_kb_check() )
	break;
     output_house_sign( stream, i, house_cusps[i], &cusp, &sign,
						     data->name, (char *)rphs );
     ruler = sign_rulers[sign];
	 if ( cusp == -1 ) {
	if ( mode & TEXT )
	   get_transfer_text( sign, i, hsfile, stream );
	   get_transfer_text( ruler, 13, hsfile, stream );
	}
     else {
	if ( mode & TEXT ) {
	   fprintf( stream, (char *)fmt8, sign_str( sign ) );
	   get_transfer_text( sign, i, hsfile, stream );
	   fprintf( stream, (char *)fmt8, sign_str( cusp ) );
	   get_transfer_text( cusp, i, hsfile, stream );
	   get_transfer_text( ruler, 13, hsfile, stream );
	   }
	}
     }
 if ( mode & TEXT )
    close_files( hsfile );
 }
 if ( x_kb_check() ) {
    close_tables( table, global );
    return;
    }
 close_tables( table, global );
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 )
    return;
 if ( mode & SUMMARY )
    print_summary(stream, mode, table, global, data->name, comment );
 close_tables( table, global );
}