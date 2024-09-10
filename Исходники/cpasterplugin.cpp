bool CodepasterPlugin::initialize(const QStringList &arguments, QString *error_message)
{
    Q_UNUSED(arguments)
    Q_UNUSED(error_message)

    // Create the globalcontext list to register actions accordingly
    Core::Context globalcontext(Core::Constants::C_GLOBAL);

    // Create the settings Page
    m_settings->fromSettings(Core::ICore::instance()->settings());
    SettingsPage *settingsPage = new SettingsPage(m_settings);
    addAutoReleasedObject(settingsPage);

    // Create the protocols and append them to the Settings
    const QSharedPointer<NetworkAccessManagerProxy> networkAccessMgrProxy(new NetworkAccessManagerProxy);
    Protocol *protos[] =  { new PasteBinDotComProtocol(networkAccessMgrProxy),
                            new PasteBinDotCaProtocol(networkAccessMgrProxy),
                            new CodePasterProtocol(networkAccessMgrProxy),
                            new FileShareProtocol
                           };
    const int count = sizeof(protos) / sizeof(Protocol *);
    for(int i = 0; i < count; ++i) {
        connect(protos[i], SIGNAL(pasteDone(QString)), this, SLOT(finishPost(QString)));
        connect(protos[i], SIGNAL(fetchDone(QString,QString,bool)),
                this, SLOT(finishFetch(QString,QString,bool)));
        settingsPage->addProtocol(protos[i]->name());
        if (protos[i]->hasSettings())
            addAutoReleasedObject(protos[i]->settingsPage());
        m_protocols.append(protos[i]);
    }

    //register actions
    Core::ActionManager *actionManager = ICore::instance()->actionManager();

    Core::ActionContainer *toolsContainer =
        actionManager->actionContainer(Core::Constants::M_TOOLS);

    Core::ActionContainer *cpContainer =
        actionManager->createMenu(Core::Id("CodePaster"));
    cpContainer->menu()->setTitle(tr("&Code Pasting"));
    toolsContainer->addMenu(cpContainer);

    Core::Command *command;

    m_postEditorAction = new QAction(tr("Paste Snippet..."), this);
    command = actionManager->registerAction(m_postEditorAction, "CodePaster.Post", globalcontext);
    command->setDefaultKeySequence(QKeySequence(tr("Alt+C,Alt+P")));
    connect(m_postEditorAction, SIGNAL(triggered()), this, SLOT(postEditor()));
    cpContainer->addAction(command);

    m_postClipboardAction = new QAction(tr("Paste Clipboard..."), this);
    command = actionManager->registerAction(m_postClipboardAction, "CodePaster.PostClipboard", globalcontext);
    connect(m_postClipboardAction, SIGNAL(triggered()), this, SLOT(postClipboard()));
    cpContainer->addAction(command);

    m_fetchAction = new QAction(tr("Fetch Snippet..."), this);
    command = actionManager->registerAction(m_fetchAction, "CodePaster.Fetch", globalcontext);
    command->setDefaultKeySequence(QKeySequence(tr("Alt+C,Alt+F")));
    connect(m_fetchAction, SIGNAL(triggered()), this, SLOT(fetch()));
    cpContainer->addAction(command);

    connect(Core::EditorManager::instance(), SIGNAL(currentEditorChanged(Core::IEditor*)),
            this, SLOT(updateActions()));
    updateActions();
    return true;
}