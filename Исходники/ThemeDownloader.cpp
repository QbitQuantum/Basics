void ThemeDownloader::init() {
  wizard_ = new QWizard();
  
  wizard_->setAttribute(Qt::WA_DeleteOnClose);
  
	//The screen width should be 1100 unless the resolution is too low
	int width = 1100;
	if (BumpTopApp::singleton()->screen_resolution().x < width) {
    width = BumpTopApp::singleton()->screen_resolution().x;
	}
	wizard_->resize(width,BumpTopApp::singleton()->screen_resolution().x * 0.5);

	QPalette palette;
	QBrush brush(QColor(243, 243, 227, 255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Base, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
	QBrush brush1(QColor(240, 240, 240, 255));
	brush1.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
	wizard_->setPalette(palette);
	wizard_->setOptions(QWizard::HelpButtonOnRight);
	
  QWizardPage* page = new QWizardPage(wizard_);
	QVBoxLayout* vertical_layout = new QVBoxLayout(page);

  wizard_->setWindowTitle(QT_TR_NOOP("Customize"));

  web_view_ = new QWebView(page);
  web_view_->page()->setForwardUnsupportedContent(true);
  web_view_->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  vertical_layout->addWidget(web_view_, 200);
  
  progress_bar_ = new QProgressBar(page);
  progress_bar_->setVisible(false);
  progress_bar_->setMinimum(0);
  vertical_layout->addWidget(progress_bar_, 1);
  
  default_status_message_ = QT_TR_NOOP("Download a theme above, and it will be installed");
  status_ = new QLabel(default_status_message_);
  status_->setFont(QFont("Tahoma", 12));
  vertical_layout->addWidget(status_, 0, Qt::AlignRight);

	page->setLayout(vertical_layout);
	wizard_->addPage(page);
	
	button_layout_ = new QList<QWizard::WizardButton>();
	*button_layout_ << QWizard::Stretch << QWizard::CustomButton1 << QWizard::FinishButton;
	wizard_->setButtonLayout(*button_layout_);
  
	wizard_->setButtonText(QWizard::FinishButton, QT_TR_NOOP("Close"));	
	wizard_->setButtonText(QWizard::CustomButton1, QT_TR_NOOP("Go Back"));
  
	wizard_->setWizardStyle(QWizard::ModernStyle);
	wizard_->setOption(QWizard::HaveHelpButton, false);

  QMetaObject::connectSlotsByName(web_view_->page());
  connect(web_view_->page(), SIGNAL(loadStarted()), this, SLOT(loadStarted()));	
  connect(web_view_->page(), SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));	
  connect(web_view_->page(), SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));	
  connect(web_view_->page(), SIGNAL(downloadRequested(const QNetworkRequest &)), this, SLOT(downloadRequested(const QNetworkRequest &)));
  connect(web_view_->page(), SIGNAL(unsupportedContent(QNetworkReply *)), this, SLOT(unsupportedContent(QNetworkReply *)));
  connect(web_view_->page(), SIGNAL(linkClicked(const QUrl &)), this, SLOT(linkClicked(const QUrl &)));
  connect(wizard_, SIGNAL(customButtonClicked(int)), this, SLOT(customButtonClicked(int)));
  connect(wizard_, SIGNAL(finished(int)), this, SLOT(exitDialog(int)));

  web_view_->setUrl(QUrl("http://bumptop.customize.org/"));
}