void TabBarWidgetMacStyle::tabLayout(const QStyleOptionTab *pOption,
                                     const QWidget *pWidget, QRect *pTextRect,
                                     QRect *pIconRect) const
{
    // Compute our tab layout
    // Note: adapted from QCommonStylePrivate::tabLayout()...

    Q_ASSERT(pTextRect);
    Q_ASSERT(pIconRect);

    QRect textRect = pOption->rect;
    bool verticalTab =    (pOption->shape == QTabBar::RoundedWest)
                       || (pOption->shape == QTabBar::RoundedEast)
                       || (pOption->shape == QTabBar::TriangularWest)
                       || (pOption->shape == QTabBar::TriangularEast);

    if (verticalTab) {
        textRect.setRect(0, 0, textRect.height(), textRect.width());
    }

    if (!pOption->leftButtonSize.isEmpty()) {
        textRect.adjust(-4, 0, 0, 0);
    }

    int horizontalShift = pixelMetric(QStyle::PM_TabBarTabShiftHorizontal, pOption, pWidget);
    int verticalShift = pixelMetric(QStyle::PM_TabBarTabShiftVertical, pOption, pWidget);
    int horizontalPadding = pixelMetric(QStyle::PM_TabBarTabHSpace, pOption, pWidget)/2;
    int verticalPadding = pixelMetric(QStyle::PM_TabBarTabVSpace, pOption, pWidget)/2;

    if (   (pOption->shape == QTabBar::RoundedSouth)
        || (pOption->shape == QTabBar::TriangularSouth)) {
        verticalShift = -verticalShift;
    }

    textRect.adjust(horizontalPadding, verticalShift-verticalPadding,
                    horizontalShift-horizontalPadding, verticalPadding);

    if ((pOption->state & QStyle::State_Selected) != 0) {
        textRect.setTop(textRect.top()-verticalShift);
        textRect.setRight(textRect.right()-horizontalShift);
    }

    if (!pOption->leftButtonSize.isEmpty()) {
        textRect.setLeft( textRect.left()
                         +(verticalTab?
                               pOption->leftButtonSize.height():
                               pOption->leftButtonSize.width()));
    }

    if (!pOption->rightButtonSize.isEmpty()) {
        textRect.setRight( textRect.right()
                          -(verticalTab?
                                pOption->rightButtonSize.height():
                                pOption->rightButtonSize.width()));
    }

    if (!pOption->icon.isNull()) {
        QSize iconSize = pOption->iconSize;

        if (!iconSize.isValid()) {
            int iconExtent = pixelMetric(QStyle::PM_SmallIconSize);

            iconSize = QSize(iconExtent, iconExtent);
        }

        QSize tabIconSize = pOption->icon.actualSize(iconSize,
                                                     ((pOption->state & QStyle::State_Enabled) != 0)?
                                                         QIcon::Normal:
                                                         QIcon::Disabled,
                                                     ((pOption->state & QStyle::State_Selected) != 0)?
                                                         QIcon::On:
                                                         QIcon::Off);

        tabIconSize = QSize(qMin(tabIconSize.width(), iconSize.width()),
                            qMin(tabIconSize.height(), iconSize.height()));

        *pIconRect = QRect(textRect.left(), textRect.center().y()-tabIconSize.height()/2,
                           tabIconSize.width(), tabIconSize.height());

        if (!verticalTab) {
            *pIconRect = visualRect(pOption->direction, pOption->rect, *pIconRect);
        }

        textRect.setLeft(textRect.left()+tabIconSize.width()+4);
    }

    if (!verticalTab) {
        textRect = visualRect(pOption->direction, pOption->rect, textRect);
    }

    *pTextRect = textRect;
}