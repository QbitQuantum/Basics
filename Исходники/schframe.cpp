void SCH_EDIT_FRAME::addCurrentItemToList( wxDC* aDC )
{
    SCH_SCREEN* screen = GetScreen();
    SCH_ITEM*   item = screen->GetCurItem();

    wxCHECK_RET( item != NULL, wxT( "Cannot add current item to list." ) );

    m_canvas->SetAutoPanRequest( false );

    SCH_ITEM* undoItem = item;

    if( item->Type() == SCH_SHEET_PIN_T )
    {
        SCH_SHEET* sheet = (SCH_SHEET*) item->GetParent();

        wxCHECK_RET( (sheet != NULL) && (sheet->Type() == SCH_SHEET_T),
                     wxT( "Cannot place sheet pin in invalid schematic sheet object." ) );

        undoItem = sheet;
    }

    else if( item->Type() == SCH_FIELD_T )
    {
        SCH_COMPONENT* cmp = (SCH_COMPONENT*) item->GetParent();

        wxCHECK_RET( (cmp != NULL) && (cmp->Type() == SCH_COMPONENT_T),
                     wxT( "Cannot place field in invalid schematic component object." ) );

        undoItem = cmp;
    }

    if( item->IsNew() )
    {
        if( item->Type() == SCH_SHEET_T )
        {
            // Fix the size and position of the new sheet using the last values set by
            // the m_mouseCaptureCallback function.
            m_canvas->SetMouseCapture( NULL, NULL );

            if( !EditSheet( (SCH_SHEET*)item, aDC ) )
            {
                screen->SetCurItem( NULL );
                item->Draw( m_canvas, aDC, wxPoint( 0, 0 ), g_XorMode );
                delete item;
                return;
            }

            SetSheetNumberAndCount();
        }

        if( undoItem == item )
        {
            if( !screen->CheckIfOnDrawList( item ) )  // don't want a loop!
                screen->Append( item );

            SetRepeatItem( item );

            SaveCopyInUndoList( undoItem, UR_NEW );
        }
        else
        {
            // Here, item is not a basic schematic item, but an item inside
            // a parent basic schematic item,
            // currently: sheet pin or component field.
            // currently, only a sheet pin can be found as new item,
            // because new component fields have a specific handling, and do not appears here
            SaveCopyInUndoList( undoItem, UR_CHANGED );

            if( item->Type() == SCH_SHEET_PIN_T )
                ( (SCH_SHEET*)undoItem )->AddPin( (SCH_SHEET_PIN*) item );
            else
                wxLogMessage(wxT( "addCurrentItemToList: expected type = SCH_SHEET_PIN_T, actual type = %d" ),
                            item->Type() );
        }
    }
    else
    {
        SaveUndoItemInUndoList( undoItem );
    }

    // Erase the wire representation before the 'normal' view is drawn.
    if ( item->IsWireImage() )
        item->Draw( m_canvas, aDC, wxPoint( 0, 0 ), g_XorMode );

    item->ClearFlags();
    screen->SetModify();
    screen->SetCurItem( NULL );
    m_canvas->SetMouseCapture( NULL, NULL );
    m_canvas->EndMouseCapture();

    if( item->IsConnectable() )
        screen->TestDanglingEnds();

    if( aDC )
    {
        EDA_CROSS_HAIR_MANAGER( m_canvas, aDC );  // Erase schematic cursor
        undoItem->Draw( m_canvas, aDC, wxPoint( 0, 0 ), GR_DEFAULT_DRAWMODE );
    }
}