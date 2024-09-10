void MButtonView::drawContents(QPainter *painter, const QStyleOptionGraphicsItem *option) const
{
    Q_UNUSED(option);

    Q_D(const MButtonView);
    drawIcon(painter, d->iconRect);
}