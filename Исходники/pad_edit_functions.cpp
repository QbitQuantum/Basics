/*
 * Function DoPushPadProperties
 * Function to change pad properties for the given footprint or all identical footprints
 * aPad is the pattern. The given footprint is the parent of this pad
 * aSameFootprints: if true, make changes on all identical footprints
 * aPadShapeFilter: if true, make changes only on pads having the same shape as aPad
 * aPadOrientFilter: if true, make changes only on pads having the same orientation as aPad
 * aPadLayerFilter: if true, make changes only on pads having the same layers as aPad
 * aSaveForUndo: if true: create an entry in the Undo/Redo list
 *        (usually: true in Schematic editor, false in Module editor)
 */
void PCB_BASE_FRAME::DoPushPadProperties( D_PAD* aPad, bool aSameFootprints,
                                          bool aPadShapeFilter,
                                          bool aPadOrientFilter,
                                          bool aPadLayerFilter,
                                          bool aSaveForUndo )
{
    MODULE* Module_Ref = aPad->GetParent();
    double pad_orient = aPad->GetOrientation() - Module_Ref->GetOrientation();

    // Prepare an undo list:
    if( aSaveForUndo )
    {
        PICKED_ITEMS_LIST itemsList;

        if( aSameFootprints )
        {
            for( MODULE* module = m_Pcb->m_Modules;  module;  module = module->Next() )
            {
                if( module->GetFPID() == Module_Ref->GetFPID() )
                {
                    ITEM_PICKER itemWrapper( module, UR_CHANGED );
                    itemsList.PushItem( itemWrapper );
                }
            }
        }
        else
        {
            ITEM_PICKER itemWrapper( Module_Ref, UR_CHANGED );
            itemsList.PushItem( itemWrapper );
        }

        SaveCopyInUndoList( itemsList, UR_CHANGED );
    }

    // Update the current module and same others modules if requested.
    for( MODULE* module = m_Pcb->m_Modules;  module;  module = module->Next() )
    {
        if( !aSameFootprints && (module != Module_Ref) )
            continue;

        if( module->GetFPID() != Module_Ref->GetFPID() )
            continue;

        // Erase module on screen
        module->SetFlags( DO_NOT_DRAW );
        m_canvas->RefreshDrawingRect( module->GetBoundingBox() );
        module->ClearFlags( DO_NOT_DRAW );

        for( D_PAD* pad = module->PadsList();  pad;  pad = pad->Next() )
        {
            if( aPadShapeFilter && ( pad->GetShape() != aPad->GetShape() ) )
                continue;

            double currpad_orient = pad->GetOrientation() - module->GetOrientation();

            if( aPadOrientFilter && ( currpad_orient != pad_orient ) )
                continue;

            if( aPadLayerFilter && ( pad->GetLayerSet() != aPad->GetLayerSet() ) )
                continue;

            // Do not copy pad to itself, it can create issues with custom pad primitives.
            if( pad == aPad )
                continue;

            pad->ImportSettingsFromMaster( *aPad );
        }

        module->CalculateBoundingBox();
        m_canvas->RefreshDrawingRect( module->GetBoundingBox() );
    }

    OnModify();
}