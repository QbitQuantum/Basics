ret_code GrpDir( int i, struct asm_tok tokenarray[] )
/***************************************************/
{
    char        *name;
    struct dsym *grp;
    struct dsym *seg;

    /* GROUP directive must be at pos 1, needs a name at pos 0 */
    if( i != 1 ) {
        EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
        return( ERROR );
    }
#if COFF_SUPPORT || ELF_SUPPORT
    /* GROUP valid for OMF + BIN only */
    if ( Options.output_format == OFORMAT_COFF
#if ELF_SUPPORT
        || Options.output_format == OFORMAT_ELF
#endif
       ) {
        EmitError( GROUP_DIRECTIVE_INVALID_FOR_COFF );
        return( ERROR );
    }
#endif
    grp = CreateGroup( tokenarray[0].string_ptr );
    if( grp == NULL )
        return( ERROR );

    i++; /* go past GROUP */

    do {

        /* get segment name */
        if ( tokenarray[i].token != T_ID ) {
            EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );
            return( ERROR );
        }
        name = tokenarray[i].string_ptr;
        i++;

        seg = (struct dsym *)SymSearch( name );
        if ( Parse_Pass == PASS_1 ) {
            if( seg == NULL || seg->sym.state == SYM_UNDEFINED ) {
                seg = CreateSegment( seg, name, TRUE );
                /* inherit the offset magnitude from the group */
                if ( grp->e.grpinfo->seglist )
                    seg->e.seginfo->Ofssize = grp->sym.Ofssize;
            } else if( seg->sym.state != SYM_SEG ) {
                EmitErr( SEGMENT_EXPECTED, name );
                return( ERROR );
            } else if( seg->e.seginfo->group != NULL &&
                       seg->e.seginfo->group != &grp->sym ) {
                /* segment is in another group */
                DebugMsg(("GrpDir: segment >%s< is in group >%s< already\n", name, seg->e.seginfo->group->name));
                EmitErr( SEGMENT_IN_ANOTHER_GROUP, name );
                return( ERROR );
            }
            /* the first segment will define the group's word size */
            if( grp->e.grpinfo->seglist == NULL ) {
                grp->sym.Ofssize = seg->e.seginfo->Ofssize;
            } else if ( grp->sym.Ofssize != seg->e.seginfo->Ofssize ) {
                EmitErr( GROUP_SEGMENT_SIZE_CONFLICT, grp->sym.name, seg->sym.name );
                return( ERROR );
            }
        } else {
            /* v2.04: don't check the "defined" flag. It's for IFDEF only! */
            //if( seg == NULL || seg->sym.state != SYM_SEG || seg->sym.defined == FALSE ) {
            /* v2.07: check the "segment" field instead of "defined" flag! */
            //if( seg == NULL || seg->sym.state != SYM_SEG ) {
            if( seg == NULL || seg->sym.state != SYM_SEG || seg->sym.segment == NULL ) {
                EmitErr( SEG_NOT_DEFINED, name );
                return( ERROR );
            }
        }

        /* insert segment in group if it's not there already */
        if ( seg->e.seginfo->group == NULL ) {
            struct seg_item    *si;

            /* set the segment's grp */
            seg->e.seginfo->group = &grp->sym;

            si = LclAlloc( sizeof( struct seg_item ) );
            si->seg = seg;
            si->next = NULL;
            grp->e.grpinfo->numseg++;

            /* insert the segment at the end of linked list */
            if( grp->e.grpinfo->seglist == NULL ) {
                grp->e.grpinfo->seglist = si;
            } else {
                struct seg_item *curr;
                curr = grp->e.grpinfo->seglist;
                while( curr->next != NULL ) {
                    curr = curr->next;
                }
                curr->next = si;
            }
        }

        if ( i < Token_Count ) {
            if ( tokenarray[i].token != T_COMMA || tokenarray[i+1].token == T_FINAL ) {
                EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos );
                return( ERROR );
            }
            i++;
        }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}