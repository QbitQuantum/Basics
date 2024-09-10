ret_code ExterndefDirective( int i, struct asm_tok tokenarray[] )
/***************************************************************/
{
    char                *token;
#if MANGLERSUPP
    char                *mangle_type = NULL;
#endif
    struct asym         *sym;
    enum lang_type      langtype;
    char isnew;
    struct qualified_type ti;

    DebugMsg1(("ExterndefDirective(%u) enter\n", i));

    i++; /* skip EXTERNDEF token */
#if MANGLERSUPP
    mangle_type = Check4Mangler( &i, tokenarray );
#endif
    do {

        ti.Ofssize = ModuleInfo.Ofssize;

        /* get the symbol language type if present */
        langtype = ModuleInfo.langtype;
        GetLangType( &i, tokenarray, &langtype );

        /* get the symbol name */
        if( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        token = tokenarray[i++].string_ptr;

        /* go past the colon */
        if( tokenarray[i].token != T_COLON ) {
            return( EmitError( COLON_EXPECTED ) );
        }
        i++;
        sym = SymSearch( token );

        //typetoken = tokenarray[i].string_ptr;
        ti.mem_type = MT_EMPTY;
        ti.size = 0;
        ti.is_ptr = 0;
        ti.is_far = FALSE;
        ti.ptr_memtype = MT_EMPTY;
        ti.symtype = NULL;
        ti.Ofssize = ModuleInfo.Ofssize;

        if ( tokenarray[i].token == T_ID && ( 0 == _stricmp( tokenarray[i].string_ptr, "ABS" ) ) ) {
            /* v2.07: MT_ABS is obsolete */
            //ti.mem_type = MT_ABS;
            i++;
        } else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
            /* dont scan this line further!
             * CreateProto() will either define a SYM_EXTERNAL or fail
             * if there's a syntax error or symbol redefinition.
             */
            sym = CreateProto( i + 1, tokenarray, token, langtype );
#if 0 /* global queue is obsolete */
            if ( sym && sym->isglobal == FALSE ) {
                sym->isglobal = TRUE;
                QAddItem( &ModuleInfo.g.GlobalQueue, sym );
            }
#endif
            return( sym ? NOT_ERROR : ERROR );
        } else if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
            if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                return( ERROR );
        }

        isnew = FALSE;
        if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
            sym = CreateExternal( sym, token, TRUE );
            isnew = TRUE;
        }

        /* new symbol? */

        if ( isnew ) {
            DebugMsg1(("ExterndefDirective(%s): memtype=%X set, ofssize=%X\n", token, ti.mem_type, ti.Ofssize ));

            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                CreateProc( sym, NULL, SYM_EXTERNAL );
                CopyPrototype( (struct dsym *)sym, (struct dsym *)ti.symtype );
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
            }
            switch ( ti.mem_type ) {
            //case MT_ABS:
            case MT_EMPTY:
                /* v2.04: hack no longer necessary */
                //if ( sym->weak == TRUE )
                //    sym->equate = TRUE; /* allow redefinition by EQU, = */
                break;
            case MT_FAR:
                /* v2.04: don't inherit current segment for FAR externals
                 * if -Zg is set.
                 */
                if ( Options.masm_compat_gencode )
                    break; 
                /* fall through */
            default:
                //SetSymSegOfs( sym );
                sym->segment = &CurrSeg->sym;
            }
            sym->Ofssize = ti.Ofssize;

            if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize ) {
                sym->seg_ofssize = ti.Ofssize;
                if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->Ofssize != sym->seg_ofssize )
                    sym->segment = NULL;
            }

            sym->mem_type = ti.mem_type;
            sym->is_ptr = ti.is_ptr;
            sym->isfar = ti.is_far;
            sym->ptr_memtype = ti.ptr_memtype;
            if ( ti.mem_type == MT_TYPE )
                sym->type = ti.symtype;
            else
                sym->target_type = ti.symtype;

            /* v2.04: only set language if there was no previous definition */
            SetMangler( sym, langtype, mangle_type );

        } else if ( Parse_Pass == PASS_1 ) {

            /* v2.05: added to accept type prototypes */
            if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
                ti.mem_type = ti.symtype->mem_type;
                ti.symtype = NULL;
            }
            /* ensure that the type of the symbol won't change */

            if ( sym->mem_type != ti.mem_type ) {
                /* if the symbol is already defined (as SYM_INTERNAL), Masm
                 won't display an error. The other way, first externdef and
                 then the definition, will make Masm complain, however */
                DebugMsg(("ExterndefDirective: type conflict for %s. mem_types old-new: %X-%X\n", sym->name, sym->mem_type, ti.mem_type));
                EmitWarn( 1, SYMBOL_TYPE_CONFLICT, sym->name );
            } else if ( sym->mem_type == MT_TYPE && sym->type != ti.symtype ) {
                struct asym *sym2 = sym;
                /* skip alias types and compare the base types */
                DebugMsg(("ExterndefDirective(%s): types differ: %X (%s) - %X (%s)\n", sym->name, sym->type, sym->type->name, ti.symtype, ti.symtype->name));
                while ( sym2->type )
                    sym2 = sym2->type;
                while ( ti.symtype->type )
                    ti.symtype = ti.symtype->type;
                if ( sym2 != ti.symtype ) {
                    DebugMsg(("ExterndefDirective(%s): type conflict old-new: %X (%s) - %X (%s)\n", sym->name, sym2, sym2->name, ti.symtype, ti.symtype->name));
                    EmitWarn( 1, SYMBOL_TYPE_CONFLICT, sym->name );
                }
            }

            /* v2.04: emit a - weak - warning if language differs.
             * Masm doesn't warn.
             */
            if ( langtype != LANG_NONE && sym->langtype != langtype )
                EmitWarn( 3, LANGUAGE_ATTRIBUTE_CONFLICT, sym->name );
        }
        sym->isdefined = TRUE;

#if 0
        /* write a global entry if none has been written yet */
        if ( sym->state == SYM_EXTERNAL && sym->weak == FALSE )
            ;/* skip EXTERNDEF if a real EXTERN/COMM was done */
        else if ( sym->isglobal == FALSE ) {
            sym->isglobal = TRUE;
            DebugMsg1(("ExterndefDirective(%s): writing a global entry\n", sym->name));
            QAddItem( &ModuleInfo.g.GlobalQueue, sym );
        }
#else
        if ( sym->state == SYM_INTERNAL && sym->ispublic == FALSE ) {
            sym->ispublic = TRUE;
            AddPublicData( sym );
        }
#endif

        if ( tokenarray[i].token != T_FINAL )
            if ( tokenarray[i].token == T_COMMA ) {
                if ( (i + 1) < Token_Count )
                    i++;
            } else {
                return( EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos ) );
            }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}