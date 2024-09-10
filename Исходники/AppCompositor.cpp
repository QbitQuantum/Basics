void
AppCompositor::updateAppCompositorGeometry()
{
    ILOG_TRACE_W(ILX_APPCOMPOSITOR);
    float w = _zoomFactor * width();
    float h = _zoomFactor * height();

    if (w == 0 || h == 0)
        return;

    AppInfo* info = _instance->appInfo();
    ILOG_DEBUG(ILX_APPCOMPOSITOR, " -> name: %s\n", info->name().c_str());
    ILOG_DEBUG(ILX_APPCOMPOSITOR, " -> w: %f h: %f\n", w, h);
    if (info)
    {
        if (info->appFlags() & APP_NO_MAINWINDOW)
        {
            int i = 0;
            ILOG_DEBUG(ILX_APPCOMPOSITOR, " -> APP_NO_MAINWINDOW - ZoomFactor: %f\n", _zoomFactor);
            // calc bounding box.
            Rectangle bounds;
            for (WidgetList::iterator it = _children.begin(); it != _children.end(); ++it)
            {
                SurfaceView* view = dynamic_cast<SurfaceView*>(*it);
                if (view)
                {
                    int x, y;
                    view->dfbWindow()->GetPosition(view->dfbWindow(), &x, &y);
                    Size s = view->preferredSize();
                    bounds.unite(Rectangle(x, y, s.width(), s.height()));
                }
            }

            // resize
            _hScale = width() < _compositor->getAppGeometry().width() ? w / _compositor->getAppGeometry().width() : 1;
            _vScale =
                    height() < _compositor->getAppGeometry().height() ? h / _compositor->getAppGeometry().height() : 1;
            for (WidgetList::iterator it = _children.begin(); it != _children.end(); ++it)
            {
                SurfaceView* view = dynamic_cast<SurfaceView*>(*it);
                if (view)
                {
                    int x, y;
                    view->dfbWindow()->GetPosition(view->dfbWindow(), &x, &y);
                    Size s = view->preferredSize();
                    view->setGeometry(x * _hScale, y * _vScale, s.width() * _hScale, s.height() * _vScale);
                    ILOG_DEBUG(ILX_APPCOMPOSITOR, "  -> window[%d]: %d, %d - %d x %d\n", i, view->x(), view->y(), view->width(), view->height());
                    ++i;
                }
            }
        } else
        {
            int i = 0;
            ILOG_DEBUG(ILX_APPCOMPOSITOR, " -> APP_WITH_MAINWINDOW - ZoomFactor: %f\n", _zoomFactor);
            for (WidgetList::iterator it = _children.begin(); it != _children.end(); ++it)
            {
                SurfaceView* view = dynamic_cast<SurfaceView*>(*it);
                if (view)
                {
                    if (i == 0)
                    {
                        view->setGeometry((width() - w) / 2, (height() - h) / 2, w, h);
                        ILOG_DEBUG(ILX_APPCOMPOSITOR, "  -> window[%d]: %d, %d - %d x %d\n", i, view->x(), view->y(), view->width(), view->height());
                        // Calculate scaling factors using mainwindow as base
                        Size s = view->preferredSize();
                        _hScale = w / s.width();
                        _vScale = h / s.height();
                        ILOG_DEBUG(ILX_APPCOMPOSITOR, "  -> hScale: %f vScale: %f\n", _hScale, _vScale);
                    } else
                    {
                        int x, y;
                        view->dfbWindow()->GetPosition(view->dfbWindow(), &x, &y);
                        Size s = view->preferredSize();
                        view->setGeometry(x * _hScale, y * _vScale, s.width() * _hScale, s.height() * _vScale);
                        ILOG_DEBUG(ILX_APPCOMPOSITOR, "  -> window[%d]: %d, %d - %d x %d\n", i, view->x(), view->y(), view->width(), view->height());
                    }
                    ++i;
                }
            }
        }
    }
}