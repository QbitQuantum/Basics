wxAuiDefaultDockArt::wxAuiDefaultDockArt()
{
#if defined( __WXMAC__ ) && wxOSX_USE_COCOA_OR_CARBON
    wxColor base_colour = wxColour( wxMacCreateCGColorFromHITheme(kThemeBrushToolbarBackground));
#else
    wxColor base_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
#endif

    // the base_colour is too pale to use as our base colour,
    // so darken it a bit --
    if ((255-base_colour.Red()) +
        (255-base_colour.Green()) +
        (255-base_colour.Blue()) < 60)
    {
        base_colour = wxAuiStepColour(base_colour, 92);
    }

    m_base_colour = base_colour;
    wxColor darker1_colour = wxAuiStepColour(base_colour, 85);
    wxColor darker2_colour = wxAuiStepColour(base_colour, 75);
    wxColor darker3_colour = wxAuiStepColour(base_colour, 60);
    //wxColor darker4_colour = wxAuiStepColour(base_colour, 50);
    wxColor darker5_colour = wxAuiStepColour(base_colour, 40);

    m_active_caption_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
    m_active_caption_gradient_colour = wxAuiLightContrastColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    m_active_caption_text_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);
    m_inactive_caption_colour = darker1_colour;
    m_inactive_caption_gradient_colour = wxAuiStepColour(base_colour, 97);
    m_inactive_caption_text_colour = *wxBLACK;

    m_sash_brush = wxBrush(base_colour);
    m_background_brush = wxBrush(base_colour);
    m_gripper_brush = wxBrush(base_colour);

    m_border_pen = wxPen(darker2_colour);
    m_gripper_pen1 = wxPen(darker5_colour);
    m_gripper_pen2 = wxPen(darker3_colour);
    m_gripper_pen3 = *wxWHITE_PEN;

#ifdef __WXMAC__
    m_caption_font = *wxSMALL_FONT;
#else
    m_caption_font = wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE);
#endif

    // some built in bitmaps
#if defined( __WXMAC__ )
     static const unsigned char close_bits[]={
         0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFE, 0x03, 0xF8, 0x01, 0xF0, 0x19, 0xF3,
         0xB8, 0xE3, 0xF0, 0xE1, 0xE0, 0xE0, 0xF0, 0xE1, 0xB8, 0xE3, 0x19, 0xF3,
         0x01, 0xF0, 0x03, 0xF8, 0x0F, 0xFE, 0xFF, 0xFF };
#elif defined(__WXGTK__)
     static const unsigned char close_bits[]={
         0xff, 0xff, 0xff, 0xff, 0x07, 0xf0, 0xfb, 0xef, 0xdb, 0xed, 0x8b, 0xe8,
         0x1b, 0xec, 0x3b, 0xee, 0x1b, 0xec, 0x8b, 0xe8, 0xdb, 0xed, 0xfb, 0xef,
         0x07, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#else
    static const unsigned char close_bits[]={
         // reduced height, symmetric
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf3, 0x9f, 0xf9,
         0x3f, 0xfc, 0x7f, 0xfe, 0x3f, 0xfc, 0x9f, 0xf9, 0xcf, 0xf3, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
      /*
         // same height as maximize/restore
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xcf, 0xf3, 0x9f, 0xf9,
         0x3f, 0xfc, 0x7f, 0xfe, 0x3f, 0xfc, 0x9f, 0xf9, 0xcf, 0xf3, 0xe7, 0xe7,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
      */
#endif

    static const unsigned char maximize_bits[] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xf0, 0xf7, 0xf7, 0x07, 0xf0,
        0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x07, 0xf0,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    static const unsigned char restore_bits[]={
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf0, 0x1f, 0xf0, 0xdf, 0xf7,
        0x07, 0xf4, 0x07, 0xf4, 0xf7, 0xf5, 0xf7, 0xf1, 0xf7, 0xfd, 0xf7, 0xfd,
        0x07, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    static const unsigned char pin_bits[]={
        0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0xfc,0xdf,0xfc,0xdf,0xfc,
        0xdf,0xfc,0xdf,0xfc,0xdf,0xfc,0x0f,0xf8,0x7f,0xff,0x7f,0xff,
        0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

#ifdef __WXMAC__
    m_inactive_close_bitmap = wxAuiBitmapFromBits(close_bits, 16, 16, *wxWHITE);
    m_active_close_bitmap = wxAuiBitmapFromBits(close_bits, 16, 16, *wxWHITE );
#else
    m_inactive_close_bitmap = wxAuiBitmapFromBits(close_bits, 16, 16, m_inactive_caption_text_colour);
    m_active_close_bitmap = wxAuiBitmapFromBits(close_bits, 16, 16, m_active_caption_text_colour);
#endif

#ifdef __WXMAC__
    m_inactive_maximize_bitmap = wxAuiBitmapFromBits(maximize_bits, 16, 16, *wxWHITE);
    m_active_maximize_bitmap = wxAuiBitmapFromBits(maximize_bits, 16, 16, *wxWHITE );
#else
    m_inactive_maximize_bitmap = wxAuiBitmapFromBits(maximize_bits, 16, 16, m_inactive_caption_text_colour);
    m_active_maximize_bitmap = wxAuiBitmapFromBits(maximize_bits, 16, 16, m_active_caption_text_colour);
#endif

#ifdef __WXMAC__
    m_inactive_restore_bitmap = wxAuiBitmapFromBits(restore_bits, 16, 16, *wxWHITE);
    m_active_restore_bitmap = wxAuiBitmapFromBits(restore_bits, 16, 16, *wxWHITE );
#else
    m_inactive_restore_bitmap = wxAuiBitmapFromBits(restore_bits, 16, 16, m_inactive_caption_text_colour);
    m_active_restore_bitmap = wxAuiBitmapFromBits(restore_bits, 16, 16, m_active_caption_text_colour);
#endif

    m_inactive_pin_bitmap = wxAuiBitmapFromBits(pin_bits, 16, 16, m_inactive_caption_text_colour);
    m_active_pin_bitmap = wxAuiBitmapFromBits(pin_bits, 16, 16, m_active_caption_text_colour);

    // default metric values
#if defined( __WXMAC__ ) && wxOSX_USE_COCOA_OR_CARBON
    SInt32 height;
    GetThemeMetric( kThemeMetricSmallPaneSplitterHeight , &height );
    m_sash_size = height;
#elif defined(__WXGTK__)
    m_sash_size = wxRendererNative::Get().GetSplitterParams(NULL).widthSash;
#else
    m_sash_size = 4;
#endif
    m_caption_size = 17;
    m_border_size = 1;
    m_button_size = 14;
    m_gripper_size = 9;
    m_gradient_type = wxAUI_GRADIENT_VERTICAL;
}