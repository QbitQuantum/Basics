void ApplicationMenuPage::createContent()
{
    MApplicationPage::createContent();
    pannableViewport()->setAcceptGesturesFromAnyDirection(true);

    setStyleName(inv("CommonApplicationPage"));

    QGraphicsWidget *panel = centralWidget();

    infoLabel = new MLabel(panel);
    infoLabel->setObjectName("infoLabel");
    infoLabel->setStyleName(inv("CommonBodyText"));
    infoLabel->setWordWrap(true);
    infoLabel->setAlignment(Qt::AlignTop);

    actionItalic = new MAction(panel);
    actionItalic->setObjectName("actionItalic");
    actionItalic->setLocation(MAction::ApplicationMenuLocation);
    addAction(actionItalic);
    connect(actionItalic, SIGNAL(triggered()), this, SLOT(makeTextItalic()));

    actionNormal = new MAction(panel);
    actionNormal->setObjectName("actionNormal");
    actionNormal->setLocation(MAction::ApplicationMenuLocation);
    addAction(actionNormal);
    connect(actionNormal, SIGNAL(triggered()), this, SLOT(makeTextNormal()));

    MWidgetAction *widgetAction = new MWidgetAction(panel);
    widgetAction->setLocation(MAction::ApplicationMenuLocation);

    QStringList list;
    for (int i = 0; i < 5; ++i) {
        list << QString::number(100 + i);
    }
    comboBox = new MComboBox;
    comboBox->setObjectName("comboBox");
    comboBox->addItems(list);

    comboBox->setIconVisible(false);
    comboBox->setTitle("ComboBox");
    comboBox->setCurrentIndex(0);
    widgetAction->setWidget(comboBox);
    addAction(widgetAction);

    MLayout *layout = new MLayout(panel);
    layout->setContentsMargins(0, 0, 0, 0);
    panel->setLayout(layout);
    policy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    policy->setContentsMargins(0, 0, 0, 0);
    policy->setSpacing(0);

    policy->addItem(infoLabel);

    retranslateUi();
}