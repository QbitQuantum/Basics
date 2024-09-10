//a helper function that can be used in most of the cases. 
//this will enumerate any immediate child controls of the window and copies the repective screen to the memory bitmap
//once it finished copying all the child controls, it will put it back to the screen
void 
DoubleBuffer::PaintWindow()
{
    List                childlist;
    ChildWndHandle*     pchild;
    wyInt32             index;
    RECT                rect;
    wyInt32             isignore;

    pchild = new ChildWndHandle(m_hwnd);
    childlist.Insert(pchild);
    EnumChildWindows(m_hwnd, DoubleBuffer::EnumChidWndProc, (LPARAM)&childlist);
    
    //process it in the reverse Z-order; i.e bottom up
    for(index = childlist.GetCount() - 1, pchild = (ChildWndHandle*)childlist.GetLast(); 
        index > 0; 
        --index, pchild = (ChildWndHandle*)pchild->m_prev)
    {
        isignore = 0;
        
        //check for visibility
        if(IsWindowVisible(pchild->m_hwnd) == FALSE)
        {
            continue;
        }

        if(SendMessage(pchild->m_hwnd, WM_GETDLGCODE, NULL, NULL) == DLGC_STATIC)
        {
            SendMessage(m_hwnd, UM_ISIGNOREHWNDFROMPAINT, (WPARAM)pchild->m_hwnd, (LPARAM)&isignore);
        }

        if(isignore == 0)
        {
            GetWindowRect(pchild->m_hwnd, &rect);
            MapWindowPoints(NULL, m_hwnd, (LPPOINT)&rect, 2);
            CopyScreenToBuffer(&rect);
        }
    }

    CopyBufferToScreen();

    for(pchild = (ChildWndHandle*)childlist.GetFirst(); pchild; pchild = (ChildWndHandle*)childlist.GetFirst())
    {
        childlist.Remove(pchild);
        delete pchild;
    }
}