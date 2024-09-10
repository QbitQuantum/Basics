EulaDialog::EulaDialog(QWidget* parent) : QWizard(parent) {
  setWindowTitle(trEulaTitle);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  //// First page
  QWizardPage* firstPage = new QWizardPage;

  QRadioButton* agreeButton = new QRadioButton(trIAgree);
  VERIFY(connect(agreeButton, &QRadioButton::clicked, this, &EulaDialog::agreeButtonClicked));

  QRadioButton* notAgreeButton = new QRadioButton(trIDontAgree);
  notAgreeButton->setChecked(true);
  VERIFY(connect(notAgreeButton, &QRadioButton::clicked, this, &EulaDialog::notAgreeButtonClicked));

  QHBoxLayout* radioButtonsLay = new QHBoxLayout;
  radioButtonsLay->setAlignment(Qt::AlignHCenter);
  radioButtonsLay->setSpacing(30);
  radioButtonsLay->addWidget(agreeButton);
  radioButtonsLay->addWidget(notAgreeButton);

  QTextEdit* textBrowser = new QTextEdit;
  QFile file(":" PROJECT_NAME_LOWERCASE "/LICENSE");
  if (file.open(QFile::ReadOnly | QFile::Text)) {
    textBrowser->setHtml(file.readAll());
  }

  QVBoxLayout* mainLayout1 = new QVBoxLayout;
  mainLayout1->addWidget(new QLabel("<h3>" + trEndUserAgr + "</h3>"));
  mainLayout1->addWidget(textBrowser);
  mainLayout1->addLayout(radioButtonsLay, Qt::AlignCenter);
  firstPage->setLayout(mainLayout1);

  addPage(firstPage);

  //// Buttons
  setButtonText(QWizard::CustomButton1, trBack);
  setButtonText(QWizard::CustomButton2, trNext);
  setButtonText(QWizard::CustomButton3, trFinish);

  VERIFY(connect(button(QWizard::CustomButton1), &QAbstractButton::clicked, this, &EulaDialog::backButtonClicked));
  VERIFY(connect(button(QWizard::CustomButton2), &QAbstractButton::clicked, this, &EulaDialog::nextButtonClicked));
  VERIFY(connect(button(QWizard::CustomButton3), &QAbstractButton::clicked, this, &EulaDialog::finishButtonClicked));

  setButtonLayout(QList<WizardButton>{QWizard::Stretch, QWizard::CustomButton1, QWizard::CustomButton2,
                                      QWizard::CancelButton, QWizard::CustomButton3});

  button(QWizard::CustomButton1)->setHidden(true);
  button(QWizard::CustomButton2)->setHidden(true);
  button(QWizard::CustomButton3)->setDisabled(true);
  setWizardStyle(QWizard::ModernStyle);
}