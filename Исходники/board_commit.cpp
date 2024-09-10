void BOARD_COMMIT::Revert()
{
    PICKED_ITEMS_LIST undoList;
    KIGFX::VIEW* view = m_toolMgr->GetView();
    BOARD* board = (BOARD*) m_toolMgr->GetModel();
    RN_DATA* ratsnest = board->GetRatsnest();

    for( auto it = m_changes.rbegin(); it != m_changes.rend(); ++it )
    {
        COMMIT_LINE& ent = *it;
        BOARD_ITEM* item = static_cast<BOARD_ITEM*>( ent.m_item );
        BOARD_ITEM* copy = static_cast<BOARD_ITEM*>( ent.m_copy );

        switch( ent.m_type )
        {
        case CHT_ADD:
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* oldModule = static_cast<MODULE*>( item );
                oldModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
            }

            view->Remove( item );
            ratsnest->Remove( item );
            break;

        case CHT_REMOVE:
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* newModule = static_cast<MODULE*>( item );
                newModule->RunOnChildren( boost::bind( &EDA_ITEM::ClearFlags, _1, SELECTED ) );
                newModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
            }

            view->Add( item );
            ratsnest->Add( item );
            break;

        case CHT_MODIFY:
        {
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* oldModule = static_cast<MODULE*>( item );
                oldModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
            }

            view->Remove( item );
            ratsnest->Remove( item );

            item->SwapData( copy );

            item->ClearFlags( SELECTED );

            // Update all pads/drawings/texts, as they become invalid
            // for the VIEW after SwapData() called for modules
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* newModule = static_cast<MODULE*>( item );
                newModule->RunOnChildren( boost::bind( &EDA_ITEM::ClearFlags, _1, SELECTED ) );
                newModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
            }

            view->Add( item );
            ratsnest->Add( item );
            delete copy;
            break;
        }

        default:
            assert( false );
            break;
        }
    }

    ratsnest->Recalculate();

    clear();
}