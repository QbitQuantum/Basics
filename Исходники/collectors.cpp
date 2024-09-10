// see collectors.h
void GENERAL_COLLECTOR::Collect( BOARD_ITEM* aItem, const KICAD_T aScanList[],
                                 const wxPoint& aRefPos, const COLLECTORS_GUIDE& aGuide )
{
    Empty();        // empty the collection, primary criteria list
    Empty2nd();     // empty the collection, secondary criteria list

    // remember guide, pass it to Inspect()
    SetGuide( &aGuide );

    SetScanTypes( aScanList );

    // remember where the snapshot was taken from and pass refPos to
    // the Inspect() function.
    SetRefPos( aRefPos );

    // visit the board or module with the INSPECTOR (me).
    aItem->Visit(   this,       // INSPECTOR* inspector
                    NULL,       // const void* testData, not used here
                    m_ScanTypes );

    SetTimeNow();               // when snapshot was taken

    // record the length of the primary list before concatonating on to it.
    m_PrimaryLength = m_List.size();

    // append 2nd list onto end of the first list
    for( unsigned i = 0;  i<m_List2nd.size();  ++i )
        Append( m_List2nd[i] );

    Empty2nd();
}