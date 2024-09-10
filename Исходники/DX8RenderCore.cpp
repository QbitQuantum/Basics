//---------------------------------------------------------------------
// Function:    CreateRenderContext
// Description: Function to create a context in which to render to
// Parameters:  hWnd = windows handle for rendering context
//              name = name of the rendering context
//              left = left position inside window
//              top = top       "        "      "
//              width = width   "        "      "
//              height = height "        "      "
//              bpp = bits per pixel of rendering context
//              depth = Z-Buffer depth
//              stencil = Z-Stencil bits
//              fullscreen = whether window is full screen or not
//              parent = parents rendering context if available
// Returns:     TRUE, if successful
//---------------------------------------------------------------------
BOOL CDX8RenderCore::CreateRenderContext(HWND hWnd, LPCSTR name, DWORD left,
                              DWORD top, DWORD width, DWORD height, DWORD bpp, DWORD depth,
                              DWORD stencil, BOOL fullscreen, CRenderContext *parent)
{
    CDX8RenderContext *newCtx;

    // if parent is null then we have to have an hWnd
    if (parent == NULL)
    {
        // we have to have a valid window
        if (!IsWindow(hWnd))
        {
            m_LastError = ERROR_INVALID_WINDOW_HANDLE;
            gLogger->Print(_T("CreateRenderContext: Invalid Window handle specified"));
            return FALSE;
        }
    }
    else
    {
        // if we don't have a valid window, default to parents.
        if (!IsWindow(hWnd))
        {
            hWnd = parent->GetParentHwnd();
        }
    }

    // create a new DX8 Render context.
    newCtx = new CDX8RenderContext(m_pD3D, hWnd, name, left, top, width, height, bpp,
                                    depth, stencil, fullscreen, parent);

    if (newCtx == NULL)
    {
        m_LastError = ERROR_NOT_ENOUGH_MEMORY;
        gLogger->Print(_T("CreateRenderContext: Out of memory allocating CDX8RenderContext"));
        return FALSE;
    }

    if (newCtx->GetLastError() != D3D_OK)
    {
        gLogger->Print(_T("CreateRenderContext: Failed, see log file"));
        return FALSE;
    }

    // top level parents get saved here
    if (parent == NULL)
    {
        // what the hell?
        DWORD nContexts = m_RenderContexts.size();

        m_RenderContexts.insert(MAPHWNDRC::value_type(hWnd, newCtx));
        // and save into context list
//        m_RenderContexts[hWnd] = newCtx;
        if (nContexts != 0)
        {
            return FALSE;
        }
    }
    else
    {
        parent->AddChild(newCtx);
    }

    return TRUE;
}