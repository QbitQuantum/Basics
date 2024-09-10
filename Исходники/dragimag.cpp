// Begin drag
bool wxDragImage::BeginDrag(const wxPoint& hotspot, wxWindow* window, bool fullScreen, wxRect* rect)
{
    wxASSERT_MSG( (m_hImageList != 0), wxT("Image list must not be null in BeginDrag."));
    wxASSERT_MSG( (window != 0), wxT("Window must not be null in BeginDrag."));

    m_fullScreen = fullScreen;
    if (rect)
        m_boundingRect = * rect;

    bool ret = (ImageList_BeginDrag(GetHimageList(), 0, hotspot.x, hotspot.y) != 0);

    if (!ret)
    {
        wxFAIL_MSG( wxT("BeginDrag failed.") );

        return false;
    }

    if (m_cursor.Ok())
    {
#if wxUSE_SIMPLER_DRAGIMAGE
        m_oldCursor = window->GetCursor();
        window->SetCursor(m_cursor);
#else
        if (!m_hCursorImageList)
        {
#ifndef SM_CXCURSOR
            // Smartphone may not have these metric symbol
            int cxCursor = 16;
            int cyCursor = 16;
#else
            int cxCursor = ::GetSystemMetrics(SM_CXCURSOR);
            int cyCursor = ::GetSystemMetrics(SM_CYCURSOR);
#endif
            m_hCursorImageList = (WXHIMAGELIST) ImageList_Create(cxCursor, cyCursor, ILC_MASK, 1, 1);
        }

        // See if we can find the cursor hotspot
        wxPoint curHotSpot(hotspot);

        // Although it seems to produce the right position, when the hotspot goeos
        // negative it has strange effects on the image.
        // How do we stop the cursor jumping right and below of where it should be?
#if 0
        ICONINFO iconInfo;
        if (::GetIconInfo((HICON) (HCURSOR) m_cursor.GetHCURSOR(), & iconInfo) != 0)
        {
            curHotSpot.x -= iconInfo.xHotspot;
            curHotSpot.y -= iconInfo.yHotspot;
        }
#endif
        //wxString msg;
        //msg.Printf("Hotspot = %d, %d", curHotSpot.x, curHotSpot.y);
        //wxLogDebug(msg);

        // First add the cursor to the image list
        HCURSOR hCursor = (HCURSOR) m_cursor.GetHCURSOR();
        int cursorIndex = ImageList_AddIcon((HIMAGELIST) m_hCursorImageList, (HICON) hCursor);

        wxASSERT_MSG( (cursorIndex != -1), wxT("ImageList_AddIcon failed in BeginDrag."));

        if (cursorIndex != -1)
        {
            ImageList_SetDragCursorImage((HIMAGELIST) m_hCursorImageList, cursorIndex, curHotSpot.x, curHotSpot.y);
        }
#endif
    }

#if !wxUSE_SIMPLER_DRAGIMAGE
    if (m_cursor.Ok())
        ::ShowCursor(FALSE);
#endif

    m_window = window;

    ::SetCapture(GetHwndOf(window));

    return true;
}