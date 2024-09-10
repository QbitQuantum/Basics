int SHotKeyCtrl::OnCreate( LPVOID )
{
    int nRet=__super::OnCreate(NULL);
    if(nRet!=0) return nRet;
    
    CAutoRefPtr<IRenderTarget> pRT;
    GETRENDERFACTORY->CreateRenderTarget(&pRT,0,0);
    BeforePaintEx(pRT);
    m_curFont=(IFont*)pRT->GetCurrentObject(OT_FONT);
    return 0;
}