QSize toRotatingButton::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    if (rotate & VERTICAL_MASK)
        size.transpose();

    return size;
}