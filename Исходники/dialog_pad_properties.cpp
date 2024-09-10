void DIALOG_PAD_PROPERTIES::PadPropertiesAccept( wxCommandEvent& event )
{
    if( !padValuesOK() )
        return;

    bool rastnestIsChanged = false;
    int  isign = m_isFlipped ? -1 : 1;

    transferDataToPad( m_padMaster );
    // m_padMaster is a pattern: ensure there is no net for this pad:
    m_padMaster->SetNetCode( NETINFO_LIST::UNCONNECTED );

    if( m_currentPad )   // Set current Pad parameters
    {
        wxSize  size;
        MODULE* module = m_currentPad->GetParent();

        m_parent->SaveCopyInUndoList( module, UR_CHANGED );
        module->SetLastEditTime();

        // redraw the area where the pad was, without pad (delete pad on screen)
        m_currentPad->SetFlags( DO_NOT_DRAW );
        m_parent->GetCanvas()->RefreshDrawingRect( m_currentPad->GetBoundingBox() );
        m_currentPad->ClearFlags( DO_NOT_DRAW );

        // Update values
        m_currentPad->SetShape( m_padMaster->GetShape() );
        m_currentPad->SetAttribute( m_padMaster->GetAttribute() );

        if( m_currentPad->GetPosition() != m_padMaster->GetPosition() )
        {
            m_currentPad->SetPosition( m_padMaster->GetPosition() );
            rastnestIsChanged = true;
        }

        // compute the pos 0 value, i.e. pad position for module with orientation = 0
        // i.e. relative to module origin (module position)
        wxPoint pt = m_currentPad->GetPosition() - module->GetPosition();

        RotatePoint( &pt, -module->GetOrientation() );

        m_currentPad->SetPos0( pt );

        m_currentPad->SetOrientation( m_padMaster->GetOrientation() * isign + module->GetOrientation() );

        m_currentPad->SetSize( m_padMaster->GetSize() );

        size = m_padMaster->GetDelta();
        size.y *= isign;
        m_currentPad->SetDelta( size );

        m_currentPad->SetDrillSize( m_padMaster->GetDrillSize() );
        m_currentPad->SetDrillShape( m_padMaster->GetDrillShape() );

        wxPoint offset = m_padMaster->GetOffset();
        offset.y *= isign;
        m_currentPad->SetOffset( offset );

        m_currentPad->SetPadToDieLength( m_padMaster->GetPadToDieLength() );

        if( m_currentPad->GetLayerSet() != m_padMaster->GetLayerSet() )
        {
            rastnestIsChanged = true;
            m_currentPad->SetLayerSet( m_padMaster->GetLayerSet() );
        }

        if( m_isFlipped )
            m_currentPad->SetLayerSet( FlipLayerMask( m_currentPad->GetLayerSet() ) );

        m_currentPad->SetPadName( m_padMaster->GetPadName() );

        wxString padNetname;

        // For PAD_HOLE_NOT_PLATED, ensure there is no net name selected
        if( m_padMaster->GetAttribute() != PAD_HOLE_NOT_PLATED  )
            padNetname = m_PadNetNameCtrl->GetValue();

        if( m_currentPad->GetNetname() != padNetname )
        {
            const NETINFO_ITEM* netinfo = m_board->FindNet( padNetname );

            if( !padNetname.IsEmpty() &&  netinfo == NULL )
            {
                DisplayError( NULL, _( "Unknown netname, netname not changed" ) );
            }
            else
            {
                rastnestIsChanged = true;
                m_currentPad->SetNetCode( netinfo->GetNet() );
            }
        }

        m_currentPad->SetLocalClearance( m_padMaster->GetLocalClearance() );
        m_currentPad->SetLocalSolderMaskMargin( m_padMaster->GetLocalSolderMaskMargin() );
        m_currentPad->SetLocalSolderPasteMargin( m_padMaster->GetLocalSolderPasteMargin() );
        m_currentPad->SetLocalSolderPasteMarginRatio( m_padMaster->GetLocalSolderPasteMarginRatio() );
        m_currentPad->SetZoneConnection( m_padMaster->GetZoneConnection() );
        m_currentPad->SetThermalWidth( m_padMaster->GetThermalWidth() );
        m_currentPad->SetThermalGap( m_padMaster->GetThermalGap() );

        module->CalculateBoundingBox();
        m_parent->SetMsgPanel( m_currentPad );

        // redraw the area where the pad was
        m_parent->GetCanvas()->RefreshDrawingRect( m_currentPad->GetBoundingBox() );
        m_parent->OnModify();
    }

    EndModal( wxID_OK );

    if( rastnestIsChanged )  // The net ratsnest must be recalculated
        m_board->m_Status_Pcb = 0;
}