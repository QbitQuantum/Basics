/*
 * Function GlobalChange_PadSettings
 * Function to change pad caracteristics for the given footprint
 * or alls footprints which look like the given footprint
 * aPad is the pattern. The given footprint is the parent of this pad
 * aSameFootprints: if true, make changes on all identical footprints
 * aPadShapeFilter: if true, make changes only on pads having the same shape as aPad
 * aPadOrientFilter: if true, make changes only on pads having the same orientation as aPad
 * aPadLayerFilter: if true, make changes only on pads having the same layers as aPad
 * aRedraw: if true: redraws the footprint
 * aSaveForUndo: if true: create an entry in the Undo/Redo list
 *        (usually: true in Schematic editor, false in Module editor)
 */
void PCB_BASE_FRAME::GlobalChange_PadSettings( D_PAD* aPad,
                                               bool aSameFootprints,
                                               bool aPadShapeFilter,
                                               bool aPadOrientFilter,
                                               bool aPadLayerFilter,
                                               bool aRedraw, bool aSaveForUndo )
{
    if( aPad == NULL )
        aPad = &GetDesignSettings().m_Pad_Master;

    MODULE* module = aPad->GetParent();

    if( module == NULL )
    {
        DisplayError( this, wxT( "Global_Import_Pad_Settings() Error: NULL module" ) );
        return;
    }

    // Search and copy the name of library reference.
    MODULE* Module_Ref = module;
    double pad_orient = aPad->GetOrientation() - Module_Ref->GetOrientation();

    // Prepare an undo list:
    if( aSaveForUndo )
    {
        PICKED_ITEMS_LIST itemsList;

        for( module = m_Pcb->m_Modules;  module;  module = module->Next() )
        {
            if( !aSameFootprints && (module != Module_Ref) )
                continue;

            if( module->GetFPID() != Module_Ref->GetFPID() )
                continue;

            bool   saveMe = false;

            for( D_PAD* pad = module->Pads();  pad;  pad = pad->Next() )
            {
                // Filters changes prohibited.
                if( aPadShapeFilter && ( pad->GetShape() != aPad->GetShape() ) )
                    continue;

                double currpad_orient = pad->GetOrientation() - module->GetOrientation();

                if( aPadOrientFilter && ( currpad_orient != pad_orient ) )
                    continue;

                if( aPadLayerFilter  &&  pad->GetLayerSet() != aPad->GetLayerSet() )
                    continue;

                saveMe = true;
            }

            if( saveMe )
            {
                ITEM_PICKER itemWrapper( module, UR_CHANGED );

                itemsList.PushItem( itemWrapper );
            }
        }

        SaveCopyInUndoList( itemsList, UR_CHANGED );
    }

    // Update the current module and same others modules if requested.
    for( module = m_Pcb->m_Modules;  module;  module = module->Next() )
    {
        if( !aSameFootprints && (module != Module_Ref) )
            continue;

        if( module->GetFPID() != Module_Ref->GetFPID() )
            continue;

        // Erase module on screen
        if( aRedraw )
        {
            module->SetFlags( DO_NOT_DRAW );
            m_canvas->RefreshDrawingRect( module->GetBoundingBox() );
            module->ClearFlags( DO_NOT_DRAW );
        }

        for( D_PAD* pad = module->Pads();  pad;  pad = pad->Next() )
        {
            // Filters changes prohibited.
            if( aPadShapeFilter && ( pad->GetShape() != aPad->GetShape() ) )
                continue;

            if( aPadOrientFilter &&  (pad->GetOrientation() - module->GetOrientation()) != pad_orient )
                continue;

            if( aPadLayerFilter )
            {
                if( pad->GetLayerSet() != aPad->GetLayerSet() )
                    continue;
                else
                    m_Pcb->m_Status_Pcb &= ~( LISTE_RATSNEST_ITEM_OK | CONNEXION_OK);
            }

            // Change characteristics:
            pad->SetAttribute( aPad->GetAttribute() );
            pad->SetShape( aPad->GetShape() );

            pad->SetLayerSet( aPad->GetLayerSet() );

            pad->SetSize( aPad->GetSize() );
            pad->SetDelta( aPad->GetDelta() );
            pad->SetOffset( aPad->GetOffset() );

            pad->SetDrillSize( aPad->GetDrillSize() );
            pad->SetDrillShape( aPad->GetDrillShape() );

            pad->SetOrientation( pad_orient + module->GetOrientation() );

            // copy also local mask margins, because these parameters usually depend on
            // pad sizes and layers
            pad->SetLocalSolderMaskMargin( aPad->GetLocalSolderMaskMargin() );
            pad->SetLocalSolderPasteMargin( aPad->GetLocalSolderPasteMargin() );
            pad->SetLocalSolderPasteMarginRatio( aPad->GetLocalSolderPasteMarginRatio() );

            if( pad->GetShape() != PAD_TRAPEZOID )
            {
                pad->SetDelta( wxSize( 0, 0 ) );
            }

            if( pad->GetShape() == PAD_CIRCLE )
            {
                // Ensure pad size.y = pad size.x
                int size = pad->GetSize().x;
                pad->SetSize( wxSize( size, size ) );
            }

            switch( pad->GetAttribute() )
            {
            case PAD_SMD:
            case PAD_CONN:
                pad->SetDrillSize( wxSize( 0, 0 ) );
                pad->SetOffset( wxPoint( 0, 0 ) );
                break;

            default:
                break;
            }
        }

        module->CalculateBoundingBox();

        if( aRedraw )
            m_canvas->RefreshDrawingRect( module->GetBoundingBox() );
    }

    OnModify();
}