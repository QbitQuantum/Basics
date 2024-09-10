//@SuppressLint("InlinedApi")
void ActivityContentVideoViewClient::SetSystemUiVisibility(
    /* [in] */ IView* view,
    /* [in] */ Boolean enterFullscreen)
{
    AutoPtr<IWindowManager> wm;
    mActivity->GetWindow((IWindowManager**)&wm);
    if (enterFullscreen) {
        wm->SetFlags(
                IWindowManagerLayoutParams::FLAG_FULLSCREEN,
                IWindowManagerLayoutParams::FLAG_FULLSCREEN);
    }
    else {
        wm->ClearFlags(IWindowManagerLayoutParams::FLAG_FULLSCREEN);
    }

    if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT) {
        return;
    }

    Int32 systemUiVisibility;
    view->GetSystemUiVisibility(&systemUiVisibility);
    Int32 flags = IView::SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
            | IView::SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
            | IView::SYSTEM_UI_FLAG_HIDE_NAVIGATION
            | IView::SYSTEM_UI_FLAG_FULLSCREEN
            | IView::SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
    if (enterFullscreen) {
        systemUiVisibility |= flags;
    }
    else {
        systemUiVisibility &= ~flags;
    }

    view->SetSystemUiVisibility(systemUiVisibility);
}