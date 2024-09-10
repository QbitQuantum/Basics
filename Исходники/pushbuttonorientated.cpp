QSize PushButtonOrientated::sizeHint() const
{
    QSize size = QPushButton::sizeHint();

    if (m_orientation == Qt::Vertical) {
        size.transpose();
    }

    return size;
}