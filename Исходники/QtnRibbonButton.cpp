QSize RibbonButton::sizeHint() const
{
    ensurePolished();

    int w = 0, h = 0;
    QStyleOptionToolButton opt;
    initStyleOption(&opt);

    QString textButton = text();

    if (!textButton.isEmpty() && (bool)style()->styleHint((QStyle::StyleHint)RibbonStyle::SH_RibbonItemUpperCase, 0, this))
        textButton = textButton.toUpper();

    QFontMetrics fm = fontMetrics();
    if (opt.toolButtonStyle != Qt::ToolButtonTextOnly)
    {
        QSize icon = opt.iconSize;
        QAction* action = defaultAction();
        if (action && !action->icon().isNull())
            icon = action->icon().actualSize(QSize(32,32));
        w = icon.width();
        h = icon.height();
    }

    bool indicatorCenter = false;
    QToolButton::ToolButtonPopupMode mode = QToolButton::popupMode();
    if (opt.toolButtonStyle != Qt::ToolButtonIconOnly)
    {
        if (opt.toolButtonStyle == Qt::ToolButtonTextUnderIcon)
        {
            QString strFirstRow, strSecondRow;
            CommonStyle::splitString(textButton, strFirstRow, strSecondRow);

            QSize textFirstSize;
            if (!strFirstRow.isEmpty())
                textFirstSize = fm.size(Qt::TextShowMnemonic, strFirstRow);

            if (!strSecondRow.isEmpty())
            {
                QSize textSecondSize = fm.size(Qt::TextShowMnemonic, strSecondRow);
                textFirstSize.setWidth(qMax(textFirstSize.width(), textSecondSize.width()));
            }

            indicatorCenter = strSecondRow.isEmpty() && opt.features & QStyleOptionToolButton::HasMenu;

            h = style()->pixelMetric((QStyle::PixelMetric)RibbonStyle::PM_RibbonHeightGroup, 0, this);

            // if the text is more than icon
            if (textFirstSize.width() > w)
                w = textFirstSize.width();
            // add pixel
            w += mode == MenuButtonPopup || mode == QToolButton::InstantPopup ? 4 : 10;
        } 
        else
        {
            QSize textSize = fm.size(Qt::TextShowMnemonic, textButton);
            textSize.setWidth(textSize.width() + fm.width(QLatin1Char(' '))*2);
            h = style()->pixelMetric((QStyle::PixelMetric)RibbonStyle::PM_RibbonHeightGroup, 0, 0)/3;

            if (opt.toolButtonStyle == Qt::ToolButtonTextBesideIcon) 
            {
                w += 3 + textSize.width();
                if (mode != InstantPopup)
                    w += 3;

                if (textSize.height() > h)
                   h = textSize.height();
            } 
            else 
                w = textSize.width() + 3;
        }
    }
    else 
    {
        h = style()->pixelMetric((QStyle::PixelMetric)RibbonStyle::PM_RibbonHeightGroup, 0, 0)/3;
        w = h;
    }

    opt.rect.setSize(QSize(w, h)); // PM_MenuButtonIndicator depends on the height

    if ((mode== MenuButtonPopup || mode == QToolButton::InstantPopup) && !indicatorCenter)
        w += style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &opt, this);

    return QSize(w, h).expandedTo(QApplication::globalStrut());
}