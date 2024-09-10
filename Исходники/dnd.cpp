wxDragResult wxDropSource::DoDragDrop(int flags)
{
    wxASSERT_MSG( m_data, wxT("Drop source: no data") );

    if ((m_data == NULL) || (m_data->GetFormatCount() == 0))
        return (wxDragResult)wxDragNone;

    DragReference theDrag;
    RgnHandle dragRegion;
    OSStatus err = noErr;
    PasteboardRef   pasteboard;

    // add data to drag

    err = PasteboardCreate( kPasteboardUniqueName, &pasteboard );
    if ( err != noErr )
        return wxDragNone;

    // we add a dummy promise keeper because of strange messages when linking against carbon debug
    err = PasteboardSetPromiseKeeper( pasteboard, wxMacPromiseKeeper, this );
    if ( err != noErr )
    {
        CFRelease( pasteboard );
        return wxDragNone;
    }

    err = PasteboardClear( pasteboard );
    if ( err != noErr )
    {
        CFRelease( pasteboard );
        return wxDragNone;
    }
    PasteboardSynchronize( pasteboard );

    m_data->AddToPasteboard( pasteboard, 1 );

    if (NewDragWithPasteboard( pasteboard , &theDrag) != noErr)
    {
        CFRelease( pasteboard );
        return wxDragNone;
    }

    dragRegion = NewRgn();
    RgnHandle tempRgn = NewRgn();

    EventRecord rec;
    ConvertEventRefToEventRecord(  (EventRef) wxTheApp->MacGetCurrentEvent(), &rec );

    const short dragRegionOuterBoundary = 10;
    const short dragRegionInnerBoundary = 9;

    SetRectRgn(
        dragRegion,
        rec.where.h - dragRegionOuterBoundary,
        rec.where.v  - dragRegionOuterBoundary,
        rec.where.h + dragRegionOuterBoundary,
        rec.where.v + dragRegionOuterBoundary );

    SetRectRgn(
        tempRgn,
        rec.where.h - dragRegionInnerBoundary,
        rec.where.v - dragRegionInnerBoundary,
        rec.where.h + dragRegionInnerBoundary,
        rec.where.v + dragRegionInnerBoundary );

    DiffRgn( dragRegion, tempRgn, dragRegion );
    DisposeRgn( tempRgn );

    // TODO: work with promises in order to return data
    // only when drag was successfully completed

    gTrackingGlobals.m_currentSource = this;
    gTrackingGlobals.m_result = wxDragNone;
    gTrackingGlobals.m_flags = flags;

    err = TrackDrag( theDrag, &rec, dragRegion );

    DisposeRgn( dragRegion );
    DisposeDrag( theDrag );
    CFRelease( pasteboard );
    gTrackingGlobals.m_currentSource = NULL;

    return gTrackingGlobals.m_result;
}