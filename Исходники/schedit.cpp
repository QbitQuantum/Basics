void SCH_EDIT_FRAME::OnRotate( wxCommandEvent& aEvent )
{
    SCH_SCREEN* screen = GetScreen();
    SCH_ITEM*   item = screen->GetCurItem();

    INSTALL_UNBUFFERED_DC( dc, m_canvas );

    // Allows block rotate operation on hot key.
    if( screen->m_BlockLocate.GetState() != STATE_NO_BLOCK )
    {
        screen->m_BlockLocate.SetCommand( BLOCK_ROTATE );
        HandleBlockEnd( &dc );
        return;
    }

    if( item == NULL )
    {
        // If we didn't get here by a hot key, then something has gone wrong.
        if( aEvent.GetInt() == 0 )
            return;

        EDA_HOTKEY_CLIENT_DATA* data = (EDA_HOTKEY_CLIENT_DATA*) aEvent.GetClientObject();

        wxCHECK_RET( data != NULL, wxT( "Invalid hot key client object." ) );

        item = LocateAndShowItem( data->GetPosition(), SCH_COLLECTOR::RotatableItems,
                                  aEvent.GetInt() );

        // Exit if no item found at the current location or the item is already being edited.
        if( (item == NULL) || (item->GetFlags() != 0) )
            return;
    }

    switch( item->Type() )
    {
    case SCH_COMPONENT_T:
        {
            SCH_COMPONENT* component = static_cast<SCH_COMPONENT*>( item );
            if( aEvent.GetId() == ID_SCH_ROTATE_CLOCKWISE )
                OrientComponent( CMP_ROTATE_CLOCKWISE );
            else if( aEvent.GetId() == ID_SCH_ROTATE_COUNTERCLOCKWISE )
                OrientComponent( CMP_ROTATE_COUNTERCLOCKWISE );
            else
                wxFAIL_MSG( wxT( "Unknown rotate item command ID." ) );

            if( m_autoplaceFields )
                component->AutoAutoplaceFields( GetScreen() );

            m_canvas->Refresh();

            break;
        }

    case SCH_TEXT_T:
    case SCH_LABEL_T:
    case SCH_GLOBAL_LABEL_T:
    case SCH_HIERARCHICAL_LABEL_T:
        m_canvas->MoveCursorToCrossHair();
        ChangeTextOrient( (SCH_TEXT*) item );
        m_canvas->Refresh();
        break;

    case SCH_FIELD_T:
        m_canvas->MoveCursorToCrossHair();
        RotateField( (SCH_FIELD*) item );
        if( item->GetParent()->Type() == SCH_COMPONENT_T )
        {
            // Now that we're moving a field, they're no longer autoplaced.
            SCH_COMPONENT *parent = static_cast<SCH_COMPONENT*>( item->GetParent() );
            parent->ClearFieldsAutoplaced();
        }
        m_canvas->Refresh();
        break;

    case SCH_BITMAP_T:
        RotateImage( (SCH_BITMAP*) item );
        break;

    case SCH_SHEET_T:
        if( !item->IsNew() )    // rotate a sheet during its creation has no sense
        {
            bool retCCW = ( aEvent.GetId() == ID_SCH_ROTATE_COUNTERCLOCKWISE );
            RotateHierarchicalSheet( static_cast<SCH_SHEET*>( item ), retCCW );
        }

        break;

    case SCH_JUNCTION_T:
    case SCH_NO_CONNECT_T:
        // these items are not rotated, because rotation does not change them.
        break;

    default:
        // Other items (wires...) cannot be rotated, at least during creation
        if( item->IsNew() )
            break;

        wxFAIL_MSG( wxString::Format( wxT( "Cannot rotate schematic item type %s." ),
                                      GetChars( item->GetClass() ) ) );
    }

    if( item->GetFlags() == 0 )
        screen->SetCurItem( NULL );
}