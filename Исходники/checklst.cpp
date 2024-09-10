bool wxCheckListBox::Create(wxWindow *parent,
                            wxWindowID id,
                            const wxPoint &pos,
                            const wxSize &size,
                            int n,
                            const wxString choices[],
                            long style,
                            const wxValidator& validator,
                            const wxString &name)
{
    if ( !wxCheckListBoxBase::Create(parent, id, pos, size,
                                     n, choices, style, validator, name) )
        return false;

    m_noItems = 0 ; // this will be increased by our append command
    m_selected = 0;
    
    m_checkBoxWidth = 12;
    m_checkBoxHeight= 10;
    
    long h = m_checkBoxHeight ;
#if TARGET_CARBON
    GetThemeMetric(kThemeMetricCheckBoxWidth,(long *)&m_checkBoxWidth);    
    GetThemeMetric(kThemeMetricCheckBoxHeight,&h);
#endif

    const wxFont& font = GetFont();

    FontInfo finfo;
    FetchFontInfo(font.GetMacFontNum(),font.GetMacFontSize(),font.GetMacFontStyle(),&finfo);
    
    m_TextBaseLineOffset= finfo.leading+finfo.ascent;
    m_checkBoxHeight= finfo.leading+finfo.ascent+finfo.descent;
    
    if (m_checkBoxHeight<h)
    {
        m_TextBaseLineOffset+= (h-m_checkBoxHeight)/2;
        m_checkBoxHeight= h;
    }
        
    Rect bounds ;
    Str255 title ;
    
    MacPreControlCreate( parent , id ,  wxEmptyString , pos , size ,style, validator , name , &bounds , title ) ;

    ListDefSpec listDef;
    listDef.defType = kListDefUserProcType;
    if ( macCheckListDefUPP == NULL )
    {
      macCheckListDefUPP = NewListDefUPP( wxMacCheckListDefinition ); 
    }
        listDef.u.userProc = macCheckListDefUPP ;

#if TARGET_CARBON
    Size asize;


    CreateListBoxControl( MAC_WXHWND(parent->MacGetRootWindow()), &bounds, false, 0, 1, false, true,
                          m_checkBoxHeight+2, 14, false, &listDef, (ControlRef *)&m_macControl );

    GetControlData( (ControlHandle) m_macControl, kControlNoPart, kControlListBoxListHandleTag,
                   sizeof(ListHandle), (Ptr) &m_macList, &asize);

    SetControlReference( (ControlHandle) m_macControl, (long) this);
    SetControlVisibility( (ControlHandle) m_macControl, false, false);

#else

    long    result ;

    wxStAppResource resload ;
    m_macControl = (WXWidget) ::NewControl( MAC_WXHWND(parent->MacGetRootWindow()) , &bounds , title , false ,
                  kwxMacListWithVerticalScrollbar , 0 , 0, 
                  kControlListBoxProc , (long) this ) ;
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
    pt.v = 14 ;
    LCellSize( pt , (ListHandle)m_macList ) ;
    LAddColumn( 1 , 0 , (ListHandle)m_macList ) ;
#endif
    OptionBits  options = 0;
    if ( style & wxLB_MULTIPLE )
    {
        options += lNoExtend ;
    }
    else if ( style & wxLB_EXTENDED )
    {
        options += lExtendDrag ;
    }
    else
    {
        options = (OptionBits) lOnlyOne ;
    }
    SetListSelectionFlags((ListHandle)m_macList, options);
    
    MacPostControlCreate() ;
    
    for ( int i = 0 ; i < n ; i++ )
    {
        Append( choices[i] ) ;
    }
    
    LSetDrawingMode( true , (ListHandle) m_macList ) ;

    return TRUE;
}