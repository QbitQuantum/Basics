// This function is a callback from LineServices (the pfnFmt callback)
// Line services calls this to get the formattnig information for
// a non-text object in the layout, i.e. an image or a table or a div.
// We create a dobj and give it back to LS here.
// This is like a dobj constructor.
LSERR WINAPI CEmbeddedILSObj::Fmt(/*[in]*/PCFMTIN pfmtin, /*[out]*/FMTRES* pfmtres)
{
    LSTRACE(Fmt);

    BOOL                fOwnLine;
    INT                 xMinWidth;
    LONG                cchSite;
    LONG                xWidth, yHeight;
    OBJDIM              objdim;
    stylePosition       bPositionType;
    LSERR               lserr           = lserrNone;
    CLineServices*      pLS             = _pLS;
    CFlowLayout*        pFlowLayout     = pLS->_pFlowLayout;
    PLSRUN              plsrun          = PLSRUN(pfmtin->lsfrun.plsrun);
    CLayout*            pLayout         = plsrun->GetLayout(pFlowLayout);
    CElement*           pElementLayout;
    CTreeNode*          pNodeLayout;
    const CCharFormat*  pCF;
    const CFancyFormat* pFF;
    CEmbeddedDobj*      pdobj = new CEmbeddedDobj(this, pfmtin->plsdnTop);

    if(!pdobj)
    {
        lserr = lserrOutOfMemory;
        goto Cleanup;
    }

    // pLayout is the guy we're being asked to format here.
    Assert(pLayout && pLayout!=pFlowLayout);

    pElementLayout  = pLayout->ElementOwner();
    pNodeLayout     = pElementLayout->GetFirstBranch();
    pCF             = pNodeLayout->GetCharFormat();
    pFF             = pNodeLayout->GetFancyFormat();
    bPositionType   = pNodeLayout->GetCascadedposition();

    // for overlapping layouts curtail the range of characters measured
    cchSite = pLS->GetNestedElementCch(pElementLayout);

    ZeroMemory(&objdim, sizeof(OBJDIM));

    // Let's see if this an 'ownline' thingy.  Note that even if the element
    // is not by default and 'ownline' element, we may have morphed it into
    // one -- then too it has to be a block element. If it is not one (like
    // a span, then it will not live on its own line).  Check here.
    fOwnLine = pLS->IsOwnLineSite(plsrun);

    Assert(pElementLayout->IsInlinedElement());

    // Certain sites that only Microsoft supports can break with any
    // characters, so we hack that in right here.
    // BUGBUG (cthrash) This is goofy.  We should have a better way to
    // determine this than checking tag types.
    pdobj->_fIsBreakingSite= pElementLayout->Tag()==ETAG_OBJECT
        || pElementLayout->Tag()==ETAG_MARQUEE
        // This is really unfortunate -- if a site is percent sized then it becomes a breaking
        // site inside table cells. This is primarily for IE4x compat. See IE bug 42336 (SujalP)
        || pFF->_cuvWidth.GetUnitType()==CUnitValue::UNIT_PERCENT
        // One last thing - if we have a morphed non-ownline element inside
        // a table, it's considered a breaking site.
        || (!fOwnLine && !pElementLayout->_fSite);

    // If it's on its own line, and not first on line, FetchRun should have
    // terminated the line before we got here.
    // Assert( !( fOwnLine && !pfmtin->lsfgi.fFirstOnLine) );
    pFlowLayout->GetSiteWidth(pLayout, pLS->_pci,
        pLS->_lsMode==CLineServices::LSMODE_MEASURER,
        pLS->_xWrappingWidth,
        &xWidth, &yHeight, &xMinWidth);

    // v-Dimension computed in VerticalAlignObjects
    // BUGBUG (cthrash) We have rounding errors in LS; don't pass zero
    objdim.heightsRef.dvAscent = 1;
    objdim.heightsRef.dvDescent = 0;
    objdim.heightsRef.dvMultiLineHeight = 1;
    if(_pLS->_fMinMaxPass)
    {
        objdim.heightsPres = objdim.heightsRef;
    }

    if(pLS->_fIsRuby && !pLS->_fIsRubyText)
    {
        pLS->_yMaxHeightForRubyBase = max(pLS->_yMaxHeightForRubyBase, yHeight);
    }

    // We need to store two widths in the dobj: The width corresponding to
    // the wrapping width (urColumnMax) and the minimum width.  LsGetMinDur,
    // however, does not recognize two widths for ILS objects.  We therefore
    // cache the difference, and account for these in an enumeration callback
    // after the LsGetMinDur pass.
    if(!pLS->_fMinMaxPass)
    {
        pdobj->_dvMinMaxDelta = 0;
        objdim.dur = xWidth;
    }
    else
    {
        pdobj->_dvMinMaxDelta = xWidth - xMinWidth;
        objdim.dur = xMinWidth;
    }

    if(pCF->HasCharGrid(TRUE))
    {
        long lCharGridSize = pLS->GetCharGridSize();
        pdobj->_dvMinMaxDelta = pLS->GetClosestGridMultiple(lCharGridSize, pdobj->_dvMinMaxDelta);
        objdim.dur = pLS->GetClosestGridMultiple(lCharGridSize, objdim.dur);
    }

    if(fOwnLine)
    {
        // If we are inside a something like say a PRE then too we do
        // not terminate, because if there was a \r right after the ownline site
        // then we will allow that \r to break the line. We do not check if the
        // subsequent char is a \r because there might be goop(comments, hidden
        // stuff etc etc) between this site and the \r. Hence here we just march
        // forward and if we run into text or layout later on we will terminate
        // the line then. This way we will eat up the goop if any in between.
        if(!pLS->_fScanForCR)
        {
            COneRun* porOut;
            COneRun* por = pLS->_listFree.GetFreeOneRun(plsrun);

            if(!por)
            {
                lserr = lserrOutOfMemory;
                goto Cleanup;
            }

            Assert(plsrun->IsNormalRun());
            Assert(plsrun->_lscch == plsrun->_lscchOriginal);
            por->_lscpBase += plsrun->_lscch;

            // If this object has to be on its own line, then it clearly
            // ends the current line.
            lserr = pLS->TerminateLine(por, CLineServices::TL_ADDEOS, &porOut);
            if(lserr != lserrNone)
            {
                goto Cleanup;
            }

            // Free the one run
            pLS->_listFree.SpliceIn(por);
        }
        else
        {
            // Flip this bit so that we will setup pfmtres properly later on
            fOwnLine = FALSE;
        }

        // If we have an 'ownline' site, by definition this is a breaking
        // site, meaning we can (or more precisely should) break on either
        // side of the site.
        pdobj->_fIsBreakingSite = TRUE;

        // NOTE(SujalP): Bug 65906.
        // We originally used to set ourselves up to collect after space only
        // for morphed elements. As it turns out, we want to collect after space
        // from margins of _all_ ownline sites (including morphed elements),
        // because margins for ownline-sites are not accounted for in
        // VerticalAlignObjects (see CLayout::GetMarginInfo for more details --
        // it returns 0 for ownline sites).
        pLS->_pNodeForAfterSpace = pNodeLayout;

        // All ownline sites have their x position to be 0
        if(pElementLayout->HasFlag(TAGDESC_OWNLINE))
        {
            pLayout->SetXProposed(0);
        }
    }

    if(fOwnLine)
    {
        *pfmtres = fmtrCompletedRun;
    }
    else
    {
        const long urWrappingWidth = max(pfmtin->lsfgi.urColumnMax, pLS->_xWrappingWidth);

        *pfmtres = (pfmtin->lsfgi.fFirstOnLine ||
            pfmtin->lsfgi.urPen+objdim.dur<=urWrappingWidth)?fmtrCompletedRun:fmtrExceededMargin;
    }

    // This is an accessor to the dnode, telling LS to set the dnode pointing
    // to our dobj.
    lserr = LsdnFinishRegular(pLS->_plsc, cchSite, pfmtin->lsfrun.plsrun,
        pfmtin->lsfrun.plschp, (struct dobj*)pdobj, &objdim);

Cleanup:
    return lserr;
}