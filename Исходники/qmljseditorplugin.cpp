bool QmlJSEditorPlugin::initialize(const QStringList & /*arguments*/, QString *error_message)
{
    Core::ICore *core = Core::ICore::instance();
    if (!core->mimeDatabase()->addMimeTypes(QLatin1String(":/qmljseditor/QmlJSEditor.mimetypes.xml"), error_message))
        return false;

    m_modelManager = new ModelManager(this);
    addAutoReleasedObject(m_modelManager);

    QList<int> context;
    context << core->uniqueIDManager()->uniqueIdentifier(QmlJSEditor::Constants::C_QMLJSEDITOR_ID);

    m_editor = new QmlJSEditorFactory(this);
    addObject(m_editor);

    Core::BaseFileWizardParameters wizardParameters(Core::IWizard::FileWizard);
    wizardParameters.setCategory(QLatin1String(Core::Constants::WIZARD_CATEGORY_QT));
    wizardParameters.setDisplayCategory(QCoreApplication::translate("Core", Core::Constants::WIZARD_TR_CATEGORY_QT));
    wizardParameters.setDescription(tr("Creates a Qt QML file."));
    wizardParameters.setDisplayName(tr("Qt QML File"));
    wizardParameters.setId(QLatin1String("Q.Qml"));
    addAutoReleasedObject(new QmlFileWizard(wizardParameters, core));

    m_actionHandler = new TextEditor::TextEditorActionHandler(QmlJSEditor::Constants::C_QMLJSEDITOR_ID,
          TextEditor::TextEditorActionHandler::Format
        | TextEditor::TextEditorActionHandler::UnCommentSelection
        | TextEditor::TextEditorActionHandler::UnCollapseAll);
    m_actionHandler->initializeActions();

    Core::ActionManager *am =  core->actionManager();
    Core::ActionContainer *contextMenu = am->createMenu(QmlJSEditor::Constants::M_CONTEXT);

    Core::Command *cmd;
    QAction *followSymbolUnderCursorAction = new QAction(tr("Follow Symbol Under Cursor"), this);
    cmd = am->registerAction(followSymbolUnderCursorAction, Constants::FOLLOW_SYMBOL_UNDER_CURSOR, context);
    cmd->setDefaultKeySequence(QKeySequence(Qt::Key_F2));
    connect(followSymbolUnderCursorAction, SIGNAL(triggered()), this, SLOT(followSymbolUnderCursor()));
    contextMenu->addAction(cmd);

    cmd = am->command(TextEditor::Constants::AUTO_INDENT_SELECTION);
    contextMenu->addAction(cmd);

    cmd = am->command(TextEditor::Constants::UN_COMMENT_SELECTION);
    contextMenu->addAction(cmd);

    CodeCompletion *completion = new CodeCompletion(m_modelManager);
    addAutoReleasedObject(completion);

    addAutoReleasedObject(new HoverHandler);

    // Set completion settings and keep them up to date
    TextEditor::TextEditorSettings *textEditorSettings = TextEditor::TextEditorSettings::instance();
    completion->setCompletionSettings(textEditorSettings->completionSettings());
    connect(textEditorSettings, SIGNAL(completionSettingsChanged(TextEditor::CompletionSettings)),
            completion, SLOT(setCompletionSettings(TextEditor::CompletionSettings)));

    error_message->clear();

    Core::FileIconProvider *iconProvider = Core::FileIconProvider::instance();
    iconProvider->registerIconOverlayForSuffix(QIcon(":/qmljseditor/images/qmlfile.png"), "qml");

    return true;
}