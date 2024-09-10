NPError
NPP_Destroy(NPP inst, NPSavedData **saved)
{
    pdfmoz_t *moz = inst->pdata;
    int i;

    //MSG("NPP_Destroy");

    inst->pdata = NULL;

    DeleteObject(moz->graybrush);

    DestroyCursor(moz->arrow);
    DestroyCursor(moz->hand);
    DestroyCursor(moz->wait);

    fz_free(moz->dibinf);

    for (i = 0; i < moz->pagecount; i++)
    {
	if (moz->pages[i].obj)
	    fz_dropobj(moz->pages[i].obj);
	if (moz->pages[i].page)
	    pdf_droppage(moz->pages[i].page);
	if (moz->pages[i].image)
	    fz_droppixmap(moz->pages[i].image);
    }

    fz_free(moz->pages);

    if (moz->xref)
    {
	if (moz->xref->store)
	{
	    pdf_dropstore(moz->xref->store);
	    moz->xref->store = nil;
	}

	pdf_closexref(moz->xref);
    }

    fz_free(moz);

    return NPERR_NO_ERROR;
}