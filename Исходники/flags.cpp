const QIcon Flags::getIconWithText(const LayoutUnit& layoutUnit, const KeyboardConfig& keyboardConfig)
{
    QString keySuffix(getPixmapKey(keyboardConfig));
    QString key(layoutUnit.toString() + keySuffix);
    if( iconOrTextMap.contains(key) ) {
        return iconOrTextMap[ key ];
    }

    if( keyboardConfig.indicatorType == KeyboardConfig::SHOW_FLAG ) {
        QIcon icon = getIcon(layoutUnit.layout);
        if( ! icon.isNull() ) {
            iconOrTextMap[ key ] = icon;
            return icon;
        }
    }

    QString layoutText = Flags::getShortText(layoutUnit, keyboardConfig);

    const QSize TRAY_ICON_SIZE(21, 14);
    QPixmap pixmap = QPixmap(TRAY_ICON_SIZE);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
//	p.setRenderHint(QPainter::SmoothPixmapTransform);
//	p.setRenderHint(QPainter::Antialiasing);

    if( keyboardConfig.indicatorType == KeyboardConfig::SHOW_LABEL_ON_FLAG ) {
        QIcon iconf = createIcon(layoutUnit.layout);
        iconf.paint(&painter, painter.window(), Qt::AlignCenter);
    }

    drawLabel(painter, layoutText, keyboardConfig.isFlagShown());

    painter.end();

    QIcon icon(pixmap);
    iconOrTextMap[ key ] = icon;

    return icon;
}