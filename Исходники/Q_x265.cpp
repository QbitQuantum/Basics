/**
    \fn getProfileName  
    \brief Popup a dialog that asks the user the preset name
*/
static char *getProfileName(void)
{
  QDialog dialog;
  dialog.setWindowTitle(QString::fromUtf8("Save Profile"));
  QDialogButtonBox *buttonBox = new QDialogButtonBox();  
  QVBoxLayout *vboxLayout = new QVBoxLayout();
  buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  QObject::connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  QLineEdit *text=new QLineEdit;
//  text->setAcceptRichText(false);
  
  text->setText("my profile");
  text->selectAll();

  vboxLayout->addWidget(text);
  vboxLayout->addWidget(buttonBox);

  dialog.setLayout(vboxLayout);

  if(dialog.exec()!=QDialog::Accepted)
  {
        ADM_info("Canceled");
        return NULL;
  }
  QString fileName=text->text();
  const char *out=fileName.toUtf8().constData();
  return ADM_strdup(out);
}