bool StGLMenu::stglInit() {
    myWidth = 0;
    myIsInitialized = StGLWidget::stglInit();
    if(!myIsInitialized) {
        return false;
    }
    int aMarginLeft = 0;
    for(StGLWidget* aChild = getChildren()->getStart(); aChild != NULL; aChild = aChild->getNext()) {
        StGLMenuItem* anItem = (StGLMenuItem* )aChild;
        aMarginLeft = stMax(aMarginLeft, anItem->getMargins().left);
        int anItemW = anItem->getMargins().left + anItem->computeTextWidth() + anItem->getMargins().right;
        if(myOrient == MENU_HORIZONTAL) {
            anItem->changeRectPx().moveLeftTo(myWidth);
            anItem->changeRectPx().right() = anItem->getRectPx().left() + anItemW;
            anItem->setTextWidth(anItemW - anItem->getMargins().left);
            myWidth += anItemW;
        } else {
            myWidth = stMax(myWidth, anItemW);
        }
        if(anItem->getSubMenu() != NULL) {
            if(myOrient == MENU_HORIZONTAL) {
                anItem->getSubMenu()->changeRectPx().moveTopLeftTo(anItem->getRectPxAbsolute().left(), anItem->getRectPxAbsolute().bottom());
            } else if(myOrient == MENU_VERTICAL
                   || myOrient == MENU_VERTICAL_COMPACT) {
                anItem->getSubMenu()->changeRectPx().moveTopLeftTo(anItem->getRectPxAbsolute().right() - myRoot->scale(10),
                                                                   anItem->getRectPxAbsolute().top());
            }
        }
    }
    StGLWidget* aChildLast = getChildren()->getLast();
    if(aChildLast != NULL) {
        changeRectPx().right()  = getRectPx().left() + aChildLast->getRectPx().right();
        changeRectPx().bottom() = getRectPx().top()  + aChildLast->getRectPx().bottom();
    }
    int aWidth = stMax(myWidthMin, myWidth);
    if(myOrient == MENU_VERTICAL
    || myOrient == MENU_VERTICAL_COMPACT) {
        changeRectPx().right() = getRectPx().left() + aWidth;
        int anItemCount = 0;
        for(StGLWidget* aChild = getChildren()->getStart(); aChild != NULL; aChild = aChild->getNext(), ++anItemCount) {
            StGLMenuItem* anItem = (StGLMenuItem* )aChild;
            anItem->changeRectPx().moveTopTo(anItemCount * myItemHeight);
            anItem->changeRectPx().right() = anItem->getRectPx().left() + aWidth;
            anItem->setTextWidth(aWidth);
            if(anItem->getSubMenu() != NULL) {
                anItem->getSubMenu()->changeRectPx().moveTopLeftTo(getRectPxAbsolute().right() - myRoot->scale(10),
                                                                   anItem->getRectPxAbsolute().top());
            }
        }
        changeRectPx().bottom() = getRectPx().top() + anItemCount * myItemHeight;
    }

    // already initialized?
    if(myVertexBuf.isValid()) {
        // synchronize menu items visibility
        setOpacity(myOpacity, true);
        return true;
    }

    stglResize();
    return myIsInitialized;
}