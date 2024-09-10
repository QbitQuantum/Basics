void FOOTPRINT_EDIT_FRAME::Process_Special_Functions( wxCommandEvent& event )
{
    int        id = event.GetId();
    wxPoint    pos;

    INSTALL_UNBUFFERED_DC( dc, m_canvas );

    wxGetMousePosition( &pos.x, &pos.y );

    pos.y += 20;

    switch( id )
    {
    case wxID_CUT:
    case wxID_COPY:
    case ID_TOOLBARH_PCB_SELECT_LAYER:
    case ID_MODEDIT_PAD_SETTINGS:
    case ID_PCB_USER_GRID_SETUP:
    case ID_POPUP_PCB_ROTATE_TEXTEPCB:
    case ID_POPUP_PCB_EDIT_TEXTEPCB:
    case ID_POPUP_PCB_ROTATE_TEXTMODULE:
    case ID_POPUP_PCB_ROTATE_MODULE_CLOCKWISE:
    case ID_POPUP_PCB_ROTATE_MODULE_COUNTERCLOCKWISE:
    case ID_POPUP_PCB_EDIT_TEXTMODULE:
    case ID_POPUP_PCB_IMPORT_PAD_SETTINGS:
    case ID_POPUP_PCB_EXPORT_PAD_SETTINGS:
    case ID_POPUP_PCB_GLOBAL_IMPORT_PAD_SETTINGS:
    case ID_POPUP_PCB_STOP_CURRENT_DRAWING:
    case ID_POPUP_MODEDIT_EDIT_BODY_ITEM:
    case ID_POPUP_MODEDIT_EDIT_WIDTH_ALL_EDGE:
    case ID_POPUP_MODEDIT_EDIT_LAYER_ALL_EDGE:
    case ID_POPUP_MODEDIT_ENTER_EDGE_WIDTH:
    case ID_POPUP_PCB_DELETE_EDGE:
    case ID_POPUP_PCB_DELETE_TEXTMODULE:
    case ID_POPUP_PCB_DELETE_PAD:
    case ID_POPUP_DELETE_BLOCK:
    case ID_POPUP_PLACE_BLOCK:
    case ID_POPUP_ZOOM_BLOCK:
    case ID_POPUP_MIRROR_X_BLOCK:
    case ID_POPUP_ROTATE_BLOCK:
    case ID_POPUP_COPY_BLOCK:
        break;

    case ID_POPUP_CANCEL_CURRENT_COMMAND:
    default:
        if( m_canvas->IsMouseCaptured() )
        {
            //  for all other commands: stop the move in progress
            m_canvas->CallEndMouseCapture( &dc );
        }

        if( id != ID_POPUP_CANCEL_CURRENT_COMMAND )
            SetToolID( ID_NO_TOOL_SELECTED, m_canvas->GetDefaultCursor(), wxEmptyString );

        break;
    }

    switch( id )
    {
    case ID_EXIT:
        Close( true );
        break;

    case ID_MODEDIT_SELECT_CURRENT_LIB:
        {
            wxString library = SelectLibrary( GetCurrentLib() );

            if( library.size() )
            {
                Prj().SetRString( PROJECT::PCB_LIB_NICKNAME, library );
                updateTitle();
            }
        }
        break;

    case ID_OPEN_MODULE_VIEWER:
        {
            FOOTPRINT_VIEWER_FRAME* viewer = (FOOTPRINT_VIEWER_FRAME*) Kiway().Player( FRAME_PCB_MODULE_VIEWER, false );

            if( !viewer )
            {
                viewer = (FOOTPRINT_VIEWER_FRAME*) Kiway().Player( FRAME_PCB_MODULE_VIEWER, true );
                viewer->Show( true );
                viewer->Zoom_Automatique( false );
            }
            else
            {
                // On Windows, Raise() does not bring the window on screen, when iconized
                if( viewer->IsIconized() )
                    viewer->Iconize( false );

                viewer->Raise();

                // Raising the window does not set the focus on Linux.  This should work on
                // any platform.
                if( wxWindow::FindFocus() != viewer )
                    viewer->SetFocus();
            }
        }
        break;

    case ID_MODEDIT_DELETE_PART:
        DeleteModuleFromCurrentLibrary();
        break;

    case ID_MODEDIT_NEW_MODULE:
        {
            if( !Clear_Pcb( true ) )
                break;

            SetCrossHairPosition( wxPoint( 0, 0 ) );

            MODULE* module = CreateNewModule( wxEmptyString );

            if( module )        // i.e. if create module command not aborted
            {
                // Initialize data relative to nets and netclasses (for a new
                // module the defaults are used)
                // This is mandatory to handle and draw pads
                GetBoard()->BuildListOfNets();
                module->SetPosition( wxPoint( 0, 0 ) );

                if( GetBoard()->m_Modules )
                    GetBoard()->m_Modules->ClearFlags();

                Zoom_Automatique( false );
            }

            updateView();
            m_canvas->Refresh();

            GetScreen()->ClrModify();
        }
        break;

    case ID_MODEDIT_NEW_MODULE_FROM_WIZARD:
        {
            if( GetScreen()->IsModify() && !GetBoard()->IsEmpty() )
            {
                if( !IsOK( this,
                           _( "Current Footprint will be lost and this operation cannot be undone. Continue ?" ) ) )
                    break;
            }

            FOOTPRINT_WIZARD_FRAME* wizard = (FOOTPRINT_WIZARD_FRAME*) Kiway().Player(
                        FRAME_PCB_FOOTPRINT_WIZARD_MODAL, true );

            if( wizard->ShowModal( NULL, this ) )
            {
                // Creates the new footprint from python script wizard
                MODULE* module = wizard->GetBuiltFootprint();

                if( module == NULL )        // i.e. if create module command aborted
                    break;

                Clear_Pcb( false );

                SetCrossHairPosition( wxPoint( 0, 0 ) );

                //  Add the new object to board
                GetBoard()->Add( module, ADD_APPEND );

                // Initialize data relative to nets and netclasses (for a new
                // module the defaults are used)
                // This is mandatory to handle and draw pads
                GetBoard()->BuildListOfNets();
                module->SetPosition( wxPoint( 0, 0 ) );
                module->ClearFlags();

                Zoom_Automatique( false );
                updateView();
                m_canvas->Refresh();

                if( m_Draw3DFrame )
                    m_Draw3DFrame->NewDisplay();

                GetScreen()->ClrModify();
            }

            wizard->Destroy();
        }
        break;

    case ID_MODEDIT_SAVE_LIBMODULE:
        if( GetBoard()->m_Modules && GetCurrentLib().size() )
        {
            SaveFootprintInLibrary( GetCurrentLib(), GetBoard()->m_Modules, true, true );
            GetScreen()->ClrModify();
        }
        break;

    case ID_MODEDIT_INSERT_MODULE_IN_BOARD:
    case ID_MODEDIT_UPDATE_MODULE_IN_BOARD:
        {
            // update module in the current board,
            // not just add it to the board with total disregard for the netlist...
            PCB_EDIT_FRAME* pcbframe = (PCB_EDIT_FRAME*) Kiway().Player( FRAME_PCB, false );

            if( pcbframe == NULL )      // happens when the board editor is not active (or closed)
            {
                wxMessageBox( _("No board currently edited" ) );
                break;
            }

            BOARD*          mainpcb  = pcbframe->GetBoard();
            MODULE*         source_module  = NULL;
            MODULE*         module_in_edit = GetBoard()->m_Modules;

            // Search the old module (source) if exists
            // Because this source could be deleted when editing the main board...
            if( module_in_edit->GetLink() )        // this is not a new module ...
            {
                source_module = mainpcb->m_Modules;

                for( ; source_module != NULL; source_module = (MODULE*) source_module->Next() )
                {
                    if( module_in_edit->GetLink() == source_module->GetTimeStamp() )
                        break;
                }
            }

            if( ( source_module == NULL )
              && ( id == ID_MODEDIT_UPDATE_MODULE_IN_BOARD ) ) // source not found
            {
                wxString msg;
                msg.Printf( _( "Unable to find the footprint source on the main board" ) );
                msg << _( "\nCannot update the footprint" );
                DisplayError( this, msg );
                break;
            }

            if( ( source_module != NULL )
              && ( id == ID_MODEDIT_INSERT_MODULE_IN_BOARD ) ) // source not found
            {
                wxString msg;
                msg.Printf( _( "A footprint source was found on the main board" ) );
                msg << _( "\nCannot insert this footprint" );
                DisplayError( this, msg );
                break;
            }

            m_toolManager->RunAction( COMMON_ACTIONS::selectionClear, true );

            // Create the "new" module
            MODULE* newmodule = new MODULE( *module_in_edit );
            newmodule->SetParent( mainpcb );
            newmodule->SetLink( 0 );

            // Put the footprint in the main pcb linked list.
            mainpcb->Add( newmodule );

            if( source_module )         // this is an update command
            {
                // In the main board,
                // the new module replace the old module (pos, orient, ref, value
                // and connexions are kept)
                // and the source_module (old module) is deleted
                PICKED_ITEMS_LIST pickList;

                if( pcbframe->IsGalCanvasActive() )
                {
                    KIGFX::VIEW* view = pcbframe->GetGalCanvas()->GetView();
                    source_module->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
                    view->Remove( source_module );
                }

                pcbframe->Exchange_Module( source_module, newmodule, &pickList );
                newmodule->SetTimeStamp( module_in_edit->GetLink() );

                if( pickList.GetCount() )
                    pcbframe->SaveCopyInUndoList( pickList, UR_UNSPECIFIED );
            }
            else        // This is an insert command
            {
                wxPoint cursor_pos = pcbframe->GetCrossHairPosition();

                pcbframe->SetCrossHairPosition( wxPoint( 0, 0 ) );
                pcbframe->PlaceModule( newmodule, NULL );
                newmodule->SetPosition( wxPoint( 0, 0 ) );
                pcbframe->SetCrossHairPosition( cursor_pos );
                newmodule->SetTimeStamp( GetNewTimeStamp() );
                pcbframe->SaveCopyInUndoList( newmodule, UR_NEW );
            }

            newmodule->ClearFlags();
            GetScreen()->ClrModify();
            pcbframe->SetCurItem( NULL );
            mainpcb->m_Status_Pcb = 0;

            if( pcbframe->IsGalCanvasActive() )
            {
                RN_DATA* ratsnest = pcbframe->GetBoard()->GetRatsnest();
                ratsnest->Update( newmodule );
                ratsnest->Recalculate();

                KIGFX::VIEW* view = pcbframe->GetGalCanvas()->GetView();
                newmodule->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
                view->Add( newmodule );
                pcbframe->GetGalCanvas()->ForceRefresh();
            }
        }
        break;

    case ID_MODEDIT_IMPORT_PART:
        if( ! Clear_Pcb( true ) )
            break;                  // //this command is aborted

        SetCrossHairPosition( wxPoint( 0, 0 ) );
        Import_Module();

        if( GetBoard()->m_Modules )
            GetBoard()->m_Modules->ClearFlags();

        GetScreen()->ClrModify();
        Zoom_Automatique( false );
        m_canvas->Refresh();

        if( m_Draw3DFrame )
            m_Draw3DFrame->NewDisplay();

        break;

    case ID_MODEDIT_EXPORT_PART:
        if( GetBoard()->m_Modules )
            Export_Module( GetBoard()->m_Modules );
        break;

    case ID_MODEDIT_CREATE_NEW_LIB_AND_SAVE_CURRENT_PART:
        if( GetBoard()->m_Modules )
        {
            // CreateModuleLibrary() only creates a new library, does not save footprint
            wxString libPath = CreateNewLibrary();
            if( libPath.size() )
                SaveCurrentModule( &libPath );
        }
        break;

    case ID_MODEDIT_SHEET_SET:
        break;

    case ID_MODEDIT_LOAD_MODULE:
        wxLogDebug( wxT( "Loading module from library " ) + getLibPath() );

        if( ! Clear_Pcb( true ) )
            break;

        SetCrossHairPosition( wxPoint( 0, 0 ) );

        LoadModuleFromLibrary( GetCurrentLib(), Prj().PcbFootprintLibs(), true );

        if( GetBoard() && GetBoard()->m_Modules )
        {
            GetBoard()->m_Modules->ClearFlags();

            // if either m_Reference or m_Value are gone, reinstall them -
            // otherwise you cannot see what you are doing on board
            TEXTE_MODULE* ref = &GetBoard()->m_Modules->Reference();
            TEXTE_MODULE* val = &GetBoard()->m_Modules->Value();

            if( val && ref )
            {
                ref->SetType( TEXTE_MODULE::TEXT_is_REFERENCE );    // just in case ...

                if( ref->GetLength() == 0 )
                    ref->SetText( wxT( "Ref**" ) );

                val->SetType( TEXTE_MODULE::TEXT_is_VALUE );        // just in case ...

                if( val->GetLength() == 0 )
                    val->SetText( wxT( "Val**" ) );
            }
        }

        Zoom_Automatique( false );

        if( m_Draw3DFrame )
            m_Draw3DFrame->NewDisplay();

        GetScreen()->ClrModify();

        updateView();
        m_canvas->Refresh();

        break;

    case ID_MODEDIT_PAD_SETTINGS:
        InstallPadOptionsFrame( NULL );
        break;

    case ID_MODEDIT_CHECK:
        // Currently: not implemented
        break;

    case ID_MODEDIT_EDIT_MODULE_PROPERTIES:
        if( GetBoard()->m_Modules )
        {
            SetCurItem( GetBoard()->m_Modules );

            DIALOG_MODULE_MODULE_EDITOR dialog( this, (MODULE*) GetScreen()->GetCurItem() );

            int ret = dialog.ShowModal();
            GetScreen()->GetCurItem()->ClearFlags();
            GetBoard()->m_Modules.GetFirst()->ViewUpdate();

            if( ret > 0 )
                m_canvas->Refresh();
        }
        break;

    case ID_POPUP_CLOSE_CURRENT_TOOL:
        break;

    case ID_POPUP_CANCEL_CURRENT_COMMAND:
        break;

    case ID_POPUP_PCB_ROTATE_MODULE_COUNTERCLOCKWISE:
        m_canvas->MoveCursorToCrossHair();
        Rotate_Module( NULL, (MODULE*) GetScreen()->GetCurItem(), 900, true );
        m_canvas->Refresh();
        break;

    case ID_POPUP_PCB_ROTATE_MODULE_CLOCKWISE:
        m_canvas->MoveCursorToCrossHair();
        Rotate_Module( NULL, (MODULE*) GetScreen()->GetCurItem(), -900, true );
        m_canvas->Refresh();
        break;

    case ID_POPUP_PCB_EDIT_MODULE_PRMS:
        {
            DIALOG_MODULE_MODULE_EDITOR dialog( this, (MODULE*) GetScreen()->GetCurItem() );
            dialog.ShowModal();
            GetScreen()->GetCurItem()->ClearFlags();
            m_canvas->MoveCursorToCrossHair();
            m_canvas->Refresh();
        }
        break;

    case ID_POPUP_PCB_MOVE_PAD_REQUEST:
        m_canvas->MoveCursorToCrossHair();
        StartMovePad( (D_PAD*) GetScreen()->GetCurItem(), &dc, false );
        break;

    case ID_POPUP_PCB_EDIT_PAD:
        InstallPadOptionsFrame( (D_PAD*) GetScreen()->GetCurItem() );
        m_canvas->MoveCursorToCrossHair();
    break;

    case ID_POPUP_PCB_DELETE_PAD:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        DeletePad( (D_PAD*) GetScreen()->GetCurItem(), false );
        SetCurItem( NULL );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_DUPLICATE_ITEM:
        duplicateItems( false );
        break;

    case ID_POPUP_PCB_DUPLICATE_ITEM_AND_INCREMENT:
        duplicateItems( true );
        break;

    case ID_POPUP_PCB_MOVE_EXACT:
        moveExact();
        break;

    case ID_POPUP_PCB_CREATE_ARRAY:
        createArray();
        break;

    case ID_POPUP_PCB_IMPORT_PAD_SETTINGS:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        m_canvas->MoveCursorToCrossHair();
        Import_Pad_Settings( (D_PAD*) GetScreen()->GetCurItem(), true );
        break;

    case ID_POPUP_PCB_GLOBAL_IMPORT_PAD_SETTINGS:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        // Calls the global change dialog:
        DlgGlobalChange_PadSettings( (D_PAD*) GetScreen()->GetCurItem() );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_EXPORT_PAD_SETTINGS:
        m_canvas->MoveCursorToCrossHair();
        Export_Pad_Settings( (D_PAD*) GetScreen()->GetCurItem() );
        break;

    case ID_POPUP_PCB_EDIT_TEXTMODULE:
        InstallTextModOptionsFrame( static_cast<TEXTE_MODULE*>( GetScreen()->GetCurItem() ), &dc );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_MOVE_TEXTMODULE_REQUEST:
        m_canvas->MoveCursorToCrossHair();
        StartMoveTexteModule( static_cast<TEXTE_MODULE*>( GetScreen()->GetCurItem() ), &dc );
        break;

    case ID_POPUP_PCB_ROTATE_TEXTMODULE:
        RotateTextModule( static_cast<TEXTE_MODULE*>( GetScreen()->GetCurItem() ), &dc );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_DELETE_TEXTMODULE:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        DeleteTextModule( static_cast<TEXTE_MODULE*>( GetScreen()->GetCurItem() ) );
        SetCurItem( NULL );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_MOVE_EDGE:
        Start_Move_EdgeMod( static_cast<EDGE_MODULE*>( GetScreen()->GetCurItem() ), &dc );
        m_canvas->MoveCursorToCrossHair();
        break;

    case ID_POPUP_PCB_STOP_CURRENT_DRAWING:
        m_canvas->MoveCursorToCrossHair();

        if( GetScreen()->GetCurItem()->IsNew() )
        {
            End_Edge_Module( (EDGE_MODULE*) GetScreen()->GetCurItem() );
            SetCurItem( NULL );
        }
        break;

    case ID_POPUP_MODEDIT_ENTER_EDGE_WIDTH:
        {
            EDGE_MODULE* edge = NULL;

            if( GetScreen()->GetCurItem()
              && ( GetScreen()->GetCurItem()->Type() == PCB_MODULE_EDGE_T ) )
            {
                edge = (EDGE_MODULE*) GetScreen()->GetCurItem();
            }

            Enter_Edge_Width( edge );
            m_canvas->MoveCursorToCrossHair();

            if( edge )
                m_canvas->Refresh();
        }
        break;

    case  ID_POPUP_MODEDIT_EDIT_BODY_ITEM :
        m_canvas->MoveCursorToCrossHair();
        InstallFootprintBodyItemPropertiesDlg( (EDGE_MODULE*) GetScreen()->GetCurItem() );
        m_canvas->Refresh();
        break;

    case ID_POPUP_MODEDIT_EDIT_WIDTH_ALL_EDGE:
        m_canvas->MoveCursorToCrossHair();
        Edit_Edge_Width( NULL );
        m_canvas->Refresh();
        break;

    case ID_POPUP_MODEDIT_EDIT_LAYER_ALL_EDGE:
        m_canvas->MoveCursorToCrossHair();
        Edit_Edge_Layer( NULL );
        m_canvas->Refresh();
        break;

    case ID_POPUP_PCB_DELETE_EDGE:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        m_canvas->MoveCursorToCrossHair();
        RemoveStruct( GetScreen()->GetCurItem() );
        SetCurItem( NULL );
        break;

    case ID_MODEDIT_MODULE_ROTATE:
    case ID_MODEDIT_MODULE_MIRROR:
    case ID_MODEDIT_MODULE_MOVE_EXACT:
        SaveCopyInUndoList( GetBoard()->m_Modules, UR_MODEDIT );
        Transform( (MODULE*) GetScreen()->GetCurItem(), id );
        m_canvas->Refresh();
        break;

    case ID_PCB_DRAWINGS_WIDTHS_SETUP:
        InstallOptionsFrame( pos );
        break;

    case ID_PCB_PAD_SETUP:
        {
            BOARD_ITEM* item = GetCurItem();

            if( item )
            {
                if( item->Type() != PCB_PAD_T )
                    item = NULL;
            }

            InstallPadOptionsFrame( (D_PAD*) item );
        }
        break;

    case ID_PCB_USER_GRID_SETUP:
        InvokeDialogGrid();
        break;

    case ID_POPUP_PLACE_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_MOVE );
        m_canvas->SetAutoPanRequest( false );
        HandleBlockPlace( &dc );
        break;

    case ID_POPUP_COPY_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_COPY );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        m_canvas->SetAutoPanRequest( false );
        HandleBlockPlace( &dc );
        break;

    case ID_POPUP_ZOOM_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_ZOOM );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        HandleBlockEnd( &dc );
        break;

    case ID_POPUP_DELETE_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_DELETE );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        HandleBlockEnd( &dc );
        break;

    case ID_POPUP_ROTATE_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_ROTATE );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        HandleBlockEnd( &dc );
        break;

    case ID_POPUP_MIRROR_X_BLOCK:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_MIRROR_X );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        HandleBlockEnd( &dc );
        break;

    case ID_POPUP_MOVE_BLOCK_EXACT:
        GetScreen()->m_BlockLocate.SetCommand( BLOCK_MOVE_EXACT );
        GetScreen()->m_BlockLocate.SetMessageBlock( this );
        HandleBlockEnd( &dc );
        break;

    case ID_GEN_IMPORT_DXF_FILE:
        if( GetBoard()->m_Modules )
        {
            InvokeDXFDialogModuleImport( this, GetBoard()->m_Modules );
            m_canvas->Refresh();
        }
        break;

    default:
        DisplayError( this,
                      wxT( "FOOTPRINT_EDIT_FRAME::Process_Special_Functions error" ) );
        break;
    }
}