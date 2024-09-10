PackAddonDialog::PackAddonDialog(QWidget * pParent)
: QWizard(pParent)
{
	setMinimumSize(400,350);
	setObjectName("addon_package_wizard");
	setOption(QWizard::IndependentPages,true);
	setWindowTitle(__tr2qs_ctx("Create Addon Package - KVIrc","addon"));

	QPixmap * pSide = g_pIconManager->getBigIcon("kvi_setup_label.png");
	QPixmap * pLogo = g_pIconManager->getBigIcon("kvi_bigicon_addons.png");

#if defined(COMPILE_ON_WINDOWS) || defined(COMPILE_ON_MINGW)
	#if (_WIN32_WINNT >= 0x0600)
		// We are on a Windows Vista / Seven
		// It will fallback to XP if alpha compositing is disabled
		setWizardStyle(QWizard::AeroStyle);
	#else
		// Windows XP
		setWizardStyle(QWizard::ModernStyle);
		setPixmap(QWizard::WatermarkPixmap,*pSide);
		setPixmap(QWizard::LogoPixmap,*pLogo);
	#endif
#elif defined(COMPILE_ON_MAC)
	setWizardStyle(QWizard::MacStyle);
	setPixmap(QWizard::BackgroundPixmap,*pSide);
#else
	// All other systems
	setWizardStyle(QWizard::ClassicStyle);
	setPixmap(QWizard::WatermarkPixmap,*pSide);
	setPixmap(QWizard::LogoPixmap,*pLogo);
#endif

	// Add a default property for file selectors
	setDefaultProperty("KviFileSelector","tmpFile",SIGNAL(selectionChanged(const QString &)));

	// Welcome page
	QWizardPage * pPage = new QWizardPage(this);
	QVBoxLayout * pLayout = new QVBoxLayout(pPage);

	pPage->setLayout(pLayout);
	pPage->setTitle(__tr2qs_ctx("Welcome","addon"));

	QLabel * pLabel = new QLabel(pPage);
	pLabel->setWordWrap(true);
	pLabel->setText(__tr2qs_ctx("This procedure allows you to export the selected addon to a single package.<br>It is useful when you want to distribute your addon to the public.","addon"));
	pLayout->addWidget(pLabel);

	pLabel = new QLabel(pPage);
	pLabel->setWordWrap(true);
	QString szText;
	szText += __tr2qs_ctx("You will be asked to provide some information like the package name, the version, a description and so on.","addon");
	szText += "<br><br>";
	szText += __tr2qs_ctx("Hit the \"Next\" button to begin.","addon");
	pLabel->setText(szText);
	pLayout->addWidget(pLabel);

	pPage->setMinimumWidth(350);

	addPage(pPage);

	// Packager information
	m_pPackAddonInfoPackageWidget = new PackAddonInfoPackageWidget(this);
	addPage(m_pPackAddonInfoPackageWidget);

	// File selection
	m_pPackAddonFileSelectionWidget = new PackAddonFileSelectionWidget(this);
	addPage(m_pPackAddonFileSelectionWidget);

	// Save selection
	m_pPackAddonSaveSelectionWidget = new PackAddonSaveSelectionWidget(this);
	addPage(m_pPackAddonSaveSelectionWidget);

	// Summary info
	m_pPackAddonSummaryInfoWidget = new PackAddonSummaryInfoWidget(this);
	addPage(m_pPackAddonSummaryInfoWidget);

}