void FOOTPRINT_EDIT_FRAME::RestoreCopyFromUndoList( wxCommandEvent& aEvent )
{
    if( UndoRedoBlocked() )
        return;

    if( GetScreen()->GetUndoCommandCount() <= 0 )
        return;

    // Inform tools that undo command was issued
    TOOL_EVENT event( TC_MESSAGE, TA_UNDO_REDO, AS_GLOBAL );
    m_toolManager->ProcessEvent( event );

    if( UndoRedoBlocked() )
        return;

    // Save current module state in redo list
    PICKED_ITEMS_LIST* lastcmd = new PICKED_ITEMS_LIST();
    MODULE* module = GetBoard()->m_Modules.PopFront();
    ITEM_PICKER wrapper( module, UR_MODEDIT );
    KIGFX::VIEW* view = GetGalCanvas()->GetView();
    lastcmd->PushItem( wrapper );
    GetScreen()->PushCommandToRedoList( lastcmd );

    view->Remove( module );
    module->RunOnChildren( std::bind( &KIGFX::VIEW::Remove, view, _1 ) );

    // Retrieve last module state from undo list
    lastcmd = GetScreen()->PopCommandFromUndoList();
    wrapper = lastcmd->PopItem();
    module = (MODULE*) wrapper.GetItem();
    delete lastcmd;

    if( module )
    {
        GetBoard()->Add( module, ADD_APPEND );
        view->Add( module );
        module->RunOnChildren( std::bind( &KIGFX::VIEW::Add, view, _1 ) );
        module->ViewUpdate();
    }

    SetCurItem( NULL );

    OnModify();
    m_canvas->Refresh();
}