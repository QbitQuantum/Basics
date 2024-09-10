void ViewSplitter::setActiveContainer(ViewContainer* container)
{
    QWidget* activeView = container->activeView();

    if (activeView)
        activeView->setFocus(Qt::OtherFocusReason);
}