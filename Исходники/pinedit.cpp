void LIB_EDIT_FRAME::OnEditPin( wxCommandEvent& event )
{
    if( m_drawItem == NULL || m_drawItem->Type() != LIB_PIN_T )
        return;

    STATUS_FLAGS item_flags = m_drawItem->GetFlags(); // save flags to restore them after editing
    LIB_PIN* pin = (LIB_PIN*) m_drawItem;

    DIALOG_LIB_EDIT_PIN dlg( this, pin );

    wxString units = GetUnitsLabel( g_UserUnit );
    dlg.SetOrientationList( LIB_PIN::GetOrientationNames(), LIB_PIN::GetOrientationSymbols() );
    dlg.SetOrientation( LIB_PIN::GetOrientationCodeIndex( pin->GetOrientation() ) );
    dlg.SetStyleList( LIB_PIN::GetStyleNames(), LIB_PIN::GetStyleSymbols() );
    dlg.SetStyle( LIB_PIN::GetStyleCodeIndex( pin->GetShape() ) );
    dlg.SetElectricalTypeList( LIB_PIN::GetElectricalTypeNames(),
                               LIB_PIN::GetElectricalTypeSymbols() );
    dlg.SetElectricalType( pin->GetType() );
    dlg.SetName( pin->GetName() );
    dlg.SetNameTextSize( ReturnStringFromValue( g_UserUnit, pin->GetNameTextSize() ) );
    dlg.SetNameTextSizeUnits( units );
    dlg.SetPadName( pin->GetNumberString() );
    dlg.SetPadNameTextSize( ReturnStringFromValue( g_UserUnit, pin->GetNumberTextSize() ) );

    dlg.SetPadNameTextSizeUnits( units );
    dlg.SetLength( ReturnStringFromValue( g_UserUnit, pin->GetLength() ) );
    dlg.SetLengthUnits( units );
    dlg.SetAddToAllParts( pin->GetUnit() == 0 );
    dlg.SetAddToAllBodyStyles( pin->GetConvert() == 0 );
    dlg.SetVisible( pin->IsVisible() );

    /* This ugly hack fixes a bug in wxWidgets 2.8.7 and likely earlier
     * versions for the flex grid sizer in wxGTK that prevents the last
     * column from being sized correctly.  It doesn't cause any problems
     * on win32 so it doesn't need to wrapped in ugly #ifdef __WXGTK__
     * #endif.
     */
    dlg.Layout();
    dlg.Fit();
    dlg.SetMinSize( dlg.GetSize() );
    // dlg.SetLastSizeAndPosition();    // done in DIALOG_SHIM::Show()

    if( dlg.ShowModal() == wxID_CANCEL )
    {
        if( pin->IsNew() )
        {
            pin->SetFlags( IS_CANCELLED );
            m_canvas->EndMouseCapture();
        }
        return;
    }

    // Save the pin properties to use for the next new pin.
    LastPinNameSize = ReturnValueFromString( g_UserUnit, dlg.GetNameTextSize() );
    LastPinNumSize = ReturnValueFromString( g_UserUnit, dlg.GetPadNameTextSize() );
    LastPinOrient = LIB_PIN::GetOrientationCode( dlg.GetOrientation() );
    LastPinLength = ReturnValueFromString( g_UserUnit, dlg.GetLength() );
    LastPinShape = LIB_PIN::GetStyleCode( dlg.GetStyle() );
    LastPinType = dlg.GetElectricalType();
    LastPinCommonConvert = dlg.GetAddToAllBodyStyles();
    LastPinCommonUnit = dlg.GetAddToAllParts();
    LastPinVisible = dlg.GetVisible();

    pin->EnableEditMode( true, m_editPinsPerPartOrConvert );
    pin->SetName( dlg.GetName() );
    pin->SetNameTextSize( LastPinNameSize );
    pin->SetNumber( dlg.GetPadName() );
    pin->SetNumberTextSize( LastPinNumSize );
    pin->SetOrientation( LastPinOrient );
    pin->SetLength( LastPinLength );
    pin->SetType( LastPinType );
    pin->SetShape( LastPinShape );
    pin->SetConversion( ( LastPinCommonConvert ) ? 0 : m_convert );
    pin->SetPartNumber( ( LastPinCommonUnit ) ? 0 : m_unit );
    pin->SetVisible( LastPinVisible );

    if( pin->IsModified() || pin->IsNew() )
    {
        if( !pin->InEditMode() )
            SaveCopyInUndoList( pin->GetParent() );

        OnModify( );

        MSG_PANEL_ITEMS items;
        pin->GetMsgPanelInfo( items );
        SetMsgPanel( items );
        m_canvas->Refresh();
    }

    pin->EnableEditMode( false, m_editPinsPerPartOrConvert );

    // Restore pin flags, that can be changed by the dialog editor
    pin->ClearFlags();
    pin->SetFlags( item_flags );
}