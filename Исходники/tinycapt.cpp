//
/// Paints a blank button.
//
void
TTinyCaption::PaintButton(TDC& dc, TRect& r, bool pressed)
{
    TBrush winFrameBr(TColor::SysWindowFrame);
//  dc.OWLFastWindowFrame(winFrameBr, r, 1, 1);
    dc.FrameRect(r, winFrameBr);

    r.Inflate(-1,-1);
    dc.TextRect(r, TColor::Sys3dFace);
    if (r.Width() > 4 && r.Height() > 4) {
        if (pressed) {
            dc.TextRect(r.left, r.top, r.right, r.top+1, TColor::Sys3dShadow);
            dc.TextRect(r.left, r.top+1, r.left+1, r.bottom, TColor::Sys3dShadow);
        }
        else {
            dc.TextRect(r.left, r.top, r.right-1, r.top+1, TColor::Sys3dHilight);
            dc.TextRect(r.left, r.top+1, r.left+1, r.bottom-1, TColor::Sys3dHilight);
            dc.TextRect(r.right-1, r.top+1, r.right, r.bottom, TColor::Sys3dShadow);
            dc.TextRect(r.left+1, r.bottom-1, r.right-1, r.bottom, TColor::Sys3dShadow);
        }
    }
}