bool wxListBox::Create(wxWindow *parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       int n, const wxString choices[],
                       long style,
                       const wxValidator& validator,
                       const wxString& name)
{
    if ( !wxListBoxBase::Create(parent, id, pos, size, style & ~(wxHSCROLL|wxVSCROLL), validator, name) )
        return false;

    m_noItems = 0 ; // this will be increased by our append command
    m_selected = 0;

    Rect bounds ;
    Str255 title ;

    MacPreControlCreate( parent , id ,  wxEmptyString , pos , size ,style, validator , name , &bounds , title ) ;

    ListDefSpec listDef;
    listDef.defType = kListDefUserProcType;
    if ( macListDefUPP == NULL )
    {
        macListDefUPP = NewListDefUPP( wxMacListDefinition );
    }
    listDef.u.userProc = macListDefUPP ;

    Str255 fontName ;
    SInt16 fontSize ;
    Style fontStyle ;
#if TARGET_CARBON
    GetThemeFont(kThemeViewsFont , GetApplicationScript() , fontName , &fontSize , &fontStyle ) ;
#else
    GetFontName( kFontIDMonaco , fontName ) ;
    fontSize = 9 ;
    fontStyle = normal ;
#endif
    SetFont( wxFont (fontSize, wxSWISS, wxNORMAL, wxNORMAL , false , wxMacMakeStringFromPascal( fontName ) ) ) ;
#if TARGET_CARBON
    Size asize;


    CreateListBoxControl( MAC_WXHWND(parent->MacGetRootWindow()), &bounds, false, 0, 1, (style & wxLB_HSCROLL), true,
                          kwxMacListItemHeight, kwxMacListItemHeight, false, &listDef, (ControlRef *)&m_macControl );

    GetControlData( (ControlHandle) m_macControl, kControlNoPart, kControlListBoxListHandleTag,
                   sizeof(ListHandle), (Ptr) &m_macList, &asize);

    SetControlReference( (ControlHandle) m_macControl, (long) this);
    SetControlVisibility( (ControlHandle) m_macControl, false, false);

#else

    long    result ;
    wxStAppResource resload ;
    m_macControl = (WXWidget) ::NewControl( MAC_WXHWND(parent->MacGetRootWindow()) , &bounds , title , false ,
                  (style & wxLB_HSCROLL) ? kwxMacListWithVerticalAndHorizontalScrollbar : kwxMacListWithVerticalScrollbar ,
                  0 , 0, kControlListBoxProc , (long) this ) ;
    ::GetControlData( (ControlHandle) m_macControl , kControlNoPart , kControlListBoxListHandleTag ,
               sizeof( ListHandle ) , (char*) &m_macList  , &result ) ;

    HLock( (Handle) m_macList ) ;
    ldefHandle ldef ;
    ldef = (ldefHandle) NewHandle( sizeof(ldefRec) ) ;
    if (  (**(ListHandle)m_macList).listDefProc != NULL )
    {
      (**ldef).instruction = 0x4EF9;  /* JMP instruction */
      (**ldef).function = (void(*)()) listDef.u.userProc;
      (**(ListHandle)m_macList).listDefProc = (Handle) ldef ;
    }

    Point pt = (**(ListHandle)m_macList).cellSize ;
    pt.v = kwxMacListItemHeight ;
    LCellSize( pt , (ListHandle)m_macList ) ;
    LAddColumn( 1 , 0 , (ListHandle)m_macList ) ;
#endif
    OptionBits  options = 0;
    if ( style & wxLB_MULTIPLE )
    {
        options += lExtendDrag + lUseSense  ;
    }
    else if ( style & wxLB_EXTENDED )
    {
        // default behaviour
    }
    else
    {
        options = (OptionBits) lOnlyOne ;
    }
    SetListSelectionFlags((ListHandle)m_macList, options);

    for ( int i = 0 ; i < n ; i++ )
    {
        Append( choices[i] ) ;
    }

    MacPostControlCreate() ;

    LSetDrawingMode( true , (ListHandle)m_macList ) ;

    return true;
}