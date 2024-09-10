/***********************************************************************
 *           NE_LoadSegment
 */
BOOL NE_LoadSegment( NE_MODULE *pModule, WORD segnum )
{
    WORD count;
    DWORD pos;
    const struct relocation_entry_s *rep;
    int size;
    SEGTABLEENTRY *pSegTable = NE_SEG_TABLE( pModule );
    SEGTABLEENTRY *pSeg = pSegTable + segnum - 1;

    if (pSeg->flags & NE_SEGFLAGS_LOADED)
    {
	/* self-loader ? -> already loaded it */
	if (pModule->ne_flags & NE_FFLAGS_SELFLOAD)
	    return TRUE;

	/* leave, except for DGROUP, as this may be the second instance */
	if (segnum != pModule->ne_autodata)
            return TRUE;
    }

    if (!pSeg->filepos) return TRUE;  /* No file image, just return */

    TRACE_(module)("Loading segment %d, hSeg=%04x, flags=%04x\n",
                    segnum, pSeg->hSeg, pSeg->flags );
    pos = pSeg->filepos << pModule->ne_align;
    if (pSeg->size) size = pSeg->size;
    else size = pSeg->minsize ? pSeg->minsize : 0x10000;

    if (pModule->ne_flags & NE_FFLAGS_SELFLOAD && segnum > 1)
    {
 	/* Implement self-loading segments */
 	SELFLOADHEADER *selfloadheader;
        void *oldstack;
        HFILE16 hFile16;
        WORD args[3];
        DWORD ret;

 	selfloadheader = MapSL( MAKESEGPTR(SEL(pSegTable->hSeg),0) );
        oldstack = getWOW32Reserved();
		setWOW32Reserved((void *)MAKESEGPTR(pModule->self_loading_sel,
                                                           0xff00 - sizeof(STACK16FRAME)));

        hFile16 = NE_OpenFile( pModule );
        TRACE_(dll)("Call LoadAppSegProc(hmodule=0x%04x,hf=%x,segnum=%d)\n",
                    pModule->self,hFile16,segnum );
        args[2] = pModule->self;
        args[1] = hFile16;
        args[0] = segnum;
        WOWCallback16Ex( (DWORD)selfloadheader->LoadAppSeg, WCB16_PASCAL, sizeof(args), args, &ret );
        pSeg->hSeg = LOWORD(ret);
        TRACE_(dll)("Ret LoadAppSegProc: hSeg=0x%04x\n", pSeg->hSeg);
        _lclose16( hFile16 );
		setWOW32Reserved(oldstack);

        pSeg->flags |= NE_SEGFLAGS_LOADED;
        return TRUE;
    }
    else if (!(pSeg->flags & NE_SEGFLAGS_ITERATED))
    {
        void *mem = GlobalLock16(pSeg->hSeg);
        if (!NE_READ_DATA( pModule, mem, pos, size ))
            return FALSE;
        pos += size;
    }
    else
    {
        /*
          The following bit of code for "iterated segments" was written without
          any documentation on the format of these segments. It seems to work,
          but may be missing something.
        */
        const char *buff = NE_GET_DATA( pModule, pos, size );
        const char* curr = buff;
        char *mem = GlobalLock16(pSeg->hSeg);

        pos += size;
        if (buff == NULL) return FALSE;

        while(curr < buff + size) {
            unsigned int rept = ((const short *)curr)[0];
            unsigned int len =  ((const short *)curr)[1];

            curr += 2*sizeof(short);
            while (rept--)
            {
                memcpy( mem, curr, len );
                mem += len;
            }
            curr += len;
        }
    }

    pSeg->flags |= NE_SEGFLAGS_LOADED;

    /* Perform exported function prolog fixups */
    NE_FixupSegmentPrologs( pModule, segnum );

    if (!(pSeg->flags & NE_SEGFLAGS_RELOC_DATA))
        return TRUE;  /* No relocation data, we are done */

    if (!NE_READ_DATA( pModule, &count, pos, sizeof(count) ) || !count) return TRUE;
    pos += sizeof(count);

    TRACE("Fixups for %.*s, segment %d, hSeg %04x\n",
          *((BYTE *)pModule + pModule->ne_restab),
          (char *)pModule + pModule->ne_restab + 1,
          segnum, pSeg->hSeg );

    if (!(rep = NE_GET_DATA( pModule, pos, count * sizeof(struct relocation_entry_s) )))
        return FALSE;

    return apply_relocations( pModule, rep, count, segnum );
}