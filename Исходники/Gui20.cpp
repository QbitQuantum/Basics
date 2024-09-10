ToolButton*
Gui::findOrCreateToolButton(const PluginGroupNodePtr & treeNode)
{

    // Do not create an action for non user creatable plug-ins
    bool isUserCreatable = true;
    PluginPtr internalPlugin = treeNode->getPlugin();
    if (internalPlugin && treeNode->getChildren().empty() && !internalPlugin->getIsUserCreatable()) {
        isUserCreatable = false;
    }
    if (!isUserCreatable) {
        return 0;
    }

    // Check for existing toolbuttons
    for (std::size_t i = 0; i < _imp->_toolButtons.size(); ++i) {
        if (_imp->_toolButtons[i]->getPluginToolButton() == treeNode) {
            return _imp->_toolButtons[i];
        }
    }

    // Check for parent toolbutton
    ToolButton* parentToolButton = NULL;
    if ( treeNode->getParent() ) {
        assert(treeNode->getParent() != treeNode);
        if (treeNode->getParent() != treeNode) {
            parentToolButton = findOrCreateToolButton( treeNode->getParent() );
        }
    }

    QString resourcesPath;
    if (internalPlugin) {
        resourcesPath = QString::fromUtf8(internalPlugin->getProperty<std::string>(kNatronPluginPropResourcesPath).c_str());
    }
    QString iconFilePath = resourcesPath;
    StrUtils::ensureLastPathSeparator(iconFilePath);
    iconFilePath += treeNode->getTreeNodeIconFilePath();

    QIcon toolButtonIcon, menuIcon;
    // Create tool icon
    if ( !iconFilePath.isEmpty() && QFile::exists(iconFilePath) ) {
        QPixmap pix(iconFilePath);
        int menuSize = TO_DPIX(NATRON_MEDIUM_BUTTON_ICON_SIZE);
        int toolButtonSize = !treeNode->getParent() ? TO_DPIX(NATRON_TOOL_BUTTON_ICON_SIZE) : TO_DPIX(NATRON_MEDIUM_BUTTON_ICON_SIZE);
        QPixmap menuPix = pix, toolbuttonPix = pix;
        if ( (std::max( menuPix.width(), menuPix.height() ) != menuSize) && !menuPix.isNull() ) {
            menuPix = menuPix.scaled(menuSize, menuSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        if ( (std::max( toolbuttonPix.width(), toolbuttonPix.height() ) != toolButtonSize) && !toolbuttonPix.isNull() ) {
            toolbuttonPix = toolbuttonPix.scaled(toolButtonSize, toolButtonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        menuIcon.addPixmap(menuPix);
        toolButtonIcon.addPixmap(toolbuttonPix);
    } else {
        // Set default icon only if it has no parent, otherwise leave action without an icon
        if ( !treeNode->getParent() ) {
            QPixmap toolbuttonPix, menuPix;
            getPixmapForGrouping( &toolbuttonPix, TO_DPIX(NATRON_TOOL_BUTTON_ICON_SIZE), treeNode->getTreeNodeName() );
            toolButtonIcon.addPixmap(toolbuttonPix);
            getPixmapForGrouping( &menuPix, TO_DPIX(NATRON_TOOL_BUTTON_ICON_SIZE), treeNode->getTreeNodeName() );
            menuIcon.addPixmap(menuPix);
        }
    }

    // If the tool-button has no children, this is a leaf, we must create an action
    // At this point any plug-in MUST be in a toolbutton, so it must have a parent.
    assert(!treeNode->getChildren().empty() || treeNode->getParent());

    int majorVersion = internalPlugin ? internalPlugin->getProperty<unsigned int>(kNatronPluginPropVersion, 0) : 1;
    int minorVersion = internalPlugin ? internalPlugin->getProperty<unsigned int>(kNatronPluginPropVersion, 1) : 0;

    ToolButton* pluginsToolButton = new ToolButton(getApp(),
                                                   treeNode,
                                                   treeNode->getTreeNodeID(),
                                                   majorVersion,
                                                   minorVersion,
                                                   treeNode->getTreeNodeName(),
                                                   toolButtonIcon,
                                                   menuIcon);

    if (!treeNode->getChildren().empty()) {
        // For grouping items, create the menu
        Menu* menu = new Menu(this);
        menu->setTitle( pluginsToolButton->getLabel() );
        menu->setIcon(menuIcon);
        pluginsToolButton->setMenu(menu);
        pluginsToolButton->setAction( menu->menuAction() );
    } else {
        // This is a leaf (plug-in)
        assert(internalPlugin);
        assert(parentToolButton);

        // If this is the highest major version for this plug-in use normal label, otherwise also append the major version
        bool isHighestMajorVersionForPlugin = internalPlugin->getIsHighestMajorVersion();

        std::string pluginLabel = !isHighestMajorVersionForPlugin ? internalPlugin->getLabelVersionMajorEncoded() : internalPlugin->getLabelWithoutSuffix();

        QKeySequence defaultNodeShortcut;
        QString shortcutGroup = QString::fromUtf8(kShortcutGroupNodes);
        std::vector<std::string> groupingSplit = internalPlugin->getPropertyN<std::string>(kNatronPluginPropGrouping);
        for (std::size_t j = 0; j < groupingSplit.size(); ++j) {
            shortcutGroup.push_back( QLatin1Char('/') );
            shortcutGroup.push_back(QString::fromUtf8(groupingSplit[j].c_str()));
        }
        {
            // If the plug-in has a shortcut get it

            std::list<QKeySequence> keybinds = getKeybind(shortcutGroup, QString::fromUtf8(internalPlugin->getPluginID().c_str()));
            if (!keybinds.empty()) {
                defaultNodeShortcut = keybinds.front();
            }
        }

        QAction* defaultPresetAction = new QAction(this);
        defaultPresetAction->setShortcut(defaultNodeShortcut);
        defaultPresetAction->setShortcutContext(Qt::WidgetShortcut);
        defaultPresetAction->setText(QString::fromUtf8(pluginLabel.c_str()));
        defaultPresetAction->setIcon( pluginsToolButton->getMenuIcon() );
        QObject::connect( defaultPresetAction, SIGNAL(triggered()), pluginsToolButton, SLOT(onTriggered()) );


        const std::vector<PluginPresetDescriptor>& presets = internalPlugin->getPresetFiles();
        if (presets.empty()) {
            // If the node has no presets, just make an action, otherwise make a menu
            pluginsToolButton->setAction(defaultPresetAction);
        } else {


            Menu* menu = new Menu(this);
            menu->setTitle( pluginsToolButton->getLabel() );
            menu->setIcon(menuIcon);
            pluginsToolButton->setMenu(menu);
            pluginsToolButton->setAction( menu->menuAction() );

            defaultPresetAction->setText(QString::fromUtf8(pluginLabel.c_str()) + tr(" (Default)"));
            menu->addAction(defaultPresetAction);

            for (std::vector<PluginPresetDescriptor>::const_iterator it = presets.begin(); it!=presets.end(); ++it) {

                QKeySequence presetShortcut;
                {
                    // If the preset has a shortcut get it

                    std::string shortcutKey = internalPlugin->getPluginID();
                    shortcutKey += "_preset_";
                    shortcutKey += it->presetLabel.toStdString();

                    std::list<QKeySequence> keybinds = getKeybind(shortcutGroup, QString::fromUtf8(shortcutKey.c_str()));
                    if (!keybinds.empty()) {
                        presetShortcut = keybinds.front();
                    }
                }

                QString presetLabel = QString::fromUtf8(pluginLabel.c_str());
                presetLabel += QLatin1String(" (");
                presetLabel += it->presetLabel;
                presetLabel += QLatin1String(")");

                QAction* presetAction = new QAction(this);
                QPixmap presetPix;
                if (getPresetIcon(it->presetFilePath, it->presetIconFile, TO_DPIX(NATRON_MEDIUM_BUTTON_ICON_SIZE), &presetPix)) {
                    presetAction->setIcon( presetPix );
                }
                presetAction->setShortcut(presetShortcut);
                presetAction->setShortcutContext(Qt::WidgetShortcut);
                presetAction->setText(presetLabel);
                presetAction->setData(it->presetLabel);
                QObject::connect( presetAction, SIGNAL(triggered()), pluginsToolButton, SLOT(onTriggered()) );

                menu->addAction(presetAction);
            }
        }

    } // if (!treeNode->getChildren().empty())

    // If it has a parent, add the new tool button as a child
    if (parentToolButton) {
        parentToolButton->tryAddChild(pluginsToolButton);
    }
    _imp->_toolButtons.push_back(pluginsToolButton);

    return pluginsToolButton;
} // findOrCreateToolButton