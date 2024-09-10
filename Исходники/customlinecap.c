/* FIXME: Sometimes when fillPath is non-null and stroke path is null, the native
 * version of this function returns NotImplemented. I cannot figure out why. */
GpStatus WINGDIPAPI GdipCreateCustomLineCap(GpPath* fillPath, GpPath* strokePath,
    GpLineCap baseCap, REAL baseInset, GpCustomLineCap **customCap)
{
    GpPathData *pathdata;

    TRACE("%p %p %d %f %p\n", fillPath, strokePath, baseCap, baseInset, customCap);

    if(!customCap || !(fillPath || strokePath))
        return InvalidParameter;

    *customCap = GdipAlloc(sizeof(GpCustomLineCap));
    if(!*customCap)    return OutOfMemory;

    if(strokePath){
        (*customCap)->fill = FALSE;
        pathdata = &strokePath->pathdata;
    }
    else{
        (*customCap)->fill = TRUE;
        pathdata = &fillPath->pathdata;
    }

    (*customCap)->pathdata.Points = GdipAlloc(pathdata->Count * sizeof(PointF));
    (*customCap)->pathdata.Types = GdipAlloc(pathdata->Count);

    if((!(*customCap)->pathdata.Types || !(*customCap)->pathdata.Points) &&
        pathdata->Count){
        GdipFree((*customCap)->pathdata.Points);
        GdipFree((*customCap)->pathdata.Types);
        GdipFree(*customCap);
        return OutOfMemory;
    }

    memcpy((*customCap)->pathdata.Points, pathdata->Points, pathdata->Count
           * sizeof(PointF));
    memcpy((*customCap)->pathdata.Types, pathdata->Types, pathdata->Count);
    (*customCap)->pathdata.Count = pathdata->Count;

    (*customCap)->inset = baseInset;
    (*customCap)->cap = baseCap;
    (*customCap)->join = LineJoinMiter;
    (*customCap)->scale = 1.0;

    TRACE("<-- %p\n", *customCap);

    return Ok;
}