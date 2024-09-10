/*************
 * DESCRIPTION:	handles movement of mouse
 *						calls DoMouseMove from mouse.cpp
 * INPUT:			nFlags   Specifies if various flags are set
 *						point    coordinates of mouse cursor
 * OUTPUT:			-
 *************/
void CCamView::OnMouseMove(UINT nFlags, CPoint point)
{
    CPoint pntScreen;
    RECTANGLE r;

    pntScreen = point;
    ClientToScreen(&point);

    if (!bLeftButton)
        return;

    // return when OnMouseMove was caused from SetCursorPos
    if (pntOldCursor == point)
        return;

    if (pDisplay->editmode & EDIT_SELBOX)
    {
        if (pDisplay->boxmode == BOXMODE_RENDERWINDOW)
            pDisplay->GetRenderRect(&r);
        else
        {
            r.left = pDisplay->view->left;
            r.right = pDisplay->view->right;
            r.top = pDisplay->view->top;
            r.bottom = pDisplay->view->bottom;
        }
        pDisplay->DrawSelBox();
        if (pntScreen.x < r.left)
            pDisplay->selbox.right = r.left;
        else
        {
            if (pntScreen.x > r.right)
                pDisplay->selbox.right = r.right;
            else
                pDisplay->selbox.right = pntScreen.x;
        }
        if (pntScreen.y < r.top)
            pDisplay->selbox.bottom = r.top;
        else
        {
            if (pntScreen.y > r.bottom)
                pDisplay->selbox.bottom = r.bottom;
            else
                pDisplay->selbox.bottom = pntScreen.y;
        }
        pDisplay->DrawSelBox();
    }
    else
    {
        if (pDisplay->editmode & EDIT_ACTIVE)
        {
            if (nFlags & (MK_LBUTTON | MK_RBUTTON))
            {
                mouse_data.oldmousex = pntOldCursor.x;
                mouse_data.oldmousey = pntOldCursor.y;
                DoMouseMove(pDisplay, point.x, point.y, &mouse_data);
                //		Invalidate(FALSE);
                Redraw(REDRAW_OBJECTS, mouse_data.changed);

                SetCursorPos(pntOldCursor.x, pntOldCursor.y);

                mouse_data.changed = TRUE;
            }
        }
    }
}