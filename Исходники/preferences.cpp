Preferences::Preferences(QupZilla* mainClass, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Preferences)
    , p_QupZilla(mainClass)
    , m_autoFillManager(0)
    , m_pluginsList(0)
    , m_autoFillEnabled(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->languages->setLayoutDirection(Qt::LeftToRight);

    m_themesManager = new ThemeManager(ui->themesWidget, this);
    m_pluginsList = new PluginsManager(this);
    ui->pluginsFrame->addWidget(m_pluginsList);

    if (QIcon::themeName().toLower() == QLatin1String("oxygen")) {
        ui->listWidget->item(0)->setIcon(QIcon::fromTheme("preferences-desktop", QIcon(":/icons/preferences/preferences-desktop.png")));
        ui->listWidget->item(1)->setIcon(QIcon::fromTheme("format-stroke-color", QIcon(":/icons/preferences/application-x-theme.png")));
        ui->listWidget->item(2)->setIcon(QIcon::fromTheme("tab-new-background", QIcon(":/icons/preferences/applications-internet.png")));
        ui->listWidget->item(3)->setIcon(QIcon::fromTheme("preferences-system-network", QIcon(":/icons/preferences/applications-webbrowsers.png")));
        ui->listWidget->item(4)->setIcon(QIcon::fromTheme("preferences-desktop-font", QIcon(":/icons/preferences/applications-fonts.png")));
        ui->listWidget->item(5)->setIcon(QIcon::fromTheme("configure-shortcuts", QIcon(":/icons/preferences/preferences-desktop-keyboard-shortcuts.png")));
        ui->listWidget->item(6)->setIcon(QIcon::fromTheme("download", QIcon(":/icons/preferences/mail-inbox.png")));
        ui->listWidget->item(7)->setIcon(QIcon::fromTheme("user-identity", QIcon(":/icons/preferences/dialog-password.png")));
        ui->listWidget->item(8)->setIcon(QIcon::fromTheme("preferences-system-firewall", QIcon(":/icons/preferences/preferences-system-firewall.png")));
        ui->listWidget->item(9)->setIcon(QIcon::fromTheme("preferences-desktop-notification", QIcon(":/icons/preferences/dialog-question.png")));
        ui->listWidget->item(10)->setIcon(QIcon::fromTheme("preferences-plugin", QIcon(":/icons/preferences/extension.png")));
        ui->listWidget->item(11)->setIcon(QIcon::fromTheme("applications-system", QIcon(":/icons/preferences/applications-system.png")));
    }
    else {
        ui->listWidget->item(0)->setIcon(QIcon::fromTheme("preferences-desktop", QIcon(":/icons/preferences/preferences-desktop.png")));
        ui->listWidget->item(1)->setIcon(QIcon::fromTheme("application-x-theme", QIcon(":/icons/preferences/application-x-theme.png")));
        ui->listWidget->item(2)->setIcon(QIcon::fromTheme("applications-internet", QIcon(":/icons/preferences/applications-internet.png")));
        ui->listWidget->item(3)->setIcon(QIcon::fromTheme("applications-webbrowsers", QIcon(":/icons/preferences/applications-webbrowsers.png")));
        ui->listWidget->item(4)->setIcon(QIcon::fromTheme("applications-fonts", QIcon(":/icons/preferences/applications-fonts.png")));
        ui->listWidget->item(5)->setIcon(QIcon::fromTheme("preferences-desktop-keyboard-shortcuts", QIcon(":/icons/preferences/preferences-desktop-keyboard-shortcuts.png")));
        ui->listWidget->item(6)->setIcon(QIcon::fromTheme("mail-inbox", QIcon(":/icons/preferences/mail-inbox.png")));
        ui->listWidget->item(7)->setIcon(QIcon::fromTheme("dialog-password", QIcon(":/icons/preferences/dialog-password.png")));
        ui->listWidget->item(8)->setIcon(QIcon::fromTheme("preferences-system-firewall", QIcon(":/icons/preferences/preferences-system-firewall.png")));
        ui->listWidget->item(9)->setIcon(QIcon::fromTheme("dialog-question", QIcon(":/icons/preferences/dialog-question.png")));
        ui->listWidget->item(10)->setIcon(QIcon::fromTheme("extension", QIcon(":/icons/preferences/extension.png")));
        ui->listWidget->item(11)->setIcon(QIcon::fromTheme("applications-system", QIcon(":/icons/preferences/applications-system.png")));
    }

    Settings settings;
    //GENERAL URLs
    settings.beginGroup("Web-URL-Settings");
    m_homepage = settings.value("homepage", "qupzilla:start").toString();
    m_newTabUrl = settings.value("newTabUrl", "qupzilla:speeddial").toString();
    ui->homepage->setText(m_homepage);
    ui->newTabUrl->setText(m_newTabUrl);
    int afterLaunch = settings.value("afterLaunch", 1).toInt();
    settings.endGroup();
    ui->afterLaunch->setCurrentIndex(afterLaunch);
    ui->checkUpdates->setChecked(settings.value("Web-Browser-Settings/CheckUpdates", DEFAULT_CHECK_UPDATES).toBool());
    ui->dontLoadTabsUntilSelected->setChecked(settings.value("Web-Browser-Settings/LoadTabsOnActivation", false).toBool());

#if defined(Q_OS_WIN) && !defined(Q_OS_OS2)
    ui->checkDefaultBrowser->setChecked(settings.value("Web-Browser-Settings/CheckDefaultBrowser", DEFAULT_CHECK_DEFAULTBROWSER).toBool());
    if (mApp->associationManager()->isDefaultForAllCapabilities()) {
        ui->checkNowDefaultBrowser->setText(tr("Default"));
        ui->checkNowDefaultBrowser->setEnabled(false);
    }
    else {
        ui->checkNowDefaultBrowser->setText(tr("Set as default"));
        ui->checkNowDefaultBrowser->setEnabled(true);
        connect(ui->checkNowDefaultBrowser, SIGNAL(clicked()), this, SLOT(makeQupZillaDefault()));
    }
#else // No Default Browser settings on non-Windows platform
    ui->hSpacerDefaultBrowser->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->hLayoutDefaultBrowser->invalidate();
    delete ui->hLayoutDefaultBrowser;
    delete ui->checkDefaultBrowser;
    delete ui->checkNowDefaultBrowser;
#endif

    ui->newTabFrame->setVisible(false);
    if (m_newTabUrl.isEmpty()) {
        ui->newTab->setCurrentIndex(0);
    }
    else if (m_newTabUrl == m_homepage) {
        ui->newTab->setCurrentIndex(1);
    }
    else if (m_newTabUrl == QLatin1String("qupzilla:speeddial")) {
        ui->newTab->setCurrentIndex(2);
    }
    else {
        ui->newTab->setCurrentIndex(3);
        ui->newTabFrame->setVisible(true);
    }

    afterLaunchChanged(ui->afterLaunch->currentIndex());
    connect(ui->afterLaunch, SIGNAL(currentIndexChanged(int)), this, SLOT(afterLaunchChanged(int)));
    connect(ui->newTab, SIGNAL(currentIndexChanged(int)), this, SLOT(newTabChanged(int)));
    if (p_QupZilla) {
        connect(ui->useCurrentBut, SIGNAL(clicked()), this, SLOT(useActualHomepage()));
        connect(ui->newTabUseCurrent, SIGNAL(clicked()), this, SLOT(useActualNewTab()));
    }
    else {
        ui->useCurrentBut->setEnabled(false);
        ui->newTabUseCurrent->setEnabled(false);
    }
    //PROFILES
    m_actProfileName = mApp->currentProfilePath();
    m_actProfileName = m_actProfileName.left(m_actProfileName.length() - 1);
    m_actProfileName = m_actProfileName.mid(m_actProfileName.lastIndexOf(QLatin1Char('/')));
    m_actProfileName.remove(QLatin1Char('/'));

    ui->activeProfile->setText("<b>" + m_actProfileName + "</b>");

    QSettings profileSettings(mApp->PROFILEDIR + "profiles/profiles.ini", QSettings::IniFormat);
    QString actProfileName = profileSettings.value("Profiles/startProfile", "default").toString();

    ui->startProfile->addItem(actProfileName);
    QDir profilesDir(mApp->PROFILEDIR + "profiles/");
    QStringList list_ = profilesDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (const QString &name, list_) {
        if (actProfileName == name) {
            continue;
        }

        ui->startProfile->addItem(name);
    }
    connect(ui->createProfile, SIGNAL(clicked()), this, SLOT(createProfile()));
    connect(ui->deleteProfile, SIGNAL(clicked()), this, SLOT(deleteProfile()));
    connect(ui->startProfile, SIGNAL(currentIndexChanged(QString)), this, SLOT(startProfileIndexChanged(QString)));
    startProfileIndexChanged(ui->startProfile->currentText());

    //APPEREANCE
    settings.beginGroup("Browser-View-Settings");
    ui->showStatusbar->setChecked(settings.value("showStatusBar", true).toBool());
    if (p_QupZilla) {
        ui->showBookmarksToolbar->setChecked(p_QupZilla->bookmarksToolbar()->isVisible());
        ui->showNavigationToolbar->setChecked(p_QupZilla->navigationBar()->isVisible());
    }
    else {
        ui->showBookmarksToolbar->setChecked(settings.value("showBookmarksToolbar", true).toBool());
        ui->showNavigationToolbar->setChecked(settings.value("showNavigationToolbar", true).toBool());
    }
    ui->showHome->setChecked(settings.value("showHomeButton", true).toBool());
    ui->showBackForward->setChecked(settings.value("showBackForwardButtons", true).toBool());
    ui->showAddTabButton->setChecked(settings.value("showAddTabButton", false).toBool());
    ui->showReloadStopButtons->setChecked(settings.value("showReloadButton", true).toBool());
    ui->showWebSearchBar->setChecked(settings.value("showWebSearchBar", true).toBool());
    ui->useTransparentBg->setChecked(settings.value("useTransparentBackground", false).toBool());
    int currentSettingsPage = settings.value("settingsDialogPage", 0).toInt(0);
    settings.endGroup();
#ifdef Q_OS_WIN
    ui->useTransparentBg->setEnabled(QtWin::isCompositionEnabled());
#endif

    //TABS
    settings.beginGroup("Browser-Tabs-Settings");
    ui->hideTabsOnTab->setChecked(settings.value("hideTabsWithOneTab", false).toBool());
    ui->activateLastTab->setChecked(settings.value("ActivateLastTabWhenClosingActual", false).toBool());
    ui->openNewTabAfterActive->setChecked(settings.value("newTabAfterActive", true).toBool());
    ui->openNewEmptyTabAfterActive->setChecked(settings.value("newEmptyTabAfterActive", false).toBool());
    ui->alwaysSwitchTabsWithWheel->setChecked(settings.value("AlwaysSwitchTabsWithWheel", false).toBool());
    ui->switchToNewTabs->setChecked(settings.value("OpenNewTabsSelected", false).toBool());
    ui->dontQuitOnTab->setChecked(settings.value("dontQuitWithOneTab", false).toBool());
    ui->askWhenClosingMultipleTabs->setChecked(settings.value("AskOnClosing", false).toBool());
    ui->closedInsteadOpened->setChecked(settings.value("closedInsteadOpenedTabs", false).toBool());
    ui->showTabPreviews->setChecked(settings.value("showTabPreviews", true).toBool());
    ui->animatedTabPreviews->setChecked(settings.value("tabPreviewAnimationsEnabled", true).toBool());
    settings.endGroup();

    connect(ui->showTabPreviews, SIGNAL(toggled(bool)), this, SLOT(showTabPreviewsChanged(bool)));
    showTabPreviewsChanged(ui->showTabPreviews->isChecked());

    //AddressBar
    settings.beginGroup("AddressBar");
    ui->addressbarCompletion->setCurrentIndex(settings.value("showSuggestions", 0).toInt());
    ui->useInlineCompletion->setChecked(settings.value("useInlineCompletion", true).toBool());
    ui->completionShowSwitchTab->setChecked(settings.value("showSwitchTab", true).toBool());
    ui->alwaysShowGoIcon->setChecked(settings.value("alwaysShowGoIcon", false).toBool());
    ui->selectAllOnFocus->setChecked(settings.value("SelectAllTextOnDoubleClick", true).toBool());
    ui->selectAllOnClick->setChecked(settings.value("SelectAllTextOnClick", false).toBool());
    ui->addCountryWithAlt->setChecked(settings.value("AddCountryDomainWithAltKey", true).toBool());
    bool showPBinAB = settings.value("ShowLoadingProgress", false).toBool();
    ui->showLoadingInAddressBar->setChecked(showPBinAB);
    ui->adressProgressSettings->setEnabled(showPBinAB);
    ui->progressStyleSelector->setCurrentIndex(settings.value("ProgressStyle", 0).toInt());
    bool pbInABuseCC = settings.value("UseCustomProgressColor", false).toBool();
    ui->checkBoxCustomProgressColor->setChecked(pbInABuseCC);
    ui->progressBarColorSelector->setEnabled(pbInABuseCC);
    QColor pbColor = settings.value("CustomProgressColor", p_QupZilla->palette().color(QPalette::Highlight)).value<QColor>();
    setProgressBarColorIcon(pbColor);
    connect(ui->customColorToolButton, SIGNAL(clicked(bool)), SLOT(selectCustomProgressBarColor()));
    connect(ui->resetProgressBarcolor, SIGNAL(clicked()), SLOT(setProgressBarColorIcon()));
    settings.endGroup();

    settings.beginGroup("SearchEngines");
    ui->searchWithDefaultEngine->setChecked(settings.value("SearchWithDefaultEngine", false).toBool());
    settings.endGroup();

    //BROWSING
    settings.beginGroup("Web-Browser-Settings");
    ui->allowPlugins->setChecked(settings.value("allowFlash", true).toBool());
    ui->allowJavaScript->setChecked(settings.value("allowJavaScript", true).toBool());
    ui->allowJava->setChecked(settings.value("allowJava", true).toBool());
    ui->allowDNSPrefetch->setChecked(settings.value("DNS-Prefetch", false).toBool());
    ui->linksInFocusChain->setChecked(settings.value("IncludeLinkInFocusChain", false).toBool());
    ui->zoomTextOnly->setChecked(settings.value("zoomTextOnly", false).toBool());
    ui->spatialNavigation->setChecked(settings.value("SpatialNavigation", false).toBool());
    ui->caretBrowsing->setChecked(settings.value("CaretBrowsing", false).toBool());
    ui->animateScrolling->setChecked(settings.value("AnimateScrolling", true).toBool());
    ui->printEBackground->setChecked(settings.value("PrintElementBackground", true).toBool());
    ui->wheelScroll->setValue(settings.value("wheelScrollLines", qApp->wheelScrollLines()).toInt());
    ui->defaultZoom->setValue(settings.value("DefaultZoom", 100).toInt());
    ui->xssAuditing->setChecked(settings.value("XSSAuditing", false).toBool());
    ui->formsUndoRedo->setChecked(settings.value("enableFormsUndoRedo", false).toBool());

    //Cache
    ui->pagesInCache->setValue(settings.value("maximumCachedPages", 3).toInt());
    connect(ui->pagesInCache, SIGNAL(valueChanged(int)), this, SLOT(pageCacheValueChanged(int)));
    ui->pageCacheLabel->setText(QString::number(ui->pagesInCache->value()));

    ui->allowCache->setChecked(settings.value("AllowLocalCache", true).toBool());
    ui->cacheMB->setValue(settings.value("LocalCacheSize", 50).toInt());
    ui->MBlabel->setText(settings.value("LocalCacheSize", 50).toString() + " MB");
    ui->cachePath->setText(settings.value("CachePath", QString("%1networkcache/").arg(mApp->currentProfilePath())).toString());
    connect(ui->allowCache, SIGNAL(clicked(bool)), this, SLOT(allowCacheChanged(bool)));
    connect(ui->cacheMB, SIGNAL(valueChanged(int)), this, SLOT(cacheValueChanged(int)));
    connect(ui->changeCachePath, SIGNAL(clicked()), this, SLOT(changeCachePathClicked()));
    allowCacheChanged(ui->allowCache->isChecked());

    //PASSWORD MANAGER
    ui->allowPassManager->setChecked(settings.value("SavePasswordsOnSites", true).toBool());
    connect(ui->allowPassManager, SIGNAL(toggled(bool)), this, SLOT(showPassManager(bool)));

    showPassManager(ui->allowPassManager->isChecked());

    //PRIVACY
    //Web storage
    ui->saveHistory->setChecked(settings.value("allowHistory", true).toBool());
    ui->deleteHistoryOnClose->setChecked(settings.value("deleteHistoryOnClose", false).toBool());
    if (!ui->saveHistory->isChecked()) {
        ui->deleteHistoryOnClose->setEnabled(false);
    }
    connect(ui->saveHistory, SIGNAL(toggled(bool)), this, SLOT(saveHistoryChanged(bool)));

    // Html5Storage
    ui->html5storage->setChecked(settings.value("HTML5StorageEnabled", true).toBool());
    ui->deleteHtml5storageOnClose->setChecked(settings.value("deleteHTML5StorageOnClose", false).toBool());
    connect(ui->html5storage, SIGNAL(toggled(bool)), this, SLOT(allowHtml5storageChanged(bool)));
    // Other
    ui->doNotTrack->setChecked(settings.value("DoNotTrack", false).toBool());
    ui->sendReferer->setChecked(settings.value("SendReferer", true).toBool());

    //CSS Style
    ui->userStyleSheet->setText(settings.value("userStyleSheet", "").toString());
    connect(ui->chooseUserStylesheet, SIGNAL(clicked()), this, SLOT(chooseUserStyleClicked()));
    settings.endGroup();

    //DOWNLOADS
    settings.beginGroup("DownloadManager");
    ui->downLoc->setText(settings.value("defaultDownloadPath", "").toString());
    ui->closeDownManOnFinish->setChecked(settings.value("CloseManagerOnFinish", false).toBool());
    ui->downlaodNativeSystemDialog->setChecked(settings.value("useNativeDialog", DEFAULT_DOWNLOAD_USE_NATIVE_DIALOG).toBool());
    if (ui->downLoc->text().isEmpty()) {
        ui->askEverytime->setChecked(true);
    }
    else {
        ui->useDefined->setChecked(true);
    }
    ui->useExternalDownManager->setChecked(settings.value("UseExternalManager", false).toBool());
    ui->externalDownExecutable->setText(settings.value("ExternalManagerExecutable", "").toString());
    ui->externalDownArguments->setText(settings.value("ExternalManagerArguments", "").toString());

    connect(ui->useExternalDownManager, SIGNAL(toggled(bool)), this, SLOT(useExternalDownManagerChanged(bool)));
    connect(ui->useDefined, SIGNAL(toggled(bool)), this, SLOT(downLocChanged(bool)));
    connect(ui->downButt, SIGNAL(clicked()), this, SLOT(chooseDownPath()));
    connect(ui->chooseExternalDown, SIGNAL(clicked()), this, SLOT(chooseExternalDownloadManager()));
    downLocChanged(ui->useDefined->isChecked());
    useExternalDownManagerChanged(ui->useExternalDownManager->isChecked());
    settings.endGroup();

    //FONTS
    settings.beginGroup("Browser-Fonts");
    ui->fontStandard->setCurrentFont(QFont(settings.value("StandardFont", mApp->webSettings()->fontFamily(QWebSettings::StandardFont)).toString()));
    ui->fontCursive->setCurrentFont(QFont(settings.value("CursiveFont", mApp->webSettings()->fontFamily(QWebSettings::CursiveFont)).toString()));
    ui->fontFantasy->setCurrentFont(QFont(settings.value("FantasyFont", mApp->webSettings()->fontFamily(QWebSettings::FantasyFont)).toString()));
    ui->fontFixed->setCurrentFont(QFont(settings.value("FixedFont", mApp->webSettings()->fontFamily(QWebSettings::FixedFont)).toString()));
    ui->fontSansSerif->setCurrentFont(QFont(settings.value("SansSerifFont", mApp->webSettings()->fontFamily(QWebSettings::SansSerifFont)).toString()));
    ui->fontSerif->setCurrentFont(QFont(settings.value("SerifFont", mApp->webSettings()->fontFamily(QWebSettings::SerifFont)).toString()));

    ui->sizeDefault->setValue(settings.value("DefaultFontSize", mApp->webSettings()->fontSize(QWebSettings::DefaultFontSize)).toInt());
    ui->sizeFixed->setValue(settings.value("FixedFontSize", mApp->webSettings()->fontSize(QWebSettings::DefaultFixedFontSize)).toInt());
    ui->sizeMinimum->setValue(settings.value("MinimumFontSize", mApp->webSettings()->fontSize(QWebSettings::MinimumFontSize)).toInt());
    ui->sizeMinimumLogical->setValue(settings.value("MinimumLogicalFontSize", mApp->webSettings()->fontSize(QWebSettings::MinimumLogicalFontSize)).toInt());
    settings.endGroup();

    //KEYBOARD SHORTCUTS
    settings.beginGroup("Shortcuts");
    ui->switchTabsAlt->setChecked(settings.value("useTabNumberShortcuts", true).toBool());
    ui->loadSpeedDialsCtrl->setChecked(settings.value("useSpeedDialNumberShortcuts", true).toBool());
    settings.endGroup();

    //NOTIFICATIONS
    ui->useNativeSystemNotifications->setEnabled(mApp->desktopNotifications()->supportsNativeNotifications());

    DesktopNotificationsFactory::Type notifyType;
    settings.beginGroup("Notifications");
    ui->notificationTimeout->setValue(settings.value("Timeout", 6000).toInt() / 1000);
#ifdef QZ_WS_X11
    notifyType = settings.value("UseNativeDesktop", true).toBool() ? DesktopNotificationsFactory::DesktopNative : DesktopNotificationsFactory::PopupWidget;
#else
    notifyType = DesktopNotificationsFactory::PopupWidget;
#endif
    if (ui->useNativeSystemNotifications->isEnabled() && notifyType == DesktopNotificationsFactory::DesktopNative) {
        ui->useNativeSystemNotifications->setChecked(true);
    }
    else {
        ui->useOSDNotifications->setChecked(true);
    }

    connect(ui->useNativeSystemNotifications, SIGNAL(toggled(bool)), this, SLOT(setNotificationPreviewVisible(bool)));
    connect(ui->useOSDNotifications, SIGNAL(toggled(bool)), this, SLOT(setNotificationPreviewVisible(bool)));

    ui->doNotUseNotifications->setChecked(!settings.value("Enabled", true).toBool());
    m_notifPosition = settings.value("Position", QPoint(10, 10)).toPoint();
    settings.endGroup();

    //OTHER
    //Languages
    QString activeLanguage = mApp->currentLanguage();

    if (!activeLanguage.isEmpty() && activeLanguage != QLatin1String("en_US")) {
        ui->languages->addItem(createLanguageItem(activeLanguage), activeLanguage);
    }

    ui->languages->addItem("English (en_US)");

    QDir lanDir(mApp->TRANSLATIONSDIR);
    QStringList list = lanDir.entryList(QStringList("*.qm"));
    foreach (const QString &name, list) {
        if (name.startsWith(QLatin1String("qt_"))) {
            continue;
        }

        QString loc = name;
        loc.remove(QLatin1String(".qm"));

        if (loc == activeLanguage) {
            continue;
        }

        ui->languages->addItem(createLanguageItem(loc), loc);
    }

    // Proxy Configuration
    settings.beginGroup("Web-Proxy");
    NetworkProxyFactory::ProxyPreference proxyPreference = NetworkProxyFactory::ProxyPreference(settings.value("UseProxy", NetworkProxyFactory::SystemProxy).toInt());
    QNetworkProxy::ProxyType proxyType = QNetworkProxy::ProxyType(settings.value("ProxyType", QNetworkProxy::HttpProxy).toInt());

    ui->systemProxy->setChecked(proxyPreference == NetworkProxyFactory::SystemProxy);
    ui->noProxy->setChecked(proxyPreference == NetworkProxyFactory::NoProxy);
    ui->manualProxy->setChecked(proxyPreference == NetworkProxyFactory::DefinedProxy);
    ui->pacProxy->setChecked(proxyPreference == NetworkProxyFactory::ProxyAutoConfig);
    if (proxyType == QNetworkProxy::HttpProxy) {
        ui->proxyType->setCurrentIndex(0);
    }
    else {
        ui->proxyType->setCurrentIndex(1);
    }

    ui->proxyServer->setText(settings.value("HostName", "").toString());
    ui->proxyPort->setText(settings.value("Port", 8080).toString());
    ui->proxyUsername->setText(settings.value("Username", "").toString());
    ui->proxyPassword->setText(settings.value("Password", "").toString());

    ui->useHttpsProxy->setChecked(settings.value("UseDifferentProxyForHttps", false).toBool());
    ui->httpsProxyServer->setText(settings.value("HttpsHostName", "").toString());
    ui->httpsProxyPort->setText(settings.value("HttpsPort", 8080).toString());
    ui->httpsProxyUsername->setText(settings.value("HttpsUsername", "").toString());
    ui->httpsProxyPassword->setText(settings.value("HttpsPassword", "").toString());

    ui->pacUrl->setText(settings.value("PacUrl", QUrl()).toUrl().toString());
    ui->proxyExceptions->setText(settings.value("ProxyExceptions", QStringList() << "localhost" << "127.0.0.1").toStringList().join(","));
    settings.endGroup();

    useDifferentProxyForHttpsChanged(ui->useHttpsProxy->isChecked());
    setManualProxyConfigurationEnabled(proxyPreference == NetworkProxyFactory::DefinedProxy);
    setProxyAutoConfigEnabled(proxyPreference == NetworkProxyFactory::ProxyAutoConfig);

    connect(ui->manualProxy, SIGNAL(toggled(bool)), this, SLOT(setManualProxyConfigurationEnabled(bool)));
    connect(ui->pacProxy, SIGNAL(toggled(bool)), this, SLOT(setProxyAutoConfigEnabled(bool)));
    connect(ui->useHttpsProxy, SIGNAL(toggled(bool)), this, SLOT(useDifferentProxyForHttpsChanged(bool)));
    connect(ui->reloadPac, SIGNAL(clicked()), this, SLOT(reloadPacFileClicked()));

    //CONNECTS
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonClicked(QAbstractButton*)));
    connect(ui->cookieManagerBut, SIGNAL(clicked()), this, SLOT(showCookieManager()));
    connect(ui->html5permissions, SIGNAL(clicked()), this, SLOT(showHtml5Permissions()));
    connect(ui->sslManagerButton, SIGNAL(clicked()), this, SLOT(openSslManager()));
    connect(ui->preferredLanguages, SIGNAL(clicked()), this, SLOT(showAcceptLanguage()));
    connect(ui->deleteHtml5storage, SIGNAL(clicked()), this, SLOT(deleteHtml5storage()));
    connect(ui->uaManager, SIGNAL(clicked()), this, SLOT(openUserAgentManager()));
    connect(ui->jsOptionsButton, SIGNAL(clicked()), this, SLOT(openJsOptions()));

    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(showStackedPage(QListWidgetItem*)));
    ui->listWidget->setItemSelected(ui->listWidget->itemAt(5, 5), true);

    ui->version->setText(" QupZilla v" + QupZilla::VERSION);
    ui->listWidget->setCurrentRow(currentSettingsPage);

    QDesktopWidget* desktop = QApplication::desktop();
    QSize s = size();
    if (desktop->availableGeometry(this).size().width() < s.width()) {
        s.setWidth(desktop->availableGeometry(this).size().width() - 50);
    }
    if (desktop->availableGeometry(this).size().height() < s.height()) {
        s.setHeight(desktop->availableGeometry(this).size().height() - 50);
    }
    resize(s);

#if QTWEBKIT_TO_2_3
    ui->caretBrowsing->setHidden(true);
    ui->animateScrolling->setHidden(true);
#endif

#if QTWEBKIT_TO_2_2
    ui->html5permissions->setDisabled(true);
#endif

    QzTools::setWmClass("Preferences", this);
}