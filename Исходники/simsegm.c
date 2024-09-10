static void SetSimSeg( enum sim_seg segm, const char *name )
/**********************************************************/
{
    char *pAlign = "WORD";
    char *pAlignSt = "PARA";
    char *pUse = "";
    struct asym *sym;
    const char *pFmt;
    const char *pClass;

    if ( ModuleInfo.defOfssize > USE16 ) {
        if ( ModuleInfo.model == MODEL_FLAT )
            pUse = "FLAT";
        else
            pUse = "USE32";
        if (( ModuleInfo.curr_cpu & P_CPU_MASK ) <= P_386 )
            pAlign = "DWORD";
        else
            pAlign = "PARA";
        pAlignSt = pAlign;
    }

    if ( segm == SIM_CODE )
        pClass = GetCodeClass();
    else
        pClass = SegmClass[segm];

    if ( segm == SIM_STACK || segm == SIM_FARDATA || segm == SIM_FARDATA_UN )
        pAlign = pAlignSt;

    pFmt = "%s %r %s %s %s '%s'";
    if ( name == NULL ) {
        name = SegmNames[segm];
        if ( ModuleInfo.simseg_init & ( 1 << segm ) )
            pFmt = "%s %r";
        else {
            ModuleInfo.simseg_init |= ( 1 << segm );
            /* v2.05: if segment exists already, use the current attribs.
             * This allows a better mix of full and simplified segment
             * directives. Masm behaves differently: the attributes
             * of the simplified segment directives have highest priority.
             */
            sym = SymSearch( name );
            if ( sym && sym->state == SYM_SEG && ((struct dsym *)sym)->e.seginfo->lname_idx != 0 )
                pFmt = "%s %r";
        }
    } else {
        sym = SymSearch( name );
        /* v2.04: testing for state SYM_SEG isn't enough. The segment
         * might have been "defined" by a GROUP directive. Additional
         * check for segment's lname index is needed.
         */
        //if ( sym && sym->state == SYM_SEG )
        if ( sym && sym->state == SYM_SEG && ((struct dsym *)sym)->e.seginfo->lname_idx != 0 )
            pFmt = "%s %r";
    }
    AddLineQueueX( pFmt, name, T_SEGMENT, pAlign, pUse, SegmCombine[segm], pClass );
    return;
}