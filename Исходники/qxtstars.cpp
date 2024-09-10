/*!
    \reimp
 */
QSize QxtStars::minimumSizeHint() const
{
    QSize size = qxt_d().getStarSize();
    size.rwidth() *= maximum() - minimum();
    if (orientation() == Qt::Vertical)
        size.transpose();
    return size;
}