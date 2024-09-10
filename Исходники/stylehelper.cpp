void StyleHelper::apply()
{
    Preferences *preferences = Preferences::instance();

    QString desiredStyle;
    QPalette desiredPalette;

    switch (preferences->applicationStyle()) {
    default:
    case Preferences::SystemDefaultStyle:
        desiredStyle = defaultStyle();
        desiredPalette = defaultPalette();
        break;
    case Preferences::FusionStyle:
        desiredStyle = QLatin1String("fusion");
        desiredPalette = createPalette(preferences->baseColor(),
                                       preferences->selectionColor());
        break;
    case Preferences::TiledStyle:
        desiredStyle = QLatin1String("tiled");
        desiredPalette = createPalette(preferences->baseColor(),
                                       preferences->selectionColor());
        break;
    }

    if (QApplication::style()->objectName() != desiredStyle) {
        QStyle *style;

        if (desiredStyle == QLatin1String("tiled")) {
            style = QStyleFactory::create(QLatin1String("fusion"));
            style = new TiledProxyStyle(style);
        } else {
            style = QStyleFactory::create(desiredStyle);
        }

        QApplication::setStyle(style);
    }

    if (QApplication::palette() != desiredPalette)
        QApplication::setPalette(desiredPalette);

    emit styleApplied();
}