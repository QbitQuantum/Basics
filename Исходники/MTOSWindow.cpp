bool MTOSWindow::message(MTCMessage &msg)
{
    int wm,delta;
    MTPoint p;
    void *rgn;

    if (msg.msg==MTCM_POSCHANGED) {
        rgn = parent->dsk->getvisiblergn(false);
        offsetrgn(rgn,-left-parent->box,-top-parent->boy);
        p.x = left;
        p.y = top;
        parent->toscreen(p);
        SetWindowRgn(wnd,(HRGN)rgn,true);
        MoveWindow(wnd,p.x,p.y,width,height,true);
        return true;
    };
    if (compat) {
        if (msg.msg==MTCM_ACTIVE) {
            active = (msg.param1!=0);
            if (msg.param1) {
                ShowWindow(wnd,SW_NORMAL);
            }
            else {
                BitBlt(dc,0,0,width,height,GetDC(wnd),0,0,SRCCOPY);
                ShowWindow(wnd,SW_HIDE);
            };
        };
        return MTControl::message(msg);
    };
    switch (msg.msg) {
    /*	case MTCM_POSCHANGED:
    		rgn = parent->dsk->getvisiblergn(false);
    		offsetrgn(rgn,-left-parent->box,-top-parent->boy);
    		p.x = left;
    		p.y = top;
    		parent->toscreen(p);
    		SetWindowRgn(wnd,(HRGN)rgn,false);
    		MoveWindow(wnd,p.x,p.y,width,height,true);
    		break;*/
    case MTCM_MOUSEMOVE:
        SendMessage(wnd,WM_MOUSEMOVE,lastwparam,msg.x|(msg.y<<16));
        break;
    case MTCM_MOUSEDOWN:
        if (msg.button==DB_LEFT) wm = WM_LBUTTONDOWN;
        else if (msg.button==DB_RIGHT) wm = WM_RBUTTONDOWN;
        else wm = WM_MBUTTONDOWN;
        if (msg.buttons & DB_DOUBLE) {
            SendMessage(wnd,wm,lastwparam,msg.x|(msg.y<<16));
            if (msg.button==DB_LEFT) wm = WM_LBUTTONDBLCLK;
            else if (msg.button==DB_RIGHT) wm = WM_RBUTTONDBLCLK;
            else wm = WM_MBUTTONDBLCLK;
        };
        SendMessage(wnd,wm,lastwparam,msg.x|(msg.y<<16));
        break;
    case MTCM_MOUSEUP:
        if (msg.button==DB_LEFT) wm = WM_LBUTTONUP;
        else if (msg.button==DB_RIGHT) wm = WM_RBUTTONUP;
        else wm = WM_MBUTTONUP;
        SendMessage(wnd,wm,lastwparam,msg.x|(msg.y<<16));
        break;
    case MTCM_MOUSEWHEEL:
        delta = msg.param3*40;
        SendMessage(wnd,0x020A,lastwparam,lastlparam);
        break;
    case MTCM_CHAR:
        SendMessage(wnd,WM_CHAR,lastwparam,lastlparam);
        break;
    case MTCM_KEYDOWN:
        SendMessage(wnd,WM_KEYDOWN,lastwparam,lastlparam);
        break;
    case MTCM_KEYUP:
        SendMessage(wnd,WM_KEYUP,lastwparam,lastlparam);
        break;
    };
    return MTControl::message(msg);
}