void SettingsWidget::addSettingsPage(ISettingsPage *page)
{
    QWidget * widget = page->createWidget();
    widget->setParent(this);
    m_extraPages.append(ExtraPage(page, widget));
    add(page->name(), widget);
}