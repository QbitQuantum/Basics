QWizardPage *IrcConnectionWizard::createIntroductionPage(QWidget *parent)
{
    QWizardPage *page = new QWizardPage(parent);
    page->setTitle(QObject::tr("Welcome to Quassel IRC"));

    QLabel *label = new QLabel(QObject::tr("This wizard will help you to set up your default identity and your IRC network connection.<br>"
                                           "This only covers basic settings. You can cancel this wizard any time and use the settings dialog for more detailed changes."), page);
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}