InputWidget::InputWidget(QWidget *parent)
    : AbstractItemView(parent),
    _networkId(0)
{
    ui.setupUi(this);
    connect(ui.ownNick, SIGNAL(activated(QString)), this, SLOT(changeNick(QString)));

    layout()->setAlignment(ui.ownNick, Qt::AlignBottom);
    layout()->setAlignment(ui.inputEdit, Qt::AlignBottom);
    layout()->setAlignment(ui.showStyleButton, Qt::AlignBottom);
    layout()->setAlignment(ui.styleFrame, Qt::AlignBottom);

    ui.styleFrame->setVisible(false);

    setFocusProxy(ui.inputEdit);
    ui.ownNick->setFocusProxy(ui.inputEdit);

    ui.ownNick->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui.ownNick->installEventFilter(new MouseWheelFilter(this));
    ui.inputEdit->installEventFilter(this);

    ui.inputEdit->setMinHeight(1);
    ui.inputEdit->setMaxHeight(5);
    ui.inputEdit->setMode(MultiLineEdit::MultiLine);
    ui.inputEdit->setPasteProtectionEnabled(true);

    ui.boldButton->setIcon(QIcon::fromTheme("format-text-bold"));
    ui.italicButton->setIcon(QIcon::fromTheme("format-text-italic"));
    ui.underlineButton->setIcon(QIcon::fromTheme("format-text-underline"));
    ui.textcolorButton->setIcon(QIcon::fromTheme("format-text-color"));
    ui.highlightcolorButton->setIcon(QIcon::fromTheme("format-fill-color"));
    ui.encryptionIconLabel->hide();

    _colorMenu = new QMenu();
    _colorFillMenu = new QMenu();

    QStringList names;
    names << tr("White") << tr("Black") << tr("Dark blue") << tr("Dark green") << tr("Red") << tr("Dark red") << tr("Dark magenta")  << tr("Orange")
          << tr("Yellow") << tr("Green") << tr("Dark cyan") << tr("Cyan") << tr("Blue") << tr("Magenta") << tr("Dark gray") << tr("Light gray");

    QPixmap pix(16, 16);
    for (int i = 0; i < inputLine()->mircColorMap().count(); i++) {
        pix.fill(inputLine()->mircColorMap().values()[i]);
        _colorMenu->addAction(pix, names[i])->setData(inputLine()->mircColorMap().keys()[i]);
        _colorFillMenu->addAction(pix, names[i])->setData(inputLine()->mircColorMap().keys()[i]);
    }

    pix.fill(Qt::transparent);
    _colorMenu->addAction(pix, tr("Clear Color"))->setData("");
    _colorFillMenu->addAction(pix, tr("Clear Color"))->setData("");

    ui.textcolorButton->setMenu(_colorMenu);
    connect(_colorMenu, SIGNAL(triggered(QAction *)), this, SLOT(colorChosen(QAction *)));
    ui.highlightcolorButton->setMenu(_colorFillMenu);
    connect(_colorFillMenu, SIGNAL(triggered(QAction *)), this, SLOT(colorHighlightChosen(QAction *)));

    new TabCompleter(ui.inputEdit);

    UiStyleSettings fs("Fonts");
    fs.notify("UseCustomInputWidgetFont", this, SLOT(setUseCustomFont(QVariant)));
    fs.notify("InputWidget", this, SLOT(setCustomFont(QVariant)));
    if (fs.value("UseCustomInputWidgetFont", false).toBool())
        setCustomFont(fs.value("InputWidget", QFont()));

    UiSettings s("InputWidget");

#ifdef HAVE_KDE4
    s.notify("EnableSpellCheck", this, SLOT(setEnableSpellCheck(QVariant)));
    setEnableSpellCheck(s.value("EnableSpellCheck", false));
#endif

    s.notify("EnableEmacsMode", this, SLOT(setEnableEmacsMode(QVariant)));
    setEnableEmacsMode(s.value("EnableEmacsMode", false));

    s.notify("ShowNickSelector", this, SLOT(setShowNickSelector(QVariant)));
    setShowNickSelector(s.value("ShowNickSelector", true));

    s.notify("ShowStyleButtons", this, SLOT(setShowStyleButtons(QVariant)));
    setShowStyleButtons(s.value("ShowStyleButtons", true));

    s.notify("EnablePerChatHistory", this, SLOT(setEnablePerChatHistory(QVariant)));
    setEnablePerChatHistory(s.value("EnablePerChatHistory", true));

    s.notify("MaxNumLines", this, SLOT(setMaxLines(QVariant)));
    setMaxLines(s.value("MaxNumLines", 5));

    s.notify("EnableScrollBars", this, SLOT(setScrollBarsEnabled(QVariant)));
    setScrollBarsEnabled(s.value("EnableScrollBars", true));

    s.notify("EnableLineWrap", this, SLOT(setLineWrapEnabled(QVariant)));
    setLineWrapEnabled(s.value("EnableLineWrap", true));

    s.notify("EnableMultiLine", this, SLOT(setMultiLineEnabled(QVariant)));
    setMultiLineEnabled(s.value("EnableMultiLine", true));

    ActionCollection *coll = QtUi::actionCollection();

    Action *activateInputline = coll->add<Action>("FocusInputLine");
    connect(activateInputline, SIGNAL(triggered()), SLOT(setFocus()));
    activateInputline->setText(tr("Focus Input Line"));
    activateInputline->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    connect(inputLine(), SIGNAL(textEntered(QString)), SLOT(onTextEntered(QString)), Qt::QueuedConnection); // make sure the line is already reset, bug #984
    connect(inputLine(), SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(currentCharFormatChanged(QTextCharFormat)));
}