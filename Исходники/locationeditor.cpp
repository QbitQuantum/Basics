LocationEditor::LocationEditor(QWidget *parent) :
    QToolButton(parent)
{
    QPalette pal;
    pal.setColor(backgroundRole(), QPalette::Base);
    setPalette(pal);

    this->setFont(global.getGuiFont(font()));

    inactiveColor = "QToolButton {background-color: transparent; border-radius: 0px; border:none; margin 0px; padding: 4px} ";
    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet(inactiveColor);

    defaultText = QString(tr("Click to set location..."));
    this->setText(defaultText);
    actionMenu = new QMenu();
    editAction = actionMenu->addAction(tr("Edit..."));
    clearAction = actionMenu->addAction(tr("Clear"));
    viewAction = actionMenu->addAction(tr("View on map"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(buttonClicked()));
    connect(viewAction, SIGNAL(triggered()), this, SLOT(viewClicked()));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clearClicked()));
    setAutoRaise(false);
    setMenu(actionMenu);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->reloadIcons();
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    hide();
}