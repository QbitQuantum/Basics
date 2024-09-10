SCH_ITEM* SCH_EDIT_FRAME::LocateAndShowItem( const wxPoint& aPosition, const KICAD_T aFilterList[],
                                             int aHotKeyCommandId )
{
    SCH_ITEM*      item;
    wxString       msg;
    LIB_PIN*       Pin     = NULL;
    SCH_COMPONENT* LibItem = NULL;
    wxPoint        gridPosition = GetNearestGridPosition( aPosition );

    // Check the on grid position first.  There is more likely to be multiple items on
    // grid than off grid.
    item = LocateItem( gridPosition, aFilterList, aHotKeyCommandId );

    // If the user aborted the clarification context menu, don't show it again at the
    // off grid position.
    if( !item && m_canvas->GetAbortRequest() )
    {
        m_canvas->SetAbortRequest( false );
        return NULL;
    }

    if( !item && (aPosition != gridPosition) )
        item = LocateItem( aPosition, aFilterList, aHotKeyCommandId );

    if( !item )
    {
        m_canvas->SetAbortRequest( false );  // Just in case the user aborted the context menu.
        return NULL;
    }

    // Cross probing to Pcbnew if a pin or a component is found
    switch( item->Type() )
    {
    case SCH_FIELD_T:
    case LIB_FIELD_T:
        LibItem = (SCH_COMPONENT*) item->GetParent();
        SendMessageToPCBNEW( item, LibItem );
        break;

    case SCH_COMPONENT_T:
        LibItem = (SCH_COMPONENT*) item;
        SendMessageToPCBNEW( item, LibItem );
        break;

    case LIB_PIN_T:
        Pin = (LIB_PIN*) item;
        LibItem = (SCH_COMPONENT*) LocateItem( aPosition, SCH_COLLECTOR::ComponentsOnly );
        break;

    default:
        ;
    }

    if( Pin )
    {
        // Force display pin information (the previous display could be a component info)
        MSG_PANEL_ITEMS items;

        Pin->GetMsgPanelInfo( items );

        if( LibItem )
            items.push_back( MSG_PANEL_ITEM( LibItem->GetRef( m_CurrentSheet ),
                                             LibItem->GetField( VALUE )->GetShownText(), DARKCYAN ) );

        SetMsgPanel( items );

        // Cross probing:2 - pin found, and send a locate pin command to Pcbnew (highlight net)
        SendMessageToPCBNEW( Pin, LibItem );
    }

    return item;
}