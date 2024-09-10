void WidgetCreatorManager::moveNewWidget(const MyGUI::IntPoint& _point)
{
    if (mNewWidget == nullptr)
    {
        // тип виджета может отсутсвовать
        if (!MyGUI::WidgetManager::getInstance().isFactoryExist(mWidgetType))
            return;

        // выделяем верний виджет
        if (!mPopupMode)
            WidgetSelectorManager::getInstance().selectWidget(mStartPoint);

        MyGUI::Widget* parent = WidgetSelectorManager::getInstance().getSelectedWidget();

        // пока не найдем ближайшего над нами способного быть родителем
        while (parent != nullptr && !WidgetTypes::getInstance().findWidgetStyle(parent->getTypeName())->parent)
            parent = parent->getParent();

        if (!WidgetTypes::getInstance().findWidgetStyle(mWidgetType)->child)
            parent = nullptr;

        if (parent != nullptr)
            mNewWidget = parent->createWidgetT(
                             mPopupMode ? MyGUI::WidgetStyle::Popup : MyGUI::WidgetStyle::Child,
                             mWidgetType,
                             EditorWidgets::getInstance().getSkinReplace(mWidgetSkin),
                             MyGUI::IntCoord(),
                             MyGUI::Align::Default,
                             DEFAULT_EDITOR_LAYER);
        else
            mNewWidget = MyGUI::Gui::getInstance().createWidgetT(
                             mWidgetType,
                             EditorWidgets::getInstance().getSkinReplace(mWidgetSkin),
                             MyGUI::IntCoord(),
                             MyGUI::Align::Default,
                             DEFAULT_EDITOR_LAYER);

        // переводим старт поинт в координаты отца
        if (parent != nullptr && !mNewWidget->isRootWidget())
        {
            if (parent->getClientWidget())
                mStartPoint -= parent->getClientWidget()->getAbsolutePosition();
            else
                mStartPoint -= parent->getAbsolutePosition();
        }

        if (!MyGUI::InputManager::getInstance().isShiftPressed())
        {
            mStartPoint.left = Grid::getInstance().toGrid(mStartPoint.left);
            mStartPoint.top = Grid::getInstance().toGrid(mStartPoint.top);
        }
    }

    MyGUI::IntCoord coord = getCoordNewWidget(_point);
    mNewWidget->setCoord(coord);

    eventChangeSelector(true, mNewWidget->getAbsoluteCoord());
}