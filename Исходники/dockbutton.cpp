QSize DockButton::sizeHint() const
{
    QSize hint = QToolButton::sizeHint();
    if (toolBarOrientation(this) == Qt::Vertical) {
        hint.transpose();
    }
    return hint;
}