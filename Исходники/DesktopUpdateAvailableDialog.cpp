DesktopUpdateAvailableDialog::DesktopUpdateAvailableDialog(
                                    const DesktopUpdateInfo& updateInfo,
                                    QWidget *parent) :
      QDialog(parent),
      updateInfo_(updateInfo),
      ui(new Ui::DesktopUpdateAvailableDialog())
{
   ui->setupUi(this);
   ui->lblIcon->setFixedSize(QSize(64, 64));
   ui->label->setText(updateInfo.updateMessage);

   ui->buttonBox->clear();
   QPushButton* pDownload = new QPushButton(QString::fromUtf8("Download..."));
   ui->buttonBox->addButton(pDownload, QDialogButtonBox::AcceptRole);
   pDownload->setAutoDefault(false);
   pDownload->setDefault(true);

   QPushButton* pRemindLater = new QPushButton(QString::fromUtf8("Remind Later"));
   ui->buttonBox->addButton(pRemindLater, QDialogButtonBox::RejectRole);
   pRemindLater->setAutoDefault(false);

   QPushButton* pIgnoreUpdate = new QPushButton(QString::fromUtf8("Ignore Update"));
   ui->buttonBox->addButton(pIgnoreUpdate, QDialogButtonBox::DestructiveRole);
   pIgnoreUpdate->setAutoDefault(false);
   pIgnoreUpdate->setEnabled(!updateInfo.isUrgent);
   connect(pIgnoreUpdate, SIGNAL(clicked()),
           this, SLOT(permanentlyIgnoreUpdate()));

   pRemindLater->setFocus();
}