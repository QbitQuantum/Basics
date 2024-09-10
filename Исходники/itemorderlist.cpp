void ItemOrderList::setCurrentItemWidget(QWidget *widget)
{
    // Reparent current widget so it's safely deleted.
    QWidget *currentWidget = ui->scrollArea->takeWidget();
    if (currentWidget != nullptr) {
        currentWidget->setParent(this);
        currentWidget->hide();
    }

    if (widget != nullptr) {
        ui->scrollArea->setWidget(widget);
        widget->show();
    }
}