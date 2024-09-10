/*
   Effect:        Handle any actions relating to the user pressing *down*
                  the left mouse button within the widget.

                  In particular, we need to prepare the widget for moving
                  || sizing. To do this, we remove any drag blobs already
                  present on the widget.

                  We also capture the mouse input, so we can track the
                  movement of the mouse. We will release the capture
                  when the user releases the mouse key.

                  Since the window class style of the widget might not
                  accept double clicks, we will need to compute double
                  clicks ourselves.

                  If someone else has control of the mouse (like the
                  session window || another widget), we won't be getting
                  this mouse message.

   See Also:      WidgetLButtonUp, WidgetLMouseMove.

   Called By:     WidgetWndProc, in response to WM_LBUTTONDOWN messages.
                  LayoutWndProc, in response to WM_LBUTTONDOWN messages
                  when the mouse is over a drag blob.
*/
void WidgetLButtonDown(HWND hWnd, int nDragMode, POINT ptScreen)
{
    RECT rcParentScreen;
    HWND hWndParent, hWndPrev;
    HDC hDC;

    CurrentWidgetInfo.ptPrev = ptScreen;

    hWndParent = GetParent(hWnd);
    CurrentWidgetInfo.nDragMode = nDragMode;
    hDC = GetDC(hWndParent);

    /* Erase the drag blobs from the current widget. The blobs will */
    /* be repainted in WidgetButtonUp after the user finishes dragging */
    /* || sizing. */

    GetWindowRect(hWnd, &CurrentWidgetInfo.rcPrevDots);
    GetWindowRect(hWnd, &CurrentWidgetInfo.rcPrev);

    hWndPrev = CurrentWidgetInfo.hWnd;
    CurrentWidgetInfo.bDotsDrawn = FALSE;

    CurrentWidgetInfo.bDotsDrawn = TRUE;

    if (hWnd != CurrentWidgetInfo.hWnd)
    {
        if (KpsSetCurrentWidget(hWnd))
        {
            if (IsWindow(hWndPrev))
            {
                if (KpsIsAWidget(hWndPrev))
                {
                    InvalidateRect(hWndPrev, NULL, TRUE);
                    UpdateWindow(hWndPrev);
                }
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }

    if (!CurrentWidgetInfo.bCapture)
    {
        SetCapture(hWnd);
        GetClientRect(hWndParent, &rcParentScreen);
        KpsClientRectToScreen(hWndParent, &rcParentScreen);
        ClipCursor(&rcParentScreen);
        CurrentWidgetInfo.bCapture = TRUE;
    }

    ReleaseDC(hWndParent, hDC);

    /* Clear out the rectangle, indicating there is nothing to erase! */
    SetRectEmpty(&rcPrev);
}