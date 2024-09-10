//锁定鼠标到某一个范围
void    DesignerHook::MouseLock(TControl* Sender)
{
    TRect   Rect;   
    SetCaptureControl(Sender);
    GetClipCursor(&MouseRect_);
    if(NULL == Sender->Parent){
        return;
    }
    Rect=  Sender->Parent->ClientRect;
    //Rect = Sender->Parent->ClientToScreen(Rect);
    TPoint  PtTopLeft,PtBottomRight;
    PtTopLeft.x = Rect.Left;
    PtTopLeft.y = Rect.Top;
    PtTopLeft =  Sender->Parent->ClientToScreen(PtTopLeft);
    Rect.Top= PtTopLeft.y;
    Rect.Left= PtTopLeft.x;

    PtBottomRight.x = Rect.right;
    PtBottomRight.y = Rect.bottom;
    PtBottomRight =  Sender->Parent->ClientToScreen(PtBottomRight);
    Rect.bottom= PtBottomRight.y;
    Rect.right= PtBottomRight.x;

    ClipCursor(&Rect); //把鼠标锁定在固定区?
}