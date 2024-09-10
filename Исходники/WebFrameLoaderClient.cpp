void WebFrameLoaderClient::transitionToCommittedForNewPage()
{
    Frame* frame = core(m_webFrame);
    ASSERT(frame);

    Page* page = frame->page();
    ASSERT(page);

    bool isMainFrame = frame == page->mainFrame();

/*    if (isMainFrame && frame->view())
        frame->view()->detachFromWindow();*/

    frame->setView(0);

    m_webFrame->updateBackground();

    WebView* webView = m_webFrame->webView();

    FrameView* frameView;
    if (isMainFrame) {
        IntRect rect = webView->frameRect();
        frameView = new FrameView(frame, rect.size());
    } else
        frameView = new FrameView(frame);

    frame->setView(frameView);
    frameView->deref(); // FrameViews are created with a ref count of 1. Release this ref since we've assigned it to frame.

    BalWidget* viewWindow = webView->viewWindow();
    if (viewWindow)
        frameView->setContainingWindow(viewWindow);

    /*if (isMainFrame)
        frameView->attachToWindow();*/

    if (frame->ownerRenderer())
        frame->ownerRenderer()->setWidget(frameView);

    if (HTMLFrameOwnerElement* owner = frame->ownerElement())
        frame->view()->setScrollbarsMode(owner->scrollingMode());
}