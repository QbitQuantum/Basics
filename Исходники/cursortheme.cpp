QPixmap CursorTheme::createIcon() const
{
    int iconSize = QApplication::style()->pixelMetric(QStyle::PM_LargeIconSize);
    int cursorSize = nominalCursorSize(iconSize);
    QSize size = QSize(iconSize, iconSize);

    QPixmap pixmap = createIcon(cursorSize);

    if (!pixmap.isNull())
    {
        // Scale the pixmap if it's larger than the preferred icon size
        if (pixmap.width() > size.width() || pixmap.height() > size.height())
            pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    return pixmap;
}