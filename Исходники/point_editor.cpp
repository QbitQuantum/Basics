int POINT_EDITOR::OnSelectionChange( const TOOL_EVENT& aEvent )
{
    const SELECTION& selection = m_selectionTool->GetSelection();

    if( selection.Size() == 1 )
    {
        Activate();

        KIGFX::VIEW_CONTROLS* controls = getViewControls();
        KIGFX::VIEW* view = getView();
        PCB_BASE_EDIT_FRAME* editFrame = getEditFrame<PCB_BASE_EDIT_FRAME>();
        EDA_ITEM* item = selection.items.GetPickedItem( 0 );

        m_editPoints = EDIT_POINTS_FACTORY::Make( item, getView()->GetGAL() );

        if( !m_editPoints )
            return 0;

        view->Add( m_editPoints.get() );
        m_editedPoint = NULL;
        bool modified = false;

        // Main loop: keep receiving events
        while( OPT_TOOL_EVENT evt = Wait() )
        {
            if( !m_editPoints ||
                evt->Matches( m_selectionTool->ClearedEvent ) ||
                evt->Matches( m_selectionTool->UnselectedEvent ) ||
                evt->Matches( m_selectionTool->SelectedEvent ) )
            {
                break;
            }

            if( evt->IsMotion() )
            {
                EDIT_POINT* point = m_editPoints->FindPoint( evt->Position() );

                if( m_editedPoint != point )
                    setEditedPoint( point );
            }

            else if( evt->IsAction( &COMMON_ACTIONS::pointEditorAddCorner ) )
            {
                addCorner( controls->GetCursorPosition() );
                updatePoints();
            }

            else if( evt->IsAction( &COMMON_ACTIONS::pointEditorRemoveCorner ) )
            {
                if( m_editedPoint )
                {
                    removeCorner( m_editedPoint );
                    updatePoints();
                }
            }

            else if( evt->IsDrag( BUT_LEFT ) && m_editedPoint )
            {
                if( !modified )
                {
                    // Save items, so changes can be undone
                    editFrame->OnModify();
                    editFrame->SaveCopyInUndoList( selection.items, UR_CHANGED );
                    controls->ForceCursorPosition( false );
                    m_original = *m_editedPoint;    // Save the original position
                    controls->SetAutoPan( true );
                    modified = true;
                }

                bool enableAltConstraint = !!evt->Modifier( MD_CTRL );
                if( enableAltConstraint != (bool) m_altConstraint )  // alternative constraint
                    setAltConstraint( enableAltConstraint );

                m_editedPoint->SetPosition( controls->GetCursorPosition() );

                if( m_altConstraint )
                    m_altConstraint->Apply();
                else
                    m_editedPoint->ApplyConstraint();

                updateItem();
                updatePoints();

                m_editPoints->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            }

            else if( evt->IsAction( &COMMON_ACTIONS::pointEditorUpdate ) )
            {
                updatePoints();
            }

            else if( evt->IsMouseUp( BUT_LEFT ) )
            {
                controls->SetAutoPan( false );
                setAltConstraint( false );
                modified = false;
                m_toolMgr->PassEvent();
            }

            else if( evt->IsCancel() )
            {
                if( modified )      // Restore the last change
                {
                    wxCommandEvent dummy;
                    editFrame->RestoreCopyFromUndoList( dummy );

                    updatePoints();
                    modified = false;
                }

                // Let the selection tool receive the event too
                m_toolMgr->PassEvent();

                break;
            }

            else
            {
                m_toolMgr->PassEvent();
            }
        }

        if( m_editPoints )
        {
            finishItem();
            item->ViewUpdate( KIGFX::VIEW_ITEM::GEOMETRY );
            view->Remove( m_editPoints.get() );
            m_editPoints.reset();
        }

        controls->ShowCursor( false );
        controls->SetAutoPan( false );
        controls->SetSnapping( false );
        controls->ForceCursorPosition( false );
    }

    return 0;
}