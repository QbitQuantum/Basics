void EditGroupWidget::addEditPage(IEditGroupPage* page)
{
    QWidget* widget = page->createWidget();
    widget->setParent(this);

    m_extraPages.append(ExtraPage(page, widget));
    addPage(page->name(), page->icon(), widget);
}