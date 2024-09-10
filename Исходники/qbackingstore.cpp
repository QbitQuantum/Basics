/*!
    Synchronizes the backing store, i.e. dirty areas are repainted and flushed.
*/
void QWidgetBackingStore::sync()
{
    QTLWExtra *tlwExtra = tlw->d_func()->maybeTopData();
    if (discardSyncRequest(tlw, tlwExtra)) {
        // If the top-level is minimized, it's not visible on the screen so we can delay the
        // update until it's shown again. In order to do that we must keep the dirty states.
        // These will be cleared when we receive the first expose after showNormal().
        // However, if the widget is not visible (isVisible() returns false), everything will
        // be invalidated once the widget is shown again, so clear all dirty states.
        if (!tlw->isVisible()) {
            dirty = QRegion();
            for (int i = 0; i < dirtyWidgets.size(); ++i)
                resetWidget(dirtyWidgets.at(i));
            dirtyWidgets.clear();
            fullUpdatePending = false;
        }
        return;
    }

    const bool updatesDisabled = !tlw->updatesEnabled();
    bool repaintAllWidgets = false;

    const bool inTopLevelResize = tlwExtra->inTopLevelResize;
    const QRect tlwRect(tlw->data->crect);
    const QRect surfaceGeometry(windowSurface->geometry());
    if ((fullUpdatePending || inTopLevelResize || surfaceGeometry.size() != tlwRect.size()) && !updatesDisabled) {
        if (hasStaticContents()) {
            // Repaint existing dirty area and newly visible area.
            const QRect clipRect(0, 0, surfaceGeometry.width(), surfaceGeometry.height());
            const QRegion staticRegion(staticContents(0, clipRect));
            QRegion newVisible(0, 0, tlwRect.width(), tlwRect.height());
            newVisible -= staticRegion;
            dirty += newVisible;
            windowSurface->setStaticContents(staticRegion);
        } else {
            // Repaint everything.
            dirty = QRegion(0, 0, tlwRect.width(), tlwRect.height());
            for (int i = 0; i < dirtyWidgets.size(); ++i)
                resetWidget(dirtyWidgets.at(i));
            dirtyWidgets.clear();
            repaintAllWidgets = true;
        }
    }

    if (inTopLevelResize || surfaceGeometry != tlwRect)
        windowSurface->setGeometry(tlwRect);

    if (updatesDisabled)
        return;

    if (hasDirtyFromPreviousSync)
        dirty += dirtyFromPreviousSync;

    // Contains everything that needs repaint.
    QRegion toClean(dirty);

    // Loop through all update() widgets and remove them from the list before they are
    // painted (in case someone calls update() in paintEvent). If the widget is opaque
    // and does not have transparent overlapping siblings, append it to the
    // opaqueNonOverlappedWidgets list and paint it directly without composition.
    QVarLengthArray<QWidget *, 32> opaqueNonOverlappedWidgets;
    for (int i = 0; i < dirtyWidgets.size(); ++i) {
        QWidget *w = dirtyWidgets.at(i);
        QWidgetPrivate *wd = w->d_func();
        if (wd->data.in_destructor)
            continue;

        // Clip with mask() and clipRect().
        wd->dirty &= wd->clipRect();
        wd->clipToEffectiveMask(wd->dirty);

        // Subtract opaque siblings and children.
        bool hasDirtySiblingsAbove = false;
        // We know for sure that the widget isn't overlapped if 'isMoved' is true.
        if (!wd->isMoved)
            wd->subtractOpaqueSiblings(wd->dirty, &hasDirtySiblingsAbove);
        // Scrolled and moved widgets must draw all children.
        if (!wd->isScrolled && !wd->isMoved)
            wd->subtractOpaqueChildren(wd->dirty, w->rect());

        if (wd->dirty.isEmpty()) {
            resetWidget(w);
            continue;
        }

        const QRegion widgetDirty(w != tlw ? wd->dirty.translated(w->mapTo(tlw, QPoint()))
                                           : wd->dirty);
        toClean += widgetDirty;

#ifndef QT_NO_GRAPHICSVIEW
        if (tlw->d_func()->extra->proxyWidget) {
            resetWidget(w);
            continue;
        }
#endif

        if (!hasDirtySiblingsAbove && wd->isOpaque && !dirty.intersects(widgetDirty.boundingRect())) {
            opaqueNonOverlappedWidgets.append(w);
        } else {
            resetWidget(w);
            dirty += widgetDirty;
        }
    }
    dirtyWidgets.clear();

    fullUpdatePending = false;

    if (toClean.isEmpty()) {
        // Nothing to repaint. However, we might have newly exposed areas on the
        // screen if this function was called from sync(QWidget *, QRegion)), so
        // we have to make sure those are flushed.
        flush();
        return;
    }

#ifndef QT_NO_GRAPHICSVIEW
    if (tlw->d_func()->extra->proxyWidget) {
        updateStaticContentsSize();
        dirty = QRegion();
        const QVector<QRect> rects(toClean.rects());
        for (int i = 0; i < rects.size(); ++i)
            tlw->d_func()->extra->proxyWidget->update(rects.at(i));
        return;
    }
#endif

#ifndef Q_BACKINGSTORE_SUBSURFACES
    BeginPaintInfo beginPaintInfo;
    beginPaint(toClean, tlw, windowSurface, &beginPaintInfo);
    if (beginPaintInfo.nothingToPaint) {
        for (int i = 0; i < opaqueNonOverlappedWidgets.size(); ++i)
            resetWidget(opaqueNonOverlappedWidgets[i]);
        dirty = QRegion();
        return;
    }
#endif

    // Must do this before sending any paint events because
    // the size may change in the paint event.
    updateStaticContentsSize();
    const QRegion dirtyCopy(dirty);
    dirty = QRegion();

    // Paint opaque non overlapped widgets.
    for (int i = 0; i < opaqueNonOverlappedWidgets.size(); ++i) {
        QWidget *w = opaqueNonOverlappedWidgets[i];
        QWidgetPrivate *wd = w->d_func();

        int flags = QWidgetPrivate::DrawRecursive;
        // Scrolled and moved widgets must draw all children.
        if (!wd->isScrolled && !wd->isMoved)
            flags |= QWidgetPrivate::DontDrawOpaqueChildren;
        if (w == tlw)
            flags |= QWidgetPrivate::DrawAsRoot;

        QRegion toBePainted(wd->dirty);
        resetWidget(w);

#ifdef Q_BACKINGSTORE_SUBSURFACES
        QWindowSurface *subSurface = w->windowSurface();
        BeginPaintInfo beginPaintInfo;

        QPoint off = w->mapTo(tlw, QPoint());
        toBePainted.translate(off);
        beginPaint(toBePainted, w, subSurface, &beginPaintInfo, true);
        toBePainted.translate(-off);

        if (beginPaintInfo.nothingToPaint)
            continue;

        if (beginPaintInfo.windowSurfaceRecreated) {
            // Eep the window surface has changed. The old one may have been
            // deleted, in which case we will segfault on the call to
            // painterOffset() below. Use the new window surface instead.
            subSurface = w->windowSurface();
        }

        QPoint offset(tlwOffset);
        if (subSurface == windowSurface)
            offset += w->mapTo(tlw, QPoint());
        else
            offset = static_cast<QWSWindowSurface*>(subSurface)->painterOffset();
        wd->drawWidget(subSurface->paintDevice(), toBePainted, offset, flags, 0, this);

        endPaint(toBePainted, subSurface, &beginPaintInfo);
#else
        QPoint offset(tlwOffset);
        if (w != tlw)
            offset += w->mapTo(tlw, QPoint());
        wd->drawWidget(windowSurface->paintDevice(), toBePainted, offset, flags, 0, this);
#endif
    }

    // Paint the rest with composition.
#ifndef Q_BACKINGSTORE_SUBSURFACES
    if (repaintAllWidgets || !dirtyCopy.isEmpty()) {
        const int flags = QWidgetPrivate::DrawAsRoot | QWidgetPrivate::DrawRecursive;
        tlw->d_func()->drawWidget(windowSurface->paintDevice(), dirtyCopy, tlwOffset, flags, 0, this);
    }

    endPaint(toClean, windowSurface, &beginPaintInfo);
#else
    if (!repaintAllWidgets && dirtyCopy.isEmpty())
        return; // Nothing more to paint.

    QList<QWindowSurface *> surfaceList(subSurfaces);
    surfaceList.prepend(windowSurface);
    const QRect dirtyBoundingRect(dirtyCopy.boundingRect());

    // Loop through all window surfaces (incl. the top-level surface) and
    // repaint those intersecting with the bounding rect of the dirty region.
    for (int i = 0; i < surfaceList.size(); ++i) {
        QWindowSurface *subSurface = surfaceList.at(i);
        QWidget *w = subSurface->window();
        QWidgetPrivate *wd = w->d_func();

        const QRect clipRect = wd->clipRect().translated(w->mapTo(tlw, QPoint()));
        if (!qRectIntersects(dirtyBoundingRect, clipRect))
            continue;

        toClean = dirtyCopy;
        BeginPaintInfo beginPaintInfo;
        beginPaint(toClean, w, subSurface, &beginPaintInfo);
        if (beginPaintInfo.nothingToPaint)
            continue;

        if (beginPaintInfo.windowSurfaceRecreated) {
            // Eep the window surface has changed. The old one may have been
            // deleted, in which case we will segfault on the call to
            // painterOffset() below. Use the new window surface instead.
            subSurface = w->windowSurface();
        }

        int flags = QWidgetPrivate::DrawRecursive;
        if (w == tlw)
            flags |= QWidgetPrivate::DrawAsRoot;
        const QPoint painterOffset = static_cast<QWSWindowSurface*>(subSurface)->painterOffset();
        wd->drawWidget(subSurface->paintDevice(), toClean, painterOffset, flags, 0, this);

        endPaint(toClean, subSurface, &beginPaintInfo);
    }
#endif
}