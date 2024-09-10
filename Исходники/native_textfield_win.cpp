 void NativeTextfieldWin::OnContextMenu(HWND window, const gfx::Point& point)
 {
     POINT p = point.ToPOINT();
     if(p.x==-1 || p.y==-1)
     {
         GetCaretPos(&p);
         MapWindowPoints(HWND_DESKTOP, &p, 1);
     }
     BuildContextMenu();
     context_menu_->RunContextMenuAt(gfx::Point(p));
 }