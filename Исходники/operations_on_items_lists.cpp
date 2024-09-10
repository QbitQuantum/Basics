void SCH_EDIT_FRAME::DeleteItem( SCH_ITEM* aItem, bool aAppend )
{
    wxCHECK_RET( aItem != NULL, wxT( "Cannot delete invalid item." ) );
    wxCHECK_RET( !( aItem->GetFlags() & STRUCT_DELETED ),
                 wxT( "Cannot delete item that is already deleted." ) );

    // Here, aItem is not null.
    SCH_SCREEN* screen = GetScreen();

    if( aItem->Type() == SCH_SHEET_PIN_T )
    {
        // This item is attached to a node, and is not accessible by the global list directly.
        SCH_SHEET* sheet = (SCH_SHEET*) aItem->GetParent();
        wxCHECK_RET( (sheet != NULL) && (sheet->Type() == SCH_SHEET_T),
                     wxT( "Sheet label has invalid parent item." ) );
        SaveCopyInUndoList( (SCH_ITEM*) sheet, UR_CHANGED, aAppend );
        sheet->RemovePin( (SCH_SHEET_PIN*) aItem );
        m_canvas->RefreshDrawingRect( sheet->GetBoundingBox() );
    }
    else
    {
        PICKED_ITEMS_LIST itemsList;
        ITEM_PICKER picker( aItem, UR_DELETED );

        aItem->SetFlags( STRUCT_DELETED );
        itemsList.PushItem( picker );
        screen->Remove( aItem );

        if( aItem->IsConnectable() && aItem->Type() != SCH_JUNCTION_T )
        {
            std::vector< wxPoint > pts;
            aItem->GetConnectionPoints( pts );
            for( auto point : pts )
            {
                SCH_ITEM* junction;
                if( !screen->IsJunctionNeeded( point )
                        && ( junction = screen->GetItem( point, 0, SCH_JUNCTION_T ) ) )
                {
                    ITEM_PICKER picker_juction( junction, UR_DELETED );
                    junction->SetFlags( STRUCT_DELETED );
                    itemsList.PushItem( picker_juction );
                    screen->Remove( junction );
                }
            }
        }

        SaveCopyInUndoList( itemsList, UR_DELETED, aAppend );
        m_canvas->RefreshDrawingRect( aItem->GetBoundingBox() );
    }
}