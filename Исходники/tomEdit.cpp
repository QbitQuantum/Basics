bool tomEdit::Init() 
{
    WLDC dc(this) ;
    s_XPixelPerInch = dc.GetDeviceCaps(LOGPIXELSX) ;
    s_YPixelPerInch = dc.GetDeviceCaps(LOGPIXELSY) ;

    m_ref_count = 1 ;

    m_show_vert_scroll_bar = false ;
    m_show_horz_scroll_bar = false ;
    m_background_transparent = true ;
    m_use_system_background_color = true ;
    m_use_system_highlight_text_color = true ;
    m_use_system_highlight_text_background_color = true ;

    m_word_wrap = !(GetStyle() & (WS_HSCROLL | ES_AUTOHSCROLL)) ;

    HRESULT hr ;
    IUnknown * pUnknown ;

    // 由于CreateTextServices会触发TxGetCharFormat和TxGetParaFormat，
    // 所以要在此之前初始化CharFormat和ParaFormat

    // 初始化CharFormat
    InitDefaultCharFormat() ;

    // 初始化ParaFormat
    InitDefaultParaFormat() ;

    RECT bound_in_host ;
    GetRectInHost(&bound_in_host) ;

    if (FAILED(CreateBorder(IID_IRectangleBorder, (IUnknown**)&m_border)))
        return FALSE ;
    m_border->SetPos(bound_in_host.left, bound_in_host.top) ;
    m_border->SetSize(bound_in_host.right - bound_in_host.left, bound_in_host.bottom - bound_in_host.top) ;
    m_border->SetInset(m_border_inset.left, m_border_inset.top, m_border_inset.right, m_border_inset.bottom) ;

    if (FAILED(CreateTextServices(NULL, this, &pUnknown)))
        return false ;

    hr = pUnknown->QueryInterface(IID_ITextServices, (void**)&m_services) ;
    pUnknown->Release() ;

    if (FAILED(hr))
        return false ;

    // 输入的客户区矩形范围似乎无用，总是会调用ITextHost::TxGetClientRect来获取区域
    if (FAILED(m_services->OnTxInPlaceActivate(&bound_in_host)))
        return false ;

    LRESULT mask ;
    m_services->TxSendMessage(EM_GETEVENTMASK, 0, 0, &mask) ;
    mask |= ENM_SELCHANGE ;
    m_services->TxSendMessage(EM_SETEVENTMASK, 0, mask, NULL) ;

    m_call_back = new tomEditCallback(this) ;
    SetOLECallback(m_call_back) ;

    // 注册拖拽
    IDropTarget * dt = NULL ;
    if (S_OK == m_services->TxGetDropTarget(&dt))
    {
        RegisterDragDrop(dt) ;
        dt->Release() ;
    }

    return true ;
}