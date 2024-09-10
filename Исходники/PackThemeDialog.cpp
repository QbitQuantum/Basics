PackThemeDialog::PackThemeDialog(QWidget * pParent, KviPointerList<KviThemeInfo> * pThemeInfoList)
: QWizard(pParent)
{
	setWindowTitle(__tr2qs_ctx("Export Theme - KVIrc","theme"));
	setMinimumSize(400,350);
	setDefaultProperty("QTextEdit","plainText",SIGNAL(textChanged()));
	m_pThemeInfoList = pThemeInfoList;

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
	pPage->setTitle(__tr2qs_ctx("Welcome","theme"));

	QString szText = "<p>";
	szText += __tr2qs_ctx("This procedure allows you to export the selected themes to a single package. It is useful when you want to distribute your themes to the public.","theme");
	szText += "</p><p>";
	szText += __tr2qs_ctx("You will be asked to provide a package name, a description and, if you want, an icon/screenshot.","theme");
	szText += "</p><p>";
	szText += __tr2qs_ctx("Hit the \"Next\" button to begin.","theme");
	szText += "<p>";

	QLabel * pLabel = new QLabel(pPage);
	pLabel->setWordWrap(true);
	pLabel->setText(szText);
	pLayout->addWidget(pLabel);
	addPage(pPage);

	// Theme data
	m_pPackThemeDataWidget = new PackThemeDataWidget(this);
	addPage(m_pPackThemeDataWidget);

	// Packager information
	m_pPackThemeInfoWidget = new PackThemeInfoWidget(this);
	addPage(m_pPackThemeInfoWidget);

	// Screenshot/logo/icon
	m_pPackThemeImageWidget = new PackThemeImageWidget(this);
	addPage(m_pPackThemeImageWidget);

	// Save file name
	m_pPackThemeSaveWidget = new PackThemeSaveWidget(this);
	addPage(m_pPackThemeSaveWidget);

	//last thing to do before starting
	m_pPackThemeDataWidget->parseThemes(m_pThemeInfoList);
}