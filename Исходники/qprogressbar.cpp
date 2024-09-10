void QProgressBar::setOrientation(Qt::Orientation orientation)
{
    Q_D(QProgressBar);
    if (d->orientation == orientation)
        return;
    d->orientation = orientation;
    if (!testAttribute(Qt::WA_WState_OwnSizePolicy)) {
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy(sp);
        setAttribute(Qt::WA_WState_OwnSizePolicy, false);
    }
    d->resetLayoutItemMargins();
    update();
    updateGeometry();
}