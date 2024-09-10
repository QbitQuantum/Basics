int wxColourDialog::ShowModal()
{
    WX_HOOK_MODAL_DIALOG();

    // initialize the struct used by Windows
    CHOOSECOLOR chooseColorStruct;
    memset(&chooseColorStruct, 0, sizeof(CHOOSECOLOR));

    size_t i;

    // and transfer data from m_colourData to it
    COLORREF custColours[16];
    for ( i = 0; i < WXSIZEOF(custColours); i++ )
    {
        if ( m_colourData.GetCustomColour(i).IsOk() )
            custColours[i] = wxColourToRGB(m_colourData.GetCustomColour(i));
        else
            custColours[i] = RGB(255,255,255);
    }

    chooseColorStruct.lStructSize = sizeof(CHOOSECOLOR);
    if ( m_parent )
        chooseColorStruct.hwndOwner = GetHwndOf(m_parent);
    chooseColorStruct.rgbResult = wxColourToRGB(m_colourData.GetColour());
    chooseColorStruct.lpCustColors = custColours;

    chooseColorStruct.Flags = CC_RGBINIT | CC_ENABLEHOOK;
    chooseColorStruct.lCustData = (LPARAM)this;
    chooseColorStruct.lpfnHook = wxColourDialogHookProc;

    if ( m_colourData.GetChooseFull() )
        chooseColorStruct.Flags |= CC_FULLOPEN;

    // do show the modal dialog
    if ( !::ChooseColor(&chooseColorStruct) )
    {
        // 0 error means the dialog was simply cancelled, i.e. no real error
        // occurred
        const DWORD err = CommDlgExtendedError();
        if ( err )
        {
            wxLogError(_("Colour selection dialog failed with error %0lx."), err);
        }

        return wxID_CANCEL;
    }


    // transfer the values chosen by user back into m_colourData
    for ( i = 0; i < WXSIZEOF(custColours); i++ )
    {
      wxRGBToColour(m_colourData.m_custColours[i], custColours[i]);
    }

    wxRGBToColour(m_colourData.GetColour(), chooseColorStruct.rgbResult);

    // this doesn't seem to work (contrary to what MSDN implies) on current
    // Windows versions: CC_FULLOPEN is never set on return if it wasn't
    // initially set and vice versa
    //m_colourData.SetChooseFull((chooseColorStruct.Flags & CC_FULLOPEN) != 0);

    return wxID_OK;
}