void QGraphicsMozView::forceViewActiveFocus()
{
    QGraphicsItem *parent = parentItem();
    while (parent) {
        if (parent->flags() & QGraphicsItem::ItemIsFocusScope)
            parent->setFocus(Qt::OtherFocusReason);
        parent = parent->parentItem();
    }

    setFocus(Qt::OtherFocusReason);
    if (d->mViewInitialized) {
        d->mView->SetIsActive(true);
    }
}