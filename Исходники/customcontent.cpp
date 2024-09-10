CustomContent::CustomContent(ShortcutModel *model, QWidget *parent)
    : ContentWidget(parent)
    , m_conflict(nullptr)
    , m_model(model)
    , m_buttonTuple(new ButtonTuple)
{
    setTitle(tr("Shortcuts"));
    TranslucentFrame *widget = new TranslucentFrame();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addSpacing(10);

    m_commandGroup = new SettingsGroup();
    m_name = new LineEditWidget();
    m_name->setTitle(tr("Name"));
    m_name->setPlaceholderText(tr("Required"));

    m_command = new LineEditWidget();
    m_command->setTitle(tr("Command"));
    m_command->setPlaceholderText(tr("Required"));
    QPushButton *pushbutton = new QPushButton("...");
    pushbutton->setFixedWidth(50);
    m_command->addRightWidget(pushbutton);

    m_shortcut = new CustomItem;
    m_shortcut->setShortcut("");

    m_commandGroup->appendItem(m_name);
    m_commandGroup->appendItem(m_command);
    m_commandGroup->appendItem(m_shortcut);

    layout->addWidget(m_commandGroup);

    QPushButton *cancel = m_buttonTuple->leftButton();
    cancel->setText(tr("Cancel"));
    QPushButton *ok = m_buttonTuple->rightButton();
    ok->setText(tr("Add"));

    m_bottomTip = new QLabel();
    m_bottomTip->setWordWrap(true);
    m_bottomTip->hide();

    layout->addWidget(m_buttonTuple);
    layout->addWidget(m_bottomTip);
    layout->addStretch();

    widget->setLayout(layout);
    setContent(widget);

    connect(cancel, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(ok, SIGNAL(clicked()), this, SLOT(onShortcut()));
    connect(pushbutton, &QPushButton::clicked, this, &CustomContent::onOpenFile);
    connect(m_shortcut, &CustomItem::requestUpdateKey, this, &CustomContent::updateKey);
    connect(model, &ShortcutModel::keyEvent, this, &CustomContent::keyEvent);
}