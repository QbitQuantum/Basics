void SCH_EDIT_FRAME::OnLeftClick( wxDC* aDC, const wxPoint& aPosition )
{
    SCH_ITEM*   item = GetScreen()->GetCurItem();
    wxPoint     gridPosition = GetGridPosition( aPosition );

    if( ( GetToolId() == ID_NO_TOOL_SELECTED ) || ( item && item->GetFlags() ) )
    {
        m_canvas->SetAutoPanRequest( false );
        SetRepeatItem( NULL );

        if( item && item->GetFlags() )
        {
            switch( item->Type() )
            {
            case SCH_LABEL_T:
            case SCH_GLOBAL_LABEL_T:
            case SCH_HIERARCHICAL_LABEL_T:
            case SCH_TEXT_T:
            case SCH_SHEET_PIN_T:
            case SCH_SHEET_T:
            case SCH_BUS_WIRE_ENTRY_T:
            case SCH_BUS_BUS_ENTRY_T:
            case SCH_JUNCTION_T:
            case SCH_COMPONENT_T:
            case SCH_FIELD_T:
            case SCH_BITMAP_T:
            case SCH_NO_CONNECT_T:
                addCurrentItemToList();
                return;

            case SCH_LINE_T:    // May already be drawing segment.
                break;

            default:
                wxFAIL_MSG( wxT( "SCH_EDIT_FRAME::OnLeftClick error.  Item type <" ) +
                            item->GetClass() + wxT( "> is already being edited." ) );
                item->ClearFlags();
                break;
            }
        }
        else
        {
            item = LocateAndShowItem( aPosition );
        }
    }

    switch( GetToolId() )
    {
    case ID_NO_TOOL_SELECTED:
        break;

    case ID_HIGHLIGHT:
        HighlightConnectionAtPosition( aPosition );
        break;

    case ID_HIERARCHY_PUSH_POP_BUTT:
        if( ( item && item->GetFlags() ) || ( g_RootSheet->CountSheets() == 0 ) )
            break;

        item = LocateAndShowItem( aPosition, SCH_COLLECTOR::SheetsOnly );

        if( item )  // The user has clicked on a sheet: this is an enter sheet command
        {
            m_CurrentSheet->push_back( (SCH_SHEET*) item );
            DisplayCurrentSheet();
        }
        else if( m_CurrentSheet->Last() != g_RootSheet )
        {   // The user has clicked ouside a sheet:this is an leave sheet command
            m_CurrentSheet->pop_back();
            DisplayCurrentSheet();
        }
        break;

    case ID_NOCONN_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            if( GetScreen()->GetItem( gridPosition, 0, SCH_NO_CONNECT_T ) == NULL )
            {
                SCH_NO_CONNECT*  no_connect = AddNoConnect( aDC, gridPosition );
                SetRepeatItem( no_connect );
                GetScreen()->SetCurItem( no_connect );
                m_canvas->SetAutoPanRequest( true );
            }
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_JUNCTION_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            if( GetScreen()->GetItem( gridPosition, 0, SCH_JUNCTION_T ) == NULL )
            {
                SCH_JUNCTION* junction = AddJunction( aDC, gridPosition, true );
                SetRepeatItem( junction );
                GetScreen()->SetCurItem( junction );
                m_canvas->SetAutoPanRequest( true );
            }
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_WIRETOBUS_ENTRY_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            CreateBusWireEntry();
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_BUSTOBUS_ENTRY_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            CreateBusBusEntry();
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_SCHEMATIC_DELETE_ITEM_BUTT:
        DeleteItemAtCrossHair( aDC );
        break;

    case ID_WIRE_BUTT:
        BeginSegment( aDC, LAYER_WIRE );
        m_canvas->SetAutoPanRequest( true );
        break;

    case ID_BUS_BUTT:
        BeginSegment( aDC, LAYER_BUS );
        m_canvas->SetAutoPanRequest( true );
        break;

    case ID_LINE_COMMENT_BUTT:
        BeginSegment( aDC, LAYER_NOTES );
        m_canvas->SetAutoPanRequest( true );
        break;

    case ID_TEXT_COMMENT_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            GetScreen()->SetCurItem( CreateNewText( aDC, LAYER_NOTES ) );
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_ADD_IMAGE_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            GetScreen()->SetCurItem( CreateNewImage( aDC ) );
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_LABEL_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            GetScreen()->SetCurItem( CreateNewText( aDC, LAYER_LOCLABEL ) );
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_GLABEL_BUTT:
    case ID_HIERLABEL_BUTT:
        if( (item == NULL) || (item->GetFlags() == 0) )
        {
            if( GetToolId() == ID_GLABEL_BUTT )
                GetScreen()->SetCurItem( CreateNewText( aDC, LAYER_GLOBLABEL ) );

            if( GetToolId() == ID_HIERLABEL_BUTT )
                GetScreen()->SetCurItem( CreateNewText( aDC, LAYER_HIERLABEL ) );

            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_SHEET_SYMBOL_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            item = CreateSheet( aDC );

            if( item != NULL )
            {
                GetScreen()->SetCurItem( item );
                m_canvas->SetAutoPanRequest( true );
            }
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_IMPORT_HLABEL_BUTT:
    case ID_SHEET_PIN_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
            item = LocateAndShowItem( aPosition, SCH_COLLECTOR::SheetsAndSheetLabels );

        if( item == NULL )
            break;

        if( (item->Type() == SCH_SHEET_T) && (item->GetFlags() == 0) )
        {
            if( GetToolId() == ID_IMPORT_HLABEL_BUTT )
                GetScreen()->SetCurItem( ImportSheetPin( (SCH_SHEET*) item, aDC ) );
            else
                GetScreen()->SetCurItem( CreateSheetPin( (SCH_SHEET*) item, aDC ) );
        }
        else if( (item->Type() == SCH_SHEET_PIN_T) && (item->GetFlags() != 0) )
        {
            addCurrentItemToList();
        }
        break;

    case ID_SCH_PLACE_COMPONENT:
        if( (item == NULL) || (item->GetFlags() == 0) )
        {
            GetScreen()->SetCurItem( Load_Component( aDC, NULL,
                                                     s_CmpNameList, s_CmpLastUnit, true ) );
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

    case ID_PLACE_POWER_BUTT:
        if( ( item == NULL ) || ( item->GetFlags() == 0 ) )
        {
            SCHLIB_FILTER filter;
            filter.FilterPowerParts( true );
            GetScreen()->SetCurItem( Load_Component( aDC, &filter,
                                                     s_PowerNameList, s_LastPowerUnit, false ) );
            m_canvas->SetAutoPanRequest( true );
        }
        else
        {
            addCurrentItemToList();
        }
        break;

#ifdef KICAD_SPICE
    case ID_SIM_PROBE:
        {
            const KICAD_T wiresAndComponents[] = { SCH_LINE_T, SCH_COMPONENT_T, SCH_SHEET_PIN_T };
            item = LocateAndShowItem( aPosition, wiresAndComponents );

            if( !item )
                break;

            NETLIST_OBJECT_LIST* netlist = BuildNetListBase();

            for( NETLIST_OBJECT* obj : *netlist )
            {
                if( obj->m_Comp == item )
                {
                    SIM_PLOT_FRAME* simFrame = (SIM_PLOT_FRAME*) Kiway().Player( FRAME_SIMULATOR, false );

                    if( simFrame )
                        simFrame->AddVoltagePlot( obj->GetNetName() );

                    break;
                }
            }
        }
        break;

    case ID_SIM_TUNE:
        {
            const KICAD_T fieldsAndComponents[] = { SCH_COMPONENT_T, SCH_FIELD_T };
            item = LocateAndShowItem( aPosition, fieldsAndComponents );

            if( !item )
                return;

            if( item->Type() != SCH_COMPONENT_T )
            {
                item = static_cast<SCH_ITEM*>( item->GetParent() );

                if( item->Type() != SCH_COMPONENT_T )
                    return;
            }

            SIM_PLOT_FRAME* simFrame = (SIM_PLOT_FRAME*) Kiway().Player( FRAME_SIMULATOR, false );

            if( simFrame )
                simFrame->AddTuner( static_cast<SCH_COMPONENT*>( item ) );
        }
        break;
#endif /* KICAD_SPICE */

    default:
        SetToolID( ID_NO_TOOL_SELECTED, m_canvas->GetDefaultCursor(), wxEmptyString );
        wxFAIL_MSG( wxT( "SCH_EDIT_FRAME::OnLeftClick invalid tool ID <" ) +
                    wxString::Format( wxT( "%d> selected." ), GetToolId() ) );
    }
}