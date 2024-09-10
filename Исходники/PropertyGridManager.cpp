/////////////////// <RANGE CONTROL>
    void PropertyGridManager::buildRangeControl(MyGUI::Widget *const control, PropertyGridProperty *const property)
    {
        int left = insertPropertyIdLabel(control, property) ;

        // scrollbar in between
        int width = control->getWidth() - left - WIDGET_SPACING * 2;
        MyGUI::IntCoord coord(left + WIDGET_SPACING, 1, width, control->getHeight() - 2);
        MyGUI::ScrollBar *scrollBar = (MyGUI::ScrollBar *)control->createWidget<MyGUI::ScrollBar>("SliderH", coord, MyGUI::Align::Left | MyGUI::Align::Top, "ScrollBar");
        scrollBar->setEnabled(!property->isReadOnly());
        MyGUIUtils::expandWidgetCoord(control, 0, 0, 0, 2);

        scrollBar->setScrollRange(100);
        scrollBar->setUserData(property);
        static_cast<MyGUI::ScrollBar *>(scrollBar)->eventScrollChangePosition += MyGUI::newDelegate(this, &PropertyGridManager::onMyGUIScrollChangePosition);


        MyGUI::TextBox *labelPtr;

        // label for min value
        left = insertLabel(control, "minLabel", "0.000", scrollBar->getLeft() + WIDGET_SPACING, labelPtr);
        labelPtr->setAlign(MyGUI::Align::Left | MyGUI::Align::VCenter);
        labelPtr->setNeedMouseFocus(false);
        labelPtr->setTextAlign(MyGUI::Align::Left);
        labelPtr->setTextColour(MyGUI::Colour::Black);

        // label for max value
        insertLabel(control, "maxLabel", "0.000", scrollBar->getRight() - labelPtr->getWidth() - WIDGET_SPACING, labelPtr); // built right after the minLabel
        labelPtr->setAlign(MyGUI::Align::Right | MyGUI::Align::VCenter);
        labelPtr->setNeedMouseFocus(false);
        labelPtr->setTextAlign(MyGUI::Align::Right);
        labelPtr->setTextColour(MyGUI::Colour::Black);

        // label for value
        insertLabel(control, "valueLabel", "0.000", (scrollBar->getLeft() + scrollBar->getRight()) / 2, labelPtr); // built right after the minLabel
        labelPtr->setAlign(MyGUI::Align::Center);
        labelPtr->setNeedMouseFocus(false);
        labelPtr->setTextAlign(MyGUI::Align::Center);
        labelPtr->setTextColour(MyGUI::Colour::Black);
    }