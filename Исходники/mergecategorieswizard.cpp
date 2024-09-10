QWizardPage* MergeCategoriesWizard::createFinishedPage()
{
  QWizardPage *finished = new QWizardPage(this);
  QHBoxLayout *lay = new QHBoxLayout(finished);
  QLabel *desc = new QLabel(finished);
  lay->addWidget(desc);
  finished->setLayout(lay);

  desc->setWordWrap(true);
  finished->setTitle(i18n("Import completed"));
  desc->setText(i18n("The categories have been merged.\n\nThank you for improving Simon."));

  return finished;
}