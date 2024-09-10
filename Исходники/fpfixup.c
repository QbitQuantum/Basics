void AddFloatingPointEmulationFixup( struct code_info *CodeInfo )
/***************************************************************/
{
    int i;
    enum fp_patches patch;
    struct asym *sym[2];
    struct fixup *fixup;
    int_32 data;
    char name[8] = "F__RQQ";

    DebugMsg(("AddFloatingPointEmulationFixup enter, token=%u, regoverride=%d\n", CodeInfo->token, CodeInfo->prefix.RegOverride ));

    if( CodeInfo->token == T_FWAIT ) {
        patch = FPP_WAIT;
    } else if ( CodeInfo->prefix.RegOverride == EMPTY ) {
        patch = FPP_NORMAL;
    } else {
        patch = CodeInfo->prefix.RegOverride + 2;
    }

    /* emit 1-2 externals for the patch if not done already */
    for ( i = 0; i < 2; i++ ) {
        sym[i] = NULL;
        if ( patchmask & ( 1 << ( i*8+patch ) ) ) {
            name[1] = 'I' + i;
            name[2] = patchchr2[patch];
            sym[i] = SymSearch( name );
            if( sym[i] == NULL || sym[i]->state == SYM_UNDEFINED ) {
                sym[i] = MakeExtern( name, MT_FAR, NULL, sym[i], USE16 );
                sym[i]->langtype = LANG_NONE;
            }
        }
    }

    /* no need for fixups if no object file is written */
    if ( write_to_file == FALSE )
        return;

    /* make sure the next 3 bytes in code stream aren't separated.
     * The first fixup covers bytes $+0 and $+1, the (possible) second
     * fixup covers bytes $+1 and $+2.
     */
    if( Options.output_format == OFORMAT_OMF &&
       ( CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc + 3 ) > MAX_LEDATA_THRESHOLD )
        omf_FlushCurrSeg();

    for ( i = 0; i < 2 ; i++ ) {
        if ( sym[i] ) {
            fixup = CreateFixup( sym[i], FIX_OFF16, OPTJ_NONE );
            fixup->frame_type = FRAME_TARG;
            /* assume locofs has been set inside CreateFixup() */
            //fixup->locofs = CurrSeg->e.seginfo->current_loc + i;
            fixup->locofs += i;
            data = 0;
            store_fixup( fixup, CurrSeg, &data );
        }
    }
    return;
}