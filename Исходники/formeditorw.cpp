void FormEditorW::setupActions()
{
    Core::ActionManager *am = Core::ICore::actionManager();
    Core::Command *command;

    //menus
    Core::ActionContainer *medit =
        am->actionContainer(Core::Constants::M_EDIT);
    Core::ActionContainer *mtools =
        am->actionContainer(Core::Constants::M_TOOLS);

    Core::ActionContainer *mformtools =
        am->createMenu(M_FORMEDITOR);
    mformtools->menu()->setTitle(tr("For&m Editor"));
    mtools->addMenu(mformtools);

    //overridden actions
    bindShortcut(am->registerAction(m_fwm->actionUndo(), Core::Constants::UNDO, m_contexts), m_fwm->actionUndo());
    bindShortcut(am->registerAction(m_fwm->actionRedo(), Core::Constants::REDO, m_contexts), m_fwm->actionRedo());
    bindShortcut(am->registerAction(m_fwm->actionCut(), Core::Constants::CUT, m_contexts), m_fwm->actionCut());
    bindShortcut(am->registerAction(m_fwm->actionCopy(), Core::Constants::COPY, m_contexts), m_fwm->actionCopy());
    bindShortcut(am->registerAction(m_fwm->actionPaste(), Core::Constants::PASTE, m_contexts), m_fwm->actionPaste());
    bindShortcut(am->registerAction(m_fwm->actionSelectAll(), Core::Constants::SELECTALL, m_contexts), m_fwm->actionSelectAll());

    m_actionPrint = new QAction(this);
    bindShortcut(am->registerAction(m_actionPrint, Core::Constants::PRINT, m_contexts), m_actionPrint);
    connect(m_actionPrint, SIGNAL(triggered()), this, SLOT(print()));

    //'delete' action. Do not set a shortcut as Designer handles
    // the 'Delete' key by event filter. Setting a shortcut triggers
    // buggy behaviour on Mac (Pressing Delete in QLineEdit removing the widget).
    command = am->registerAction(m_fwm->actionDelete(), Core::Id("FormEditor.Edit.Delete"), m_contexts);
    bindShortcut(command, m_fwm->actionDelete());
    command->setAttribute(Core::Command::CA_Hide);
    medit->addAction(command, Core::Constants::G_EDIT_COPYPASTE);

    m_actionGroupEditMode = new QActionGroup(this);
    m_actionGroupEditMode->setExclusive(true);
    connect(m_actionGroupEditMode, SIGNAL(triggered(QAction*)), this, SLOT(activateEditMode(QAction*)));

    m_modeActionSeparator = new QAction(this);
    m_modeActionSeparator->setSeparator(true);
    command = am->registerAction(m_modeActionSeparator, Core::Id("FormEditor.Sep.ModeActions"), m_contexts);
    medit->addAction(command, Core::Constants::G_EDIT_OTHER);

    m_toolActionIds.push_back(Core::Id("FormEditor.WidgetEditor"));
    createEditModeAction(m_actionGroupEditMode, m_contexts, am, medit,
                         tr("Edit Widgets"), m_toolActionIds.back(),
                         EditModeWidgetEditor, QLatin1String("widgettool.png"), tr("F3"));

    m_toolActionIds.push_back(Core::Id("FormEditor.SignalsSlotsEditor"));
    createEditModeAction(m_actionGroupEditMode, m_contexts, am, medit,
                         tr("Edit Signals/Slots"), m_toolActionIds.back(),
                         EditModeSignalsSlotEditor, QLatin1String("signalslottool.png"), tr("F4"));

    m_toolActionIds.push_back(Core::Id("FormEditor.BuddyEditor"));
    createEditModeAction(m_actionGroupEditMode, m_contexts, am, medit,
                         tr("Edit Buddies"), m_toolActionIds.back(),
                         EditModeBuddyEditor, QLatin1String("buddytool.png"));

    m_toolActionIds.push_back(Core::Id("FormEditor.TabOrderEditor"));
    createEditModeAction(m_actionGroupEditMode, m_contexts, am, medit,
                         tr("Edit Tab Order"),  m_toolActionIds.back(),
                         EditModeTabOrderEditor, QLatin1String("tabordertool.png"));

    //tool actions
    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutHorizontally"));
    const QString horizLayoutShortcut = osMac ? tr("Meta+H") : tr("Ctrl+H");
    addToolAction(m_fwm->actionHorizontalLayout(), am, m_contexts,
                  m_toolActionIds.back(), mformtools, horizLayoutShortcut);

    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutVertically"));
    const QString vertLayoutShortcut = osMac ? tr("Meta+L") : tr("Ctrl+L");
    addToolAction(m_fwm->actionVerticalLayout(), am, m_contexts,
                  m_toolActionIds.back(),  mformtools, vertLayoutShortcut);

    m_toolActionIds.push_back(Core::Id("FormEditor.SplitHorizontal"));
    addToolAction(m_fwm->actionSplitHorizontal(), am, m_contexts,
                  m_toolActionIds.back(), mformtools);

    m_toolActionIds.push_back(Core::Id("FormEditor.SplitVertical"));
    addToolAction(m_fwm->actionSplitVertical(), am, m_contexts,
                  m_toolActionIds.back(), mformtools);

    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutForm"));
    addToolAction(m_fwm->actionFormLayout(), am, m_contexts,
                  m_toolActionIds.back(),  mformtools);

    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutGrid"));
    const QString gridShortcut = osMac ? tr("Meta+G") : tr("Ctrl+G");
    addToolAction(m_fwm->actionGridLayout(), am, m_contexts,
                  m_toolActionIds.back(),  mformtools, gridShortcut);

    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutBreak"));
    addToolAction(m_fwm->actionBreakLayout(), am, m_contexts,
                  m_toolActionIds.back(), mformtools);

    m_toolActionIds.push_back(Core::Id("FormEditor.LayoutAdjustSize"));
    const QString adjustShortcut = osMac ? tr("Meta+J") : tr("Ctrl+J");
    addToolAction(m_fwm->actionAdjustSize(), am, m_contexts,
                  m_toolActionIds.back(),  mformtools, adjustShortcut);

    m_toolActionIds.push_back(Core::Id("FormEditor.SimplifyLayout"));
    addToolAction(m_fwm->actionSimplifyLayout(), am, m_contexts,
                  m_toolActionIds.back(),  mformtools);

    createSeparator(this, am, m_contexts, mformtools, Core::Id("FormEditor.Menu.Tools.Separator1"));

    addToolAction(m_fwm->actionLower(), am, m_contexts,
                  Core::Id("FormEditor.Lower"), mformtools);

    addToolAction(m_fwm->actionRaise(), am, m_contexts,
                  Core::Id("FormEditor.Raise"), mformtools);

    // Commands that do not go into the editor toolbar
    createSeparator(this, am, m_contexts, mformtools, Core::Id("FormEditor.Menu.Tools.Separator2"));

#if QT_VERSION >= 0x050000
    m_actionPreview = m_fwm->action(QDesignerFormWindowManagerInterface::DefaultPreviewAction);
#else
    m_actionPreview = m_fwm->actionDefaultPreview();
#endif
    QTC_ASSERT(m_actionPreview, return);
    addToolAction(m_actionPreview,  am,  m_contexts,
                   Core::Id("FormEditor.Preview"), mformtools, tr("Alt+Shift+R"));

    // Preview in style...
#if QT_VERSION >= 0x050000
    m_actionGroupPreviewInStyle = m_fwm->actionGroup(QDesignerFormWindowManagerInterface::StyledPreviewActionGroup);
#else
    m_actionGroupPreviewInStyle = m_fwm->actionGroupPreviewInStyle();
#endif

    Core::ActionContainer *previewAC = createPreviewStyleMenu(am, m_actionGroupPreviewInStyle);
    m_previewInStyleMenu = previewAC->menu();
    mformtools->addMenu(previewAC);
    setPreviewMenuEnabled(false);

    // Form settings
    createSeparator(this, am, m_contexts,  medit, Core::Id("FormEditor.Edit.Separator2"), Core::Constants::G_EDIT_OTHER);

    createSeparator(this, am, m_contexts, mformtools, Core::Id("FormEditor.Menu.Tools.Separator3"));

    m_actionSwitchSource = new QAction(tr("Switch Source/Form"), this);
    connect(m_actionSwitchSource, SIGNAL(triggered()), this, SLOT(switchSourceForm()));

    // Switch form/source in editor/design contexts.
    Core::Context switchContexts = m_contexts;
    switchContexts.add(Core::Constants::C_EDITORMANAGER);
    addToolAction(m_actionSwitchSource, am, switchContexts, Core::Id("FormEditor.FormSwitchSource"), mformtools,
                  tr("Shift+F4"));

    createSeparator(this, am, m_contexts, mformtools, Core::Id("FormEditor.Menu.Tools.Separator4"));
#if QT_VERSION >= 0x050000
    QAction *actionFormSettings = m_fwm->action(QDesignerFormWindowManagerInterface::FormWindowSettingsDialogAction);
#else
    QAction *actionFormSettings = m_fwm->actionShowFormWindowSettingsDialog();
#endif
    addToolAction(actionFormSettings, am, m_contexts, Core::Id("FormEditor.FormSettings"), mformtools);

    createSeparator(this, am, m_contexts, mformtools, Core::Id("FormEditor.Menu.Tools.Separator5"));
    m_actionAboutPlugins = new QAction(tr("About Qt Designer plugins...."), this);
    addToolAction(m_actionAboutPlugins,  am,  m_contexts,
                   Core::Id("FormEditor.AboutPlugins"), mformtools);
    connect(m_actionAboutPlugins,  SIGNAL(triggered()), m_fwm,
#if QT_VERSION >= 0x050000
            SLOT(showPluginDialog())
#else
            SLOT(aboutPlugins())
#endif
            );
    m_actionAboutPlugins->setEnabled(false);

    // FWM
    connect(m_fwm, SIGNAL(activeFormWindowChanged(QDesignerFormWindowInterface*)), this, SLOT(activeFormWindowChanged(QDesignerFormWindowInterface*)));
}