SplitterCollapser::SplitterCollapser(QSplitter *splitter, QWidget *widget)
    : QToolButton(),
      d(new SplitterCollapserPrivate)
{
    d->q = this;

    // We do not want our collapser to be added as a regular widget in the
    // splitter!
    setAttribute(Qt::WA_NoChildEventsForParent);

    d->mOpacityTimeLine = new QTimeLine(TIMELINE_DURATION, this);
    d->mOpacityTimeLine->setFrameRange(int(MINIMUM_OPACITY * 1000), 1000);
    connect(d->mOpacityTimeLine, SIGNAL(valueChanged(qreal)), SLOT(update()));

    d->mWidget = widget;
    d->mWidget->installEventFilter(this);

    qApp->installEventFilter(this);

    d->mSplitter = splitter;
    setParent(d->mSplitter);

    if (splitter->indexOf(widget) < splitter->count() / 2) {
        d->mDirection = LTR;
    } else {
        d->mDirection = RTL;
    }
    if (splitter->orientation() == Qt::Vertical) {
        // FIXME: Ugly!
        d->mDirection = static_cast<Direction>(int(d->mDirection) + int(TTB));
    }

    connect(this, SIGNAL(clicked()), SLOT(slotClicked()));

    show();
}