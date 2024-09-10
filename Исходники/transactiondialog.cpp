TransactionDialog::TransactionDialog(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::TransactionDialog)
{
  ui->setupUi(this);
  ui->actionRunInTerminal->setIcon(IconHelper::getIconTerminal());
  m_runInTerminalButton =
      new QPushButton(IconHelper::getIconTerminal(), StrConstants::getRunInTerminal());
  ui->buttonBox->addButton(m_runInTerminalButton, QDialogButtonBox::AcceptRole);

  QPushButton *yesButton = ui->buttonBox->button(QDialogButtonBox::Yes);
  QPushButton *noButton = ui->buttonBox->button(QDialogButtonBox::No);

  noButton->setFocus();

  connect(m_runInTerminalButton, SIGNAL(clicked()), this,
          SLOT(slotRunInTerminal()));
  connect(yesButton, SIGNAL(clicked()), this, SLOT(slotYes()));
  connect(noButton, SIGNAL(clicked()), this, SLOT(reject()));

  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog |
                 Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

  if(UnixCommand::getLinuxDistro()==ectn_CHAKRA || UnixCommand::getLinuxDistro()==ectn_ARCHBSD)
  {
    removeYesButton();
  }
}