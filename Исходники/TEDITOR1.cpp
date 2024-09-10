TEditor::TEditor( const TRect& bounds,
                  TScrollBar *aHScrollBar,
                  TScrollBar *aVScrollBar,
                  TIndicator *aIndicator,
                  size_t aBufSize ) :
    TView( bounds ),
    hScrollBar( aHScrollBar ),
    vScrollBar( aVScrollBar ),
    indicator( aIndicator ),
    bufSize( aBufSize ),
    canUndo( True ),
    selecting( False ),
    overwrite( False ),
    autoIndent( False ) ,
    lockCount( 0 ),
    keyState( 0 )
{
    growMode = gfGrowHiX | gfGrowHiY;
    options |= ofSelectable;
    eventMask = evMouseDown | evKeyDown | evCommand | evBroadcast;
    showCursor();
    initBuffer();
    if( buffer != 0 )
        isValid = True;
    else
    {
        editorDialog( edOutOfMemory );
        bufSize = 0;
        isValid = False;
    }
    setBufLen(0);
}