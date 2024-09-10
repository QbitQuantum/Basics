void PCB_EDIT_FRAME::PutDataInPreviousState( PICKED_ITEMS_LIST* aList, bool aRedoCommand,
                                             bool aRebuildRatsnet )
{
    BOARD_ITEM* item;
    bool        not_found = false;
    bool        reBuild_ratsnest = false;
    KIGFX::VIEW* view = GetGalCanvas()->GetView();
    RN_DATA* ratsnest = GetBoard()->GetRatsnest();

    // Undo in the reverse order of list creation: (this can allow stacked changes
    // like the same item can be changes and deleted in the same complex command

    bool build_item_list = true;    // if true the list of existing items must be rebuilt

    for( int ii = aList->GetCount() - 1; ii >= 0 ; ii-- )
    {
        item = (BOARD_ITEM*) aList->GetPickedItem( ii );
        wxASSERT( item );

        /* Test for existence of item on board.
         * It could be deleted, and no more on board:
         *   - if a call to SaveCopyInUndoList was forgotten in Pcbnew
         *   - in zones outlines, when a change in one zone merges this zone with an other
         * This test avoids a Pcbnew crash
         * Obviously, this test is not made for deleted items
         */
        UNDO_REDO_T status = aList->GetPickedItemStatus( ii );

        if( status != UR_DELETED )
        {
            if( build_item_list )
                // Build list of existing items, for integrity test
                TestForExistingItem( GetBoard(), NULL );

            build_item_list = false;

            if( !TestForExistingItem( GetBoard(), item ) )
            {
                // Remove this non existent item
                aList->RemovePicker( ii );
                ii++;       // the current item was removed, ii points now the next item
                            // decrement it because it will be incremented later
                not_found = true;
                continue;
            }
        }

        item->ClearFlags();

        // see if we must rebuild ratsnets and pointers lists
        switch( item->Type() )
        {
        case PCB_MODULE_T:
        case PCB_ZONE_AREA_T:
        case PCB_TRACE_T:
        case PCB_VIA_T:
            reBuild_ratsnest = true;
            break;

        default:
            break;
        }

        switch( aList->GetPickedItemStatus( ii ) )
        {
        case UR_CHANGED:    /* Exchange old and new data for each item */
        {
            BOARD_ITEM* image = (BOARD_ITEM*) aList->GetPickedItemLink( ii );

            // Remove all pads/drawings/texts, as they become invalid
            // for the VIEW after SwapData() called for modules
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* oldModule = static_cast<MODULE*>( item );
                oldModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
            }
            ratsnest->Remove( item );

            item->SwapData( image );

            // Update all pads/drawings/texts, as they become invalid
            // for the VIEW after SwapData() called for modules
            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* newModule = static_cast<MODULE*>( item );
                newModule->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
            }
            ratsnest->Add( item );

            item->ClearFlags( SELECTED );
            item->ViewUpdate( KIGFX::VIEW_ITEM::LAYERS );
        }
        break;

        case UR_NEW:        /* new items are deleted */
            aList->SetPickedItemStatus( UR_DELETED, ii );
            GetBoard()->Remove( item );

            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* module = static_cast<MODULE*>( item );
                module->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
            }
            view->Remove( item );

            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            break;

        case UR_DELETED:    /* deleted items are put in List, as new items */
            aList->SetPickedItemStatus( UR_NEW, ii );
            GetBoard()->Add( item );

            if( item->Type() == PCB_MODULE_T )
            {
                MODULE* module = static_cast<MODULE*>( item );
                module->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1) );
            }
            view->Add( item );

            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            build_item_list = true;
            break;

        case UR_MOVED:
            item->Move( aRedoCommand ? aList->m_TransformPoint : -aList->m_TransformPoint );
            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            ratsnest->Update( item );
            break;

        case UR_ROTATED:
            item->Rotate( aList->m_TransformPoint,
                          aRedoCommand ? m_rotationAngle : -m_rotationAngle );
            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            ratsnest->Update( item );
            break;

        case UR_ROTATED_CLOCKWISE:
            item->Rotate( aList->m_TransformPoint,
                          aRedoCommand ? -m_rotationAngle : m_rotationAngle );
            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            ratsnest->Update( item );
            break;

        case UR_FLIPPED:
            item->Flip( aList->m_TransformPoint );
            item->ViewUpdate( KIGFX::VIEW_ITEM::LAYERS );
            ratsnest->Update( item );
            break;

        default:
        {
            wxString msg;
            msg.Printf( wxT( "PutDataInPreviousState() error (unknown code %X)" ),
                        aList->GetPickedItemStatus( ii ) );
            wxMessageBox( msg );
        }
        break;
        }
    }

    if( not_found )
        wxMessageBox( wxT( "Incomplete undo/redo operation: some items not found" ) );

    // Rebuild pointers and ratsnest that can be changed.
    if( reBuild_ratsnest && aRebuildRatsnet )
    {
        if( IsGalCanvasActive() )
            ratsnest->Recalculate();
        else
            Compile_Ratsnest( NULL, true );
    }
}