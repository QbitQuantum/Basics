SCH_COMPONENT* SCH_EDIT_FRAME::Load_Component( wxDC*                          aDC,
                                               const SCHLIB_FILTER*           aFilter,
                                               SCH_BASE_FRAME::HISTORY_LIST&  aHistoryList,
                                               bool                           aUseLibBrowser )
{
    wxString msg;

    SetRepeatItem( NULL );
    m_canvas->SetIgnoreMouseEvents( true );

    auto sel = SelectComponentFromLibrary( aFilter, aHistoryList, aUseLibBrowser, 1, 1,
                                           m_footprintPreview );

    if( !sel.LibId.IsValid() )
    {
        m_canvas->SetIgnoreMouseEvents( false );
        m_canvas->MoveCursorToCrossHair();
        return NULL;
    }

    m_canvas->SetIgnoreMouseEvents( false );
    m_canvas->MoveCursorToCrossHair();

    wxString libsource;     // the library name to use. If empty, load from any lib

    if( aFilter )
        libsource = aFilter->GetLibSource();

    LIB_ID libId = sel.LibId;

    LIB_PART* part = GetLibPart( libId, true );

    if( !part )
        return NULL;

    SCH_COMPONENT* component = new SCH_COMPONENT( *part, m_CurrentSheet, sel.Unit, sel.Convert,
                                                  GetCrossHairPosition(), true );

    // Set the m_ChipName value, from component name in lib, for aliases
    // Note if part is found, and if name is an alias of a component,
    // alias exists because its root component was found
    component->SetLibId( libId );

    // Be sure the link to the corresponding LIB_PART is OK:
    component->Resolve( *Prj().SchSymbolLibTable() );

    // Set any fields that have been modified
    for( auto const& i : sel.Fields )
    {
        auto field = component->GetField( i.first );

        if( field )
            field->SetText( i.second );
    }

    // Set the component value that can differ from component name in lib, for aliases
    component->GetField( VALUE )->SetText( sel.LibId.GetLibItemName() );

    // If there is no field defined in the component, copy one over from the library
    // ( from the .dcm file )
    // This way the Datasheet field will not be empty and can be changed from the schematic
    if( component->GetField( DATASHEET )->GetText().IsEmpty() )
    {
        LIB_ALIAS* entry = GetLibAlias( component->GetLibId(), true, true );

        if( entry && !!entry->GetDocFileName() )
            component->GetField( DATASHEET )->SetText( entry->GetDocFileName() );
    }

    MSG_PANEL_ITEMS items;

    component->SetCurrentSheetPath( &GetCurrentSheet() );
    component->GetMsgPanelInfo( items );

    SetMsgPanel( items );
    component->Draw( m_canvas, aDC, wxPoint( 0, 0 ), g_XorMode );
    component->SetFlags( IS_NEW );

    if( m_autoplaceFields )
        component->AutoplaceFields( /* aScreen */ NULL, /* aManual */ false );

    PrepareMoveItem( (SCH_ITEM*) component, aDC );

    return component;
}