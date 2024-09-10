QSize RotationToolButton::sizeHint() const
{
    QSize size;
    size = QToolButton::sizeHint();

    if (rot & Vertical_Mask)
        size.transpose();
    return size;
}