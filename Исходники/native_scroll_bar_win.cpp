 int NativeScrollBarWin::GetPosition() const
 {
     SCROLLINFO si;
     si.cbSize = sizeof(si);
     si.fMask = SIF_POS;
     GetScrollInfo(sb_container_->GetScrollBarHWND(), SB_CTL, &si);
     return si.nPos;
 }