void FoundCountIcon::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    // Get access to basket pointer
    BasketListViewItem* basketInTree = m_basketTree->getBasketInTree(index);
    if (basketInTree == NULL)
        return;

    const int BASKET_ICON_SIZE = 16; // [replace with m_basketTree->iconSize()]
    const int MARGIN = 1;

    BasketScene* basket = basketInTree->basket();


    // If we are filtering all baskets, and are effectively filtering on something:
    bool showLoadingIcon = false;
    bool showEncryptedIcon = false;
    QPixmap countPixmap;
    bool showCountPixmap = Global::bnpView->isFilteringAllBaskets() &&
        Global::bnpView->currentBasket()->decoration()->filterBar()->filterData().isFiltering;
    if (showCountPixmap) {
        showLoadingIcon = (!basket->isLoaded() && !basket->isLocked()) || basketInTree->haveHiddenChildsLoading();
        showEncryptedIcon = basket->isLocked() || basketInTree->haveHiddenChildsLocked();
        bool childrenAreLoading = basketInTree->haveHiddenChildsLoading() || basketInTree->haveHiddenChildsLocked();

        countPixmap = foundCountPixmap(!basket->isLoaded(), basket->countFounds(), childrenAreLoading,
                                       basketInTree->countHiddenChildsFound(), m_basketTree->font(), option.rect.height() - 2 * MARGIN);
    }
    int effectiveWidth = option.rect.right() -
        (countPixmap.isNull() ? 0 : countPixmap.width() + MARGIN) -
        (showLoadingIcon || showEncryptedIcon ? BASKET_ICON_SIZE + MARGIN : 0);


    bool drawRoundRect = basket->backgroundColorSetting().isValid() || basket->textColorSetting().isValid();

    // Draw the rounded rectangle:
    if (drawRoundRect) {
        QPixmap roundRectBmp;
        QColor background = basket->backgroundColor();
        int textWidth = m_basketTree->fontMetrics().width(basketInTree->text(/*column=*/0));
        int iconTextMargin = m_basketTree->style()->pixelMetric(QStyle::PM_FocusFrameHMargin); ///< Space between icon and text


        // Don't forget to update the key computation if parameters
        // affecting the rendering logic change
        QString key = QString("BLIRR::%1.%2.%3.%4")
                    .arg(option.rect.width())
                    .arg(option.rect.size().height())
                    .arg(textWidth)
                    .arg(background.rgb());


        if (QPixmap* cached = QPixmapCache::find(key)) {
            // Qt's documentation recommends copying the pointer
            // into a QPixmap immediately
            roundRectBmp = *cached;
        } else {
            // Draw first time

            roundRectBmp = QPixmap(option.rect.size());
            roundRectBmp.fill(Qt::transparent);

            QPainter brushPainter(&roundRectBmp);

            int cornerR = option.rect.height()/2 - MARGIN;

            QRect roundRect(0, MARGIN,
                            BASKET_ICON_SIZE + iconTextMargin + textWidth + 2*cornerR,
                            option.rect.height() - 2*MARGIN);


            brushPainter.setPen(background);
            brushPainter.setBrush(background);
            brushPainter.setRenderHint(QPainter::Antialiasing);
            brushPainter.drawRoundedRect(roundRect, cornerR, cornerR);

            QPixmapCache::insert(key, roundRectBmp);
        }


        basketInTree->setBackground(0, QBrush(roundRectBmp));
        basketInTree->setForeground(0, QBrush(basket->textColor()));
    }
    //end if drawRoundRect

    // Render icons on the right
    int y = option.rect.center().y() - BASKET_ICON_SIZE/2;

    if (!countPixmap.isNull()) {
        painter->drawPixmap(effectiveWidth, y, countPixmap);
        effectiveWidth += countPixmap.width() + MARGIN;
    }
    if (showLoadingIcon) {
        QPixmap icon = KIconLoader::global()->loadIcon(IconNames::LOADING, KIconLoader::NoGroup, BASKET_ICON_SIZE);
        painter->drawPixmap(effectiveWidth, y, icon);
        effectiveWidth += BASKET_ICON_SIZE + MARGIN;
    }
    if (showEncryptedIcon && !showLoadingIcon) {
        QPixmap icon = KIconLoader::global()->loadIcon(IconNames::LOCKED, KIconLoader::NoGroup, BASKET_ICON_SIZE);
        painter->drawPixmap(effectiveWidth, y, icon);
    }
}