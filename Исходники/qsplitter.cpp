void QSplitter::setOrientation(Qt::Orientation orientation)
{
    Q_D(QSplitter);
    if (d->orient == orientation)
        return;

    if (!testAttribute(Qt::WA_WState_OwnSizePolicy)) {
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy(sp);
        setAttribute(Qt::WA_WState_OwnSizePolicy, false);
    }

    d->orient = orientation;

    for (int i = 0; i < d->list.size(); ++i) {
        QSplitterLayoutStruct *s = d->list.at(i);
        s->handle->setOrientation(orientation);
    }
    d->recalc(isVisible());
}