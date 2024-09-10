QWizardPage *AuthenticationWizard::createSSPage()
{
	QWizardPage *page = new QWizardPage();
	QGridLayout *layout = new QGridLayout();
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0);

	if(initiate) {
		page->setTitle(i18nc("@title", "Shared Secret"));

		layout->addWidget(new QLabel(i18nc("@info", "Enter a secret passphrase known only to you and <b>%1</b>:", contact)));
	} else {
        page->setTitle(i18nc("@title", "Authentication with <b>%1</b>", contact));
		layout->addWidget(new QLabel(i18nc("@info", "Enter the secret passphrase known only to you and <b>%1</b>:", contact)));
	}
	leSecret = new QLineEdit();
	layout->addWidget(leSecret);

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 0);
	page->setLayout(layout);
	page->setCommitPage(true);
	return page;
}