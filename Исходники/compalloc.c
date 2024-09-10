/*
 * Redirect one window for one client
 */
int
compRedirectWindow (ClientPtr pClient, WindowPtr pWin, int update)
{
    CompWindowPtr	cw = GetCompWindow (pWin);
    CompClientWindowPtr	ccw;
    CompScreenPtr       cs = GetCompScreen(pWin->drawable.pScreen);
    WindowPtr		pLayerWin;
    Bool		anyMarked = FALSE;
    
    if (pWin == cs->pOverlayWin) {
	return Success;
    }

    if (!pWin->parent)
	return BadMatch;

    /*
     * Only one Manual update is allowed
     */
    if (cw && update == CompositeRedirectManual)
	for (ccw = cw->clients; ccw; ccw = ccw->next)
	    if (ccw->update == CompositeRedirectManual)
		return BadAccess;
    
    /*
     * Allocate per-client per-window structure 
     * The client *could* allocate multiple, but while supported,
     * it is not expected to be common
     */
    ccw = malloc(sizeof (CompClientWindowRec));
    if (!ccw)
	return BadAlloc;
    ccw->id = FakeClientID (pClient->index);
    ccw->update = update;
    /*
     * Now make sure there's a per-window structure to hang this from
     */
    if (!cw)
    {
	cw = malloc(sizeof (CompWindowRec));
	if (!cw)
	{
	    free(ccw);
	    return BadAlloc;
	}
	cw->damage = DamageCreate (compReportDamage,
				   compDestroyDamage,
				   DamageReportNonEmpty,
				   FALSE,
				   pWin->drawable.pScreen,
				   pWin);
	if (!cw->damage)
	{
	    free(ccw);
	    free(cw);
	    return BadAlloc;
	}

	anyMarked = compMarkWindows (pWin, &pLayerWin);

	/* Make sure our borderClip is correct for ValidateTree */
	RegionNull(&cw->borderClip);
	RegionCopy(&cw->borderClip, &pWin->borderClip);
	cw->borderClipX = pWin->drawable.x;
	cw->borderClipY = pWin->drawable.y;
	cw->update = CompositeRedirectAutomatic;
	cw->clients = 0;
	cw->oldx = COMP_ORIGIN_INVALID;
	cw->oldy = COMP_ORIGIN_INVALID;
	cw->damageRegistered = FALSE;
	cw->damaged = FALSE;
	cw->pOldPixmap = NullPixmap;
	dixSetPrivate(&pWin->devPrivates, CompWindowPrivateKey, cw);
    }
    ccw->next = cw->clients;
    cw->clients = ccw;
    if (!AddResource (ccw->id, CompositeClientWindowType, pWin))
	return BadAlloc;
    if (ccw->update == CompositeRedirectManual)
    {
	if (!anyMarked)
	    anyMarked = compMarkWindows (pWin, &pLayerWin);

	if (cw->damageRegistered)
	{
	    DamageUnregister (&pWin->drawable, cw->damage);
	    cw->damageRegistered = FALSE;
	}
	cw->update = CompositeRedirectManual;
    }
    else if (cw->update == CompositeRedirectAutomatic && !cw->damageRegistered) {
	if (!anyMarked)
	    anyMarked = compMarkWindows (pWin, &pLayerWin);
    }

    if (!compCheckRedirect (pWin))
    {
	FreeResource (ccw->id, RT_NONE);
	return BadAlloc;
    }

    if (anyMarked)
	compHandleMarkedWindows (pWin, pLayerWin);
    
    return Success;
}