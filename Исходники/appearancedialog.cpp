QToolButton* AppearanceDialog::selectButton(int width, int height, QString toolTip) {
    QToolButton* button = new QToolButton(this);
    button->setToolTip(toolTip);
    button->setToolButtonStyle(Qt::ToolButtonTextOnly);
    button->setMenu(new QMenu(button));
    button->setMinimumWidth(width);
    button->setMinimumHeight(height);

    return button;
}