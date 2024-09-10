QPushButton *PostWidget::addButton(const QString &objName, const QString &toolTip, const QIcon &icon)
{
    QPushButton *button = new QPushButton(icon, QString(), _mainWidget);
    button->setObjectName(objName);
    button->setToolTip(toolTip);
    button->setIconSize(QSize(16, 16));
    button->setMinimumSize(QSize(20, 20));
    button->setMaximumSize(QSize(20, 20));
    button->setFlat(true);
    button->setVisible(false);
    button->setCursor(Qt::PointingHandCursor);

    d->mUiButtons.insert(objName, button);
    d->buttonsLayout->addWidget(button, 1, d->mUiButtons.count());
    return button;
}