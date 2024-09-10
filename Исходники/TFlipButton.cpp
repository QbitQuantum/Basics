QSize TFlipButton::minimumSizeHint() const
{
    QSize size = QPushButton::minimumSizeHint();
    if (mOrientation == Qt::Vertical) {
        size.transpose();
    }
    return size;
}