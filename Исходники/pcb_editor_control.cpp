int PCB_EDITOR_CONTROL::ZoneMerge( const TOOL_EVENT& aEvent )
{
    SELECTION selection = m_toolMgr->GetTool<SELECTION_TOOL>()->GetSelection();
    BOARD* board = getModel<BOARD>();
    RN_DATA* ratsnest = board->GetRatsnest();
    KIGFX::VIEW* view = getView();

    if( selection.Size() < 2 )
        return 0;

    PICKED_ITEMS_LIST changes;
    int netcode = -1;

    // Loop through all combinations
    for( int ia1 = 0; ia1 < selection.Size() - 1; ++ia1 )
    {
        ZONE_CONTAINER* curr_area = dynamic_cast<ZONE_CONTAINER*>( selection.Item<EDA_ITEM>( ia1 ) );

        if( !curr_area )
            continue;

        netcode = curr_area->GetNetCode();

        EDA_RECT b1 = curr_area->Outline()->GetBoundingBox();
        bool mod_ia1 = false;

        for( int ia2 = selection.Size() - 1; ia2 > ia1; --ia2 )
        {
            ZONE_CONTAINER* area2 = dynamic_cast<ZONE_CONTAINER*>( selection.Item<EDA_ITEM>( ia2 ) );

            if( !area2 )
                continue;

            if( area2->GetNetCode() != netcode )
                continue;

            if( curr_area->GetPriority() != area2->GetPriority() )
                continue;

            if( curr_area->GetIsKeepout() != area2->GetIsKeepout() )
                continue;

            if( curr_area->GetLayer() != area2->GetLayer() )
                continue;

            EDA_RECT b2 = area2->Outline()->GetBoundingBox();

            if( b1.Intersects( b2 ) )
            {
                EDA_ITEM* backup = curr_area->Clone();
                bool ret = board->TestAreaIntersection( curr_area, area2 );

                if( ret && board->CombineAreas( &changes, curr_area, area2 ) )
                {
                    mod_ia1 = true;
                    selection.items.RemovePicker( ia2 );

                    ITEM_PICKER picker( curr_area, UR_CHANGED );
                    picker.SetLink( backup );
                    changes.PushItem( picker );
                }
                else
                {
                    delete backup;
                }
            }
        }

        if( mod_ia1 )
            --ia1;     // if modified, we need to check it again
    }

    m_toolMgr->RunAction( COMMON_ACTIONS::selectionClear, true );
    m_frame->SaveCopyInUndoList( changes, UR_UNSPECIFIED );

    for( unsigned i = 0; i < changes.GetCount(); ++i )
    {
        ITEM_PICKER picker = changes.GetItemWrapper( i );
        BOARD_ITEM* item = static_cast<BOARD_ITEM*>( picker.GetItem() );

        if( picker.GetStatus() == UR_DELETED )
        {
            view->Remove( item );
            ratsnest->Remove( item );
        }
        else if( picker.GetStatus() == UR_CHANGED )
        {
            item->ViewUpdate( KIGFX::VIEW_ITEM::ALL );
            m_toolMgr->RunAction( COMMON_ACTIONS::selectItem, true, item );
        }
    }

    return 0;
}