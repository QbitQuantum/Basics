QWizardPage* FirstRunWizard::createIntroPage()
{
  QWizardPage *intro = new QWizardPage(this);
  QHBoxLayout *lay = new QHBoxLayout(intro);
  QLabel *desc = new QLabel(intro);
  lay->addWidget(desc);
  intro->setLayout(lay);

  desc->setWordWrap(true);
  intro->setTitle(i18n("Welcome to Simon"));
  desc->setOpenExternalLinks(true);
  desc->setText(i18n("<html><head /><body>"
    "<p>Simon is a speech recognition solution enabling you to control your computer with your voice.</p>"
    "<p>This assistant will help you to get Simon up and running.</p>"
    "<p>Go through the following steps carefully and read the instructions.</p>"
    "<p>You can still change these options later (see the manual for more information)."
    "<p>Find more instructions on <a href=\"http://userbase.kde.org/Simon\">our wiki</a>.</p>"
    "</body></html>"));

  return intro;
}