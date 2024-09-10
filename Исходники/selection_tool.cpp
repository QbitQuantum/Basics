bool GERBVIEW_SELECTION_TOOL::selectMultiple()
{
    bool cancelled = false;     // Was the tool cancelled while it was running?
    m_multiple = true;          // Multiple selection mode is active
    KIGFX::VIEW* view = getView();
    getViewControls()->SetAutoPan( true );

    KIGFX::PREVIEW::SELECTION_AREA area;
    view->Add( &area );

    while( OPT_TOOL_EVENT evt = Wait() )
    {
        if( evt->IsCancel() )
        {
            cancelled = true;
            break;
        }

        if( evt->IsDrag( BUT_LEFT ) )
        {

            // Start drawing a selection box
            area.SetOrigin( evt->DragOrigin() );
            area.SetEnd( evt->Position() );
            area.SetAdditive( m_additive );
            area.SetSubtractive( m_subtractive );

            view->SetVisible( &area, true );
            view->Update( &area );
        }

        if( evt->IsMouseUp( BUT_LEFT ) )
        {
            // End drawing the selection box
            view->SetVisible( &area, false );

            // Mark items within the selection box as selected
            std::vector<KIGFX::VIEW::LAYER_ITEM_PAIR> selectedItems;

            // Filter the view items based on the selection box
            BOX2I selectionBox = area.ViewBBox();
            view->Query( selectionBox, selectedItems );         // Get the list of selected items

            std::vector<KIGFX::VIEW::LAYER_ITEM_PAIR>::iterator it, it_end;

            int width = area.GetEnd().x - area.GetOrigin().x;
            int height = area.GetEnd().y - area.GetOrigin().y;

            // Construct an EDA_RECT to determine EDA_ITEM selection
            EDA_RECT selectionRect( wxPoint( area.GetOrigin().x, area.GetOrigin().y ),
                                    wxSize( width, height ) );

            selectionRect.Normalize();

            for( it = selectedItems.begin(), it_end = selectedItems.end(); it != it_end; ++it )
            {
                auto item = static_cast<GERBER_DRAW_ITEM*>( it->first );

                if( !item || !selectable( item ) )
                    continue;

                /* Selection mode depends on direction of drag-selection:
                 * Left > Right : Select objects that are fully enclosed by selection
                 * Right > Left : Select objects that are crossed by selection
                 */

                if( width >= 0 )
                {
                    if( selectionBox.Contains( item->ViewBBox() ) )
                    {
                        if( m_subtractive )
                            unselect( item );
                        else
                            select( item );
                    }
                }
                else
                {
                    if( item->HitTest( selectionRect ) )
                    {
                        if( m_subtractive )
                            unselect( item );
                        else
                            select( item );
                    }

                }
            }

            if( m_selection.Size() == 1 )
                m_frame->SetCurItem( static_cast<GERBER_DRAW_ITEM*>( m_selection.Front() ) );
            else
                m_frame->SetCurItem( NULL );

            // Inform other potentially interested tools
            if( !m_selection.Empty() )
                m_toolMgr->ProcessEvent( SelectedEvent );

            break;  // Stop waiting for events
        }
    }

    // Stop drawing the selection box
    view->Remove( &area );
    m_multiple = false;         // Multiple selection mode is inactive
    getViewControls()->SetAutoPan( false );

    return cancelled;
}