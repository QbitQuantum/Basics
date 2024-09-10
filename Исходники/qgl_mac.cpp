/****************************************************************************
  Hacks to glue AGL to an HIView
  ***************************************************************************/
QRegion qt_mac_get_widget_rgn(const QWidget *widget)
{
    if(!widget->isVisible() || widget->isMinimized())
        return QRegion();
    const QRect wrect = QRect(qt_mac_posInWindow(widget), widget->size());
    if(!wrect.isValid())
        return QRegion();

    RgnHandle macr = qt_mac_get_rgn();
    GetControlRegion((HIViewRef)widget->winId(), kControlStructureMetaPart, macr);
    OffsetRgn(macr, wrect.x(), wrect.y());
    QRegion ret = qt_mac_convert_mac_region(macr);

    QPoint clip_pos = wrect.topLeft();
    for(const QWidget *last_clip = 0, *clip = widget; clip; last_clip = clip, clip = clip->parentWidget()) {
        if(clip != widget) {
            GetControlRegion((HIViewRef)clip->winId(), kControlStructureMetaPart, macr);
            OffsetRgn(macr, clip_pos.x(), clip_pos.y());
            ret &= qt_mac_convert_mac_region(macr);
        }
        const QObjectList &children = clip->children();
        for(int i = children.size()-1; i >= 0; --i) {
            if(QWidget *child = qobject_cast<QWidget*>(children.at(i))) {
                if(child == last_clip)
                    break;

                // This check may seem weird, but when we are using a unified toolbar
                // The widget is actually being owned by that toolbar and not by Qt.
                // This means that the geometry it reports will be wrong
                // and will accidentally cause problems when calculating the region
                // So, it is better to skip these widgets since they aren't the hierarchy
                // anyway.
                if (HIViewGetSuperview(HIViewRef(child->winId())) != HIViewRef(clip->winId()))
                    continue;

                if(child->isVisible() && !child->isMinimized() && !child->isTopLevel()) {
                    const QRect childRect = QRect(clip_pos+child->pos(), child->size());
                    if(childRect.isValid() && wrect.intersects(childRect)) {
                        GetControlRegion((HIViewRef)child->winId(), kControlStructureMetaPart, macr);
                        OffsetRgn(macr, childRect.x(), childRect.y());
                        ret -= qt_mac_convert_mac_region(macr);
                    }
                }
            }
        }
        if(clip->isWindow())
            break;
        clip_pos -= clip->pos();
    }
    qt_mac_dispose_rgn(macr);
    return ret;
}