int GiCoreView::drawAll(GiView* view, GiCanvas* canvas)
{
    GcBaseView* aview = impl->_doc->findView(view);
    GiGraphics* gs = aview->graph();
    int n = 0;

    if (aview && gs->beginPaint(canvas)) {
        n = aview->drawAll(*gs);
        gs->endPaint();
    }
    if (!impl->newids.empty()) {
        impl->newids.push_back(0);
    }
    impl->checkDrawAppendEnded();

    return n;
}