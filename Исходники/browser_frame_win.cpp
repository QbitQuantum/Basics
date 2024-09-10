void BrowserFrameWin::UpdateDWMFrame()
{
    // Nothing to do yet, or we're not showing a DWM frame.
    if(!GetWidget()->client_view() || !browser_frame_->ShouldUseNativeFrame())
    {
        return;
    }

    MARGINS margins = { 0 };
    if(browser_view_->IsBrowserTypeNormal())
    {
        // In fullscreen mode, we don't extend glass into the client area at all,
        // because the GDI-drawn text in the web content composited over it will
        // become semi-transparent over any glass area.
        if(!IsMaximized() && !IsFullscreen())
        {
            margins.cxLeftWidth = kClientEdgeThickness + 1;
            margins.cxRightWidth = kClientEdgeThickness + 1;
            margins.cyBottomHeight = kClientEdgeThickness + 1;
            margins.cyTopHeight = kClientEdgeThickness + 1;
        }
        // In maximized mode, we only have a titlebar strip of glass, no side/bottom
        // borders.
        if(!browser_view_->IsFullscreen())
        {
            gfx::Rect tabstrip_bounds(
                browser_frame_->GetBoundsForTabStrip(browser_view_->tabstrip()));
            margins.cyTopHeight = tabstrip_bounds.bottom() + kDWMFrameTopOffset;
        }
    }
    else
    {
        // For popup and app windows we want to use the default margins.
    }
    DwmExtendFrameIntoClientArea(GetNativeView(), &margins);
}