CControlBar * CExtMiniDockFrameWnd::GetControlBar()
{
CWnd* pTempWnd = GetWindow( GW_CHILD );
    if( pTempWnd == NULL )
        return NULL;
	pTempWnd = pTempWnd->GetWindow( GW_CHILD );
    if( pTempWnd == NULL )
        return NULL;
    if( !pTempWnd->IsKindOf( RUNTIME_CLASS(CControlBar) ) )
        return NULL;
    return reinterpret_cast < CControlBar * >( pTempWnd );
}