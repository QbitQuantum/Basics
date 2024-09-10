void DIALOG_GLOBAL_DELETION::AcceptPcbDelete( )
{
    bool gen_rastnest = false;

    m_Parent->SetCurItem( NULL );

    if( m_DelAlls->GetValue() )
    {
        m_Parent->Clear_Pcb( true );
    }
    else
    {
        if( !IsOK( this, _( "Are you sure you want to delete the selected items?" ) ) )
            return;

        BOARD*            pcb = m_Parent->GetBoard();
        PICKED_ITEMS_LIST pickersList;
        ITEM_PICKER       itemPicker( NULL, UR_DELETED );
        BOARD_ITEM*       item;
        BOARD_ITEM*       nextitem;
        RN_DATA*          ratsnest = pcb->GetRatsnest();

        LSET layers_filter = LSET().set();

        if( m_rbLayersOption->GetSelection() != 0 )     // Use current layer only
            layers_filter = LSET( ToLAYER_ID( m_currentLayer ) );

        if( m_DelZones->GetValue() )
        {
            int area_index = 0;
            item = pcb->GetArea( area_index );

            while( item )
            {
                if( layers_filter[item->GetLayer()] )
                {
                    itemPicker.SetItem( item );
                    pickersList.PushItem( itemPicker );
                    pcb->Remove( item );
                    item->ViewRelease();
                    ratsnest->Remove( item );
                    gen_rastnest = true;
                }
                else
                {
                    area_index++;
                }

                item = pcb->GetArea( area_index );
            }
        }

        if( m_DelDrawings->GetValue() || m_DelBoardEdges->GetValue() )
        {
            LSET masque_layer;

            if( m_DelDrawings->GetValue() )
                 masque_layer = LSET::AllNonCuMask().set( Edge_Cuts, false );

            if( m_DelBoardEdges->GetValue() )
                 masque_layer.set( Edge_Cuts );

            masque_layer &= layers_filter;

            for( item = pcb->m_Drawings; item; item = nextitem )
            {
                nextitem = item->Next();

                if( item->Type() == PCB_LINE_T  &&  masque_layer[item->GetLayer()] )
                {
                    itemPicker.SetItem( item );
                    pickersList.PushItem( itemPicker );
                    item->ViewRelease();
                    item->UnLink();
                }
            }
        }

        if( m_DelTexts->GetValue() )
        {
            LSET del_text_layers = layers_filter;

            for( item = pcb->m_Drawings; item; item = nextitem )
            {
                nextitem = item->Next();

                if( item->Type() == PCB_TEXT_T  &&  del_text_layers[item->GetLayer()] )
                {
                    itemPicker.SetItem( item );
                    pickersList.PushItem( itemPicker );
                    item->ViewRelease();
                    item->UnLink();
                }
            }
        }

        if( m_DelModules->GetValue() )
        {
            for( item = pcb->m_Modules; item; item = nextitem )
            {
                nextitem = item->Next();

                if( layers_filter[item->GetLayer()] &&
                    ( ( m_ModuleFilterNormal->GetValue() && !item->IsLocked() ) ||
                      ( m_ModuleFilterLocked->GetValue() && item->IsLocked() ) ) )
                {
                    itemPicker.SetItem( item );
                    pickersList.PushItem( itemPicker );
                    static_cast<MODULE*>( item )->RunOnChildren(
                            boost::bind( &KIGFX::VIEW_ITEM::ViewRelease, _1 ) );
                    ratsnest->Remove( item );
                    item->ViewRelease();
                    item->UnLink();
                    gen_rastnest = true;
                }
            }
        }

        if( m_DelTracks->GetValue() )
        {
            STATUS_FLAGS track_mask_filter = 0;

            if( !m_TrackFilterLocked->GetValue() )
                track_mask_filter |= TRACK_LOCKED;

            if( !m_TrackFilterAR->GetValue() )
                track_mask_filter |= TRACK_AR;

            TRACK* nexttrack;

            for( TRACK *track = pcb->m_Track; track; track = nexttrack )
            {
                nexttrack = track->Next();

                if( ( track->GetState( TRACK_LOCKED | TRACK_AR ) & track_mask_filter ) != 0 )
                    continue;

                if( ( track->GetState( TRACK_LOCKED | TRACK_AR ) == 0 ) &&
                    !m_TrackFilterNormal->GetValue() )
                    continue;

                if( ( track->Type() == PCB_VIA_T ) && !m_TrackFilterVias->GetValue() )
                    continue;

                if( ( track->GetLayerSet() & layers_filter ) == 0 )
                    continue;

                itemPicker.SetItem( track );
                pickersList.PushItem( itemPicker );
                track->ViewRelease();
                ratsnest->Remove( track );
                track->UnLink();
                gen_rastnest = true;
            }
        }

        if( pickersList.GetCount() )
            m_Parent->SaveCopyInUndoList( pickersList, UR_DELETED );

        if( m_DelMarkers->GetValue() )
            pcb->DeleteMARKERs();

        if( gen_rastnest )
            m_Parent->Compile_Ratsnest( NULL, true );

        if( m_Parent->IsGalCanvasActive() )
            pcb->GetRatsnest()->Recalculate();

    }

    m_Parent->GetCanvas()->Refresh();
    m_Parent->OnModify();

    EndModal( 1 );
}