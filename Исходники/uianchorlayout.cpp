bool UIAnchorLayout::updateWidget(const UIWidgetPtr& widget, const UIAnchorGroupPtr& anchorGroup, UIWidgetPtr first)
{
    UIWidgetPtr parentWidget = getParentWidget();
    if(!parentWidget)
        return false;

    if(first == widget) {
        g_logger.error(stdext::format("child '%s' of parent widget '%s' is recursively anchored to itself, please fix this", widget->getId(), parentWidget->getId()));
        return false;
    }

    if(!first)
        first = widget;

    Rect newRect = widget->getRect();
    bool verticalMoved = false;
    bool horizontalMoved = false;

    // calculates new rect based on anchors
    for(const UIAnchorPtr& anchor : anchorGroup->getAnchors()) {
        // skip invalid anchors
        if(anchor->getHookedEdge() == Fw::AnchorNone)
            continue;

        // determine hooked widget
        UIWidgetPtr hookedWidget = anchor->getHookedWidget(widget, parentWidget);

        // skip invalid anchors
        if(!hookedWidget)
            continue;

        if(hookedWidget != getParentWidget()) {
            // update this hooked widget anchors
            auto it = m_anchorsGroups.find(hookedWidget);
            if(it != m_anchorsGroups.end()) {
                const UIAnchorGroupPtr& hookedAnchorGroup = it->second;
                if(!hookedAnchorGroup->isUpdated())
                    updateWidget(hookedWidget, hookedAnchorGroup, first);
            }
        }

        int point = anchor->getHookedPoint(hookedWidget, parentWidget);

        switch(anchor->getAnchoredEdge()) {
            case Fw::AnchorHorizontalCenter:
                newRect.moveHorizontalCenter(point + widget->getMarginLeft() - widget->getMarginRight());
                horizontalMoved = true;
                break;
            case Fw::AnchorLeft:
                if(!horizontalMoved) {
                    newRect.moveLeft(point + widget->getMarginLeft());
                    horizontalMoved = true;
                } else
                    newRect.setLeft(point + widget->getMarginLeft());
                break;
            case Fw::AnchorRight:
                if(!horizontalMoved) {
                    newRect.moveRight(point - widget->getMarginRight());
                    horizontalMoved = true;
                } else
                    newRect.setRight(point - widget->getMarginRight());
                break;
            case Fw::AnchorVerticalCenter:
                newRect.moveVerticalCenter(point + widget->getMarginTop() - widget->getMarginBottom());
                verticalMoved = true;
                break;
            case Fw::AnchorTop:
                if(!verticalMoved) {
                    newRect.moveTop(point + widget->getMarginTop());
                    verticalMoved = true;
                } else
                    newRect.setTop(point + widget->getMarginTop());
                break;
            case Fw::AnchorBottom:
                if(!verticalMoved) {
                    newRect.moveBottom(point - widget->getMarginBottom());
                    verticalMoved = true;
                } else
                    newRect.setBottom(point - widget->getMarginBottom());
                break;
            default:
                break;
        }
    }

    bool changed = false;
    if(widget->setRect(newRect))
        changed = true;
    anchorGroup->setUpdated(true);
    return changed;
}