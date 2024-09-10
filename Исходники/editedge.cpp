void PCB_EDIT_FRAME::Delete_Drawings_All_Layer( LAYER_ID aLayer )
{
    if( IsCopperLayer( aLayer ) )
    {
        DisplayError( this, _( "Copper layer global delete not allowed!" ) );
        return;
    }

    wxString msg = wxString::Format(
        _( "Delete everything on layer %s?" ),
        GetChars( GetBoard()->GetLayerName( aLayer ) ) );

    if( !IsOK( this, msg ) )
        return;

    PICKED_ITEMS_LIST   pickList;
    ITEM_PICKER         picker( NULL, UR_DELETED );
    BOARD_ITEM*         PtNext;

    for( BOARD_ITEM* item = GetBoard()->m_Drawings;  item;  item = PtNext )
    {
        PtNext = item->Next();

        switch( item->Type() )
        {
        case PCB_LINE_T:
        case PCB_TEXT_T:
        case PCB_DIMENSION_T:
        case PCB_TARGET_T:
            if( item->GetLayer() == aLayer )
            {
                item->UnLink();
                picker.SetItem( item );
                pickList.PushItem( picker );
            }

            break;

        default:
        {
            wxString msg;
            msg.Printf( wxT("Delete_Drawings_All_Layer() error: unknown type %d"),
                        item->Type() );
            wxMessageBox( msg );
            break;
        }
        }
    }

    if( pickList.GetCount() )
    {
        OnModify();
        SaveCopyInUndoList(pickList, UR_DELETED);
    }
}