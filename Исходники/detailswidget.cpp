QWidget *DetailsWidget::takeWidget()
{
    QWidget *widget = d->m_widget;
    d->m_widget = 0;
    d->m_grid->removeWidget(widget);
    if (widget)
        widget->setParent(0);
    return widget;
}