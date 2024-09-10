Win32Window::~Win32Window()
{
    Win32Factory *pFactory = (Win32Factory*)Win32Factory::instance( getIntf() );
    pFactory->m_windowMap[m_hWnd] = NULL;

    if( m_hWnd )
    {
        if( m_dragDrop )
        {
            // Remove the window from the list of drop targets
            RevokeDragDrop( m_hWnd );
            m_pDropTarget->Release();
        }

        DestroyWindow( m_hWnd );
    }
}