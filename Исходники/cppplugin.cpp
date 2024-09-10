bool CppPlugin::initialize(const QStringList & /*arguments*/, QString *errorMessage)
{
    Core::ICore *core = Core::ICore::instance();

    if (!core->mimeDatabase()->addMimeTypes(QLatin1String(":/cppeditor/CppEditor.mimetypes.xml"), errorMessage))
        return false;

    addAutoReleasedObject(new CppEditorFactory(this));
    addAutoReleasedObject(new CppHoverHandler);
    addAutoReleasedObject(new CppOutlineWidgetFactory);
    addAutoReleasedObject(new CppTypeHierarchyFactory);
    addAutoReleasedObject(new CppSnippetProvider);

    m_quickFixCollector = new CppQuickFixCollector;
    addAutoReleasedObject(m_quickFixCollector);
    CppQuickFixCollector::registerQuickFixes(this);

    CppFileWizard::BaseFileWizardParameters wizardParameters(Core::IWizard::FileWizard);

    wizardParameters.setCategory(QLatin1String(Constants::WIZARD_CATEGORY));
    wizardParameters.setDisplayCategory(QCoreApplication::translate(Constants::WIZARD_CATEGORY,
                                                                    Constants::WIZARD_TR_CATEGORY));
    wizardParameters.setDisplayName(tr("C++ Class"));
    wizardParameters.setId(QLatin1String("A.Class"));
    wizardParameters.setKind(Core::IWizard::ClassWizard);
    wizardParameters.setDescription(tr("Creates a C++ header and a source file for a new class that you can add to a C++ project."));
    addAutoReleasedObject(new CppClassWizard(wizardParameters, core));

    wizardParameters.setKind(Core::IWizard::FileWizard);
    wizardParameters.setDescription(tr("Creates a C++ source file that you can add to a C++ project."));
    wizardParameters.setDisplayName(tr("C++ Source File"));
    wizardParameters.setId(QLatin1String("B.Source"));
    addAutoReleasedObject(new CppFileWizard(wizardParameters, Source, core));

    wizardParameters.setDescription(tr("Creates a C++ header file that you can add to a C++ project."));
    wizardParameters.setDisplayName(tr("C++ Header File"));
    wizardParameters.setId(QLatin1String("C.Header"));
    addAutoReleasedObject(new CppFileWizard(wizardParameters, Header, core));

    Core::Context context(CppEditor::Constants::C_CPPEDITOR);

    Core::ActionManager *am = core->actionManager();
    Core::ActionContainer *contextMenu= am->createMenu(CppEditor::Constants::M_CONTEXT);

    Core::Command *cmd;
    Core::ActionContainer *cppToolsMenu = am->actionContainer(Core::Id(CppTools::Constants::M_TOOLS_CPP));

    QAction *jumpToDefinition = new QAction(tr("Follow Symbol Under Cursor"), this);
    cmd = am->registerAction(jumpToDefinition,
        Constants::JUMP_TO_DEFINITION, context, true);
    cmd->setDefaultKeySequence(QKeySequence(Qt::Key_F2));
    connect(jumpToDefinition, SIGNAL(triggered()),
            this, SLOT(jumpToDefinition()));
    contextMenu->addAction(cmd);
    cppToolsMenu->addAction(cmd);

    QAction *switchDeclarationDefinition = new QAction(tr("Switch Between Method Declaration/Definition"), this);
    cmd = am->registerAction(switchDeclarationDefinition,
        Constants::SWITCH_DECLARATION_DEFINITION, context, true);
    cmd->setDefaultKeySequence(QKeySequence("Shift+F2"));
    connect(switchDeclarationDefinition, SIGNAL(triggered()),
            this, SLOT(switchDeclarationDefinition()));
    contextMenu->addAction(cmd);
    cppToolsMenu->addAction(cmd);

    m_findUsagesAction = new QAction(tr("Find Usages"), this);
    cmd = am->registerAction(m_findUsagesAction, Constants::FIND_USAGES, context);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+U")));
    connect(m_findUsagesAction, SIGNAL(triggered()), this, SLOT(findUsages()));
    contextMenu->addAction(cmd);
    cppToolsMenu->addAction(cmd);

    m_openTypeHierarchyAction = new QAction(tr("Open Type Hierarchy"), this);
    cmd = am->registerAction(m_openTypeHierarchyAction, Constants::OPEN_TYPE_HIERARCHY, context);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+T")));
    connect(m_openTypeHierarchyAction, SIGNAL(triggered()), this, SLOT(openTypeHierarchy()));
    contextMenu->addAction(cmd);
    cppToolsMenu->addAction(cmd);

    // Refactoring sub-menu
    Core::Context globalContext(Core::Constants::C_GLOBAL);
    Core::Command *sep = createSeparator(am, this, globalContext,
                                         Constants::SEPARATOR2);
    sep->action()->setObjectName(Constants::M_REFACTORING_MENU_INSERTION_POINT);
    contextMenu->addAction(sep);
    contextMenu->addAction(createSeparator(am, this, globalContext,
                                           Constants::SEPARATOR3));

    m_renameSymbolUnderCursorAction = new QAction(tr("Rename Symbol Under Cursor"),
                                                  this);
    cmd = am->registerAction(m_renameSymbolUnderCursorAction,
                             Constants::RENAME_SYMBOL_UNDER_CURSOR,
                             context);
    cmd->setDefaultKeySequence(QKeySequence("CTRL+SHIFT+R"));
    connect(m_renameSymbolUnderCursorAction, SIGNAL(triggered()),
            this, SLOT(renameSymbolUnderCursor()));
    cppToolsMenu->addAction(cmd);

    // Update context in global context
    cppToolsMenu->addAction(createSeparator(am, this, globalContext, CppEditor::Constants::SEPARATOR4));
    m_updateCodeModelAction = new QAction(tr("Update Code Model"), this);
    cmd = am->registerAction(m_updateCodeModelAction, Core::Id(Constants::UPDATE_CODEMODEL), globalContext);
    CPlusPlus::CppModelManagerInterface *cppModelManager = CPlusPlus::CppModelManagerInterface::instance();
    connect(m_updateCodeModelAction, SIGNAL(triggered()), cppModelManager, SLOT(updateModifiedSourceFiles()));
    cppToolsMenu->addAction(cmd);

    m_actionHandler = new TextEditor::TextEditorActionHandler(CppEditor::Constants::C_CPPEDITOR,
        TextEditor::TextEditorActionHandler::Format
        | TextEditor::TextEditorActionHandler::UnCommentSelection
        | TextEditor::TextEditorActionHandler::UnCollapseAll);

    m_actionHandler->initializeActions();

    contextMenu->addAction(createSeparator(am, this, context, CppEditor::Constants::SEPARATOR));

    cmd = am->command(TextEditor::Constants::AUTO_INDENT_SELECTION);
    contextMenu->addAction(cmd);

    cmd = am->command(TextEditor::Constants::UN_COMMENT_SELECTION);
    contextMenu->addAction(cmd);

    connect(core->progressManager(), SIGNAL(taskStarted(QString)),
            this, SLOT(onTaskStarted(QString)));
    connect(core->progressManager(), SIGNAL(allTasksFinished(QString)),
            this, SLOT(onAllTasksFinished(QString)));

    connect(core->editorManager(), SIGNAL(currentEditorChanged(Core::IEditor*)), SLOT(currentEditorChanged(Core::IEditor*)));

    readSettings();
    return true;
}