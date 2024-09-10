int PCB_EDIT_FRAME::Begin_Zone( wxDC* DC )
{
    ZONE_SETTINGS zoneInfo = GetZoneSettings();

    // verify if s_CurrentZone exists (could be deleted since last selection) :
    int ii;
    for( ii = 0; ii < GetBoard()->GetAreaCount(); ii++ )
    {
        if( s_CurrentZone == GetBoard()->GetArea( ii ) )
            break;
    }

    if( ii >= GetBoard()->GetAreaCount() ) // Not found: could be deleted since last selection
    {
        s_AddCutoutToCurrentZone = false;
        s_CurrentZone = NULL;
    }

    // If no zone contour in progress, a new zone is being created:
    if( !GetBoard()->m_CurrentZoneContour )
    {
        if( GetToolId() == ID_PCB_KEEPOUT_AREA_BUTT &&
            getActiveLayer() >= FIRST_NON_COPPER_LAYER )
        {
            DisplayError( this,
                          _( "Error: a keepout area is allowed only on copper layers" ) );
            return 0;
        }
        else
            GetBoard()->m_CurrentZoneContour = new ZONE_CONTAINER( GetBoard() );
    }

    ZONE_CONTAINER* zone = GetBoard()->m_CurrentZoneContour;

    if( zone->GetNumCorners() == 0 )    // Start a new contour: init zone params (net, layer ...)
    {
        if( !s_CurrentZone )            // A new outline is created, from scratch
        {
            ZONE_EDIT_T edited;

            // Init zone params to reasonable values
            zone->SetLayer( getActiveLayer() );

            // Prompt user for parameters:
            m_canvas->SetIgnoreMouseEvents( true );

            if( zone->IsOnCopperLayer() )
            {
                // Put a zone on a copper layer
                if( GetBoard()->GetHighLightNetCode() > 0 )
                {
                    zoneInfo.m_NetcodeSelection = GetBoard()->GetHighLightNetCode();

                    zone->SetNet( zoneInfo.m_NetcodeSelection );
                    zone->SetNetNameFromNetCode( );
                }
                double tmp = ZONE_THERMAL_RELIEF_GAP_MIL;
                wxGetApp().GetSettings()->Read( ZONE_THERMAL_RELIEF_GAP_STRING_KEY, &tmp );
                zoneInfo.m_ThermalReliefGap = KiROUND( tmp * IU_PER_MILS);

                tmp = ZONE_THERMAL_RELIEF_COPPER_WIDTH_MIL;
                wxGetApp().GetSettings()->Read( ZONE_THERMAL_RELIEF_COPPER_WIDTH_STRING_KEY,
                                                &tmp );
                zoneInfo.m_ThermalReliefCopperBridge = KiROUND( tmp * IU_PER_MILS );

                tmp = ZONE_CLEARANCE_MIL;
                wxGetApp().GetSettings()->Read( ZONE_CLEARANCE_WIDTH_STRING_KEY,
                                                &tmp );
                zoneInfo.m_ZoneClearance = KiROUND( tmp * IU_PER_MILS );

                tmp = ZONE_THICKNESS_MIL;
                wxGetApp().GetSettings()->Read( ZONE_MIN_THICKNESS_WIDTH_STRING_KEY,
                                                &tmp );
                zoneInfo.m_ZoneMinThickness = KiROUND( tmp * IU_PER_MILS );

                zoneInfo.m_CurrentZone_Layer = zone->GetLayer();

                if( GetToolId() == ID_PCB_KEEPOUT_AREA_BUTT )
                {
                    zoneInfo.SetIsKeepout( true );
                    edited = InvokeKeepoutAreaEditor( this, &zoneInfo );
                }
                else
                {
                    zoneInfo.SetIsKeepout( false );
                    edited = InvokeCopperZonesEditor( this, &zoneInfo );
                }
            }
            else   // Put a zone on a non copper layer (technical layer)
            {
                zoneInfo.SetIsKeepout( false );
                zoneInfo.m_NetcodeSelection = 0;     // No net for non copper zones
                edited = InvokeNonCopperZonesEditor( this, zone, &zoneInfo );
            }

            m_canvas->MoveCursorToCrossHair();
            m_canvas->SetIgnoreMouseEvents( false );

            if( edited == ZONE_ABORT )
                return 0;

            // Switch active layer to the selected zone layer
            setActiveLayer( zoneInfo.m_CurrentZone_Layer );

            SetZoneSettings( zoneInfo );
        }
        else
        {
            // Start a new contour: init zone params (net and layer) from an existing
            // zone (add cutout or similar zone)

            zoneInfo.m_CurrentZone_Layer = s_CurrentZone->GetLayer();
            setActiveLayer( s_CurrentZone->GetLayer() );

            zoneInfo << *s_CurrentZone;

            SetZoneSettings( zoneInfo );
        }

        // Show the Net for zones on copper layers
        if( zoneInfo.m_CurrentZone_Layer < FIRST_NO_COPPER_LAYER &&
            ! zoneInfo.GetIsKeepout() )
        {
            if( s_CurrentZone )
            {
                zoneInfo.m_NetcodeSelection = s_CurrentZone->GetNet();
                GetBoard()->SetZoneSettings( zoneInfo );
            }

            if( GetBoard()->IsHighLightNetON() )
            {
                HighLight( DC );    // Remove old highlight selection
            }

            GetBoard()->SetHighLightNet( zoneInfo.m_NetcodeSelection );
            HighLight( DC );
        }

        if( !s_AddCutoutToCurrentZone )
            s_CurrentZone = NULL; // the zone is used only once ("add similar zone" command)
    }

    // if first segment
    if( zone->GetNumCorners() == 0 )
    {
        zone->SetFlags( IS_NEW );
        zone->SetTimeStamp( GetNewTimeStamp() );

        zoneInfo.ExportSetting( *zone );

        zone->m_Poly->Start( zoneInfo.m_CurrentZone_Layer,
                             GetScreen()->GetCrossHairPosition().x,
                             GetScreen()->GetCrossHairPosition().y,
                             zone->GetHatchStyle() );

        zone->AppendCorner( GetScreen()->GetCrossHairPosition() );

        if( Drc_On && (m_drc->Drc( zone, 0 ) == BAD_DRC) && zone->IsOnCopperLayer() )
        {
            zone->ClearFlags();
            zone->RemoveAllContours();

            // use the form of SetCurItem() which does not write to the msg panel,
            // SCREEN::SetCurItem(), so the DRC error remains on screen.
            // PCB_EDIT_FRAME::SetCurItem() calls DisplayInfo().
            GetScreen()->SetCurItem( NULL );
            DisplayError( this,
                          _( "DRC error: this start point is inside or too close an other area" ) );
            return 0;
        }

        SetCurItem( zone );
        m_canvas->SetMouseCapture( Show_New_Edge_While_Move_Mouse, Abort_Zone_Create_Outline );
    }
    else    // edge in progress:
    {
        ii = zone->GetNumCorners() - 1;

        // edge in progress : the current corner coordinate was set
        // by Show_New_Edge_While_Move_Mouse
        if( zone->GetCornerPosition( ii - 1 ) != zone->GetCornerPosition( ii ) )
        {
            if( !Drc_On || !zone->IsOnCopperLayer() || ( m_drc->Drc( zone, ii - 1 ) == OK_DRC ) )
            {
                // Ok, we can add a new corner
                if( m_canvas->IsMouseCaptured() )
                    m_canvas->CallMouseCapture( DC, wxPoint(0,0), false );
                zone->AppendCorner( GetScreen()->GetCrossHairPosition() );
                SetCurItem( zone );     // calls DisplayInfo().
                if( m_canvas->IsMouseCaptured() )
                    m_canvas->CallMouseCapture( DC, wxPoint(0,0), false );
            }
        }
    }

    return zone->GetNumCorners();
}