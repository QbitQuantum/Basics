keyboard::CustomEdit::CustomEdit(ShortcutModel *model, QWidget *parent):
    ContentWidget(parent),
    m_model(model),
    m_commandGroup(new SettingsGroup),
    m_name(new LineEditWidget),
    m_command(new LineEditWidget),
    m_short(new CustomItem(this)),
    m_tip(new QLabel),
    m_conflict(nullptr)
{
    m_tip->setVisible(false);
    m_tip->setWordWrap(true);

    setTitle(tr("Shortcuts"));
    TranslucentFrame *widget = new TranslucentFrame;
    QVBoxLayout *mainlayout = new QVBoxLayout;
    QHBoxLayout *buttonlayout = new QHBoxLayout;

    mainlayout->setMargin(0);
    buttonlayout->setMargin(0);
    mainlayout->setSpacing(0);
    buttonlayout->setSpacing(1);

    m_command->setPlaceholderText(tr("Required"));
    QPushButton *pushbutton = new QPushButton("...");
    pushbutton->setFixedWidth(50);
    m_command->addRightWidget(pushbutton);

    m_commandGroup->appendItem(m_name);
    m_commandGroup->appendItem(m_command);
    m_commandGroup->appendItem(m_short);

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    QPushButton *okButton = new QPushButton(tr("Save"));

    buttonlayout->addWidget(cancelButton);
    buttonlayout->addWidget(okButton);

    mainlayout->addSpacing(10);
    mainlayout->addWidget(m_commandGroup);
    mainlayout->addWidget(m_tip);
    mainlayout->addSpacing(10);
    mainlayout->addLayout(buttonlayout);

    widget->setLayout(mainlayout);

    setContent(widget);

    connect(cancelButton, &QPushButton::clicked, this, &CustomEdit::back);
    connect(pushbutton, &QPushButton::clicked, this, &CustomEdit::onOpenFile);
    connect(m_short, &CustomItem::requestUpdateKey, this, &CustomEdit::onUpdateKey);
    connect(okButton, &QPushButton::clicked, this, &CustomEdit::onSaveAccels);

    connect(model, &ShortcutModel::keyEvent, this, &CustomEdit::keyEvent);
}