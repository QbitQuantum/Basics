FGFSTelnetDialog::FGFSTelnetDialog(QObject* parent){

 QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget((textEdit = new QTextEdit));
  layout->addWidget((lineEdit = new QLineEdit));
  layout->addWidget((connectButton = new QPushButton(tr("Connect"))));
  layout->addWidget((statusLabel = new QLabel(tr("öff"))));
  connectButton->setCheckable(true);
  connectButton->setDefault (false);     // should be default http://doc.trolltech.com/4.2/qpushbutton.html
  connectButton->setAutoDefault (false); // grrr
  textEdit->setReadOnly (true);
  textEdit->setEnabled(true);
  lineEdit->setEnabled(false);

  connect (connectButton, SIGNAL(toggled(bool)),
	   this, SIGNAL (connect_checked(bool)));
  connect (lineEdit, SIGNAL(returnPressed()),
	   this, SLOT(sendInput()));
  setLayout(layout);
  setWindowTitle(tr("FGFS Telnet Example"));
  data.reserve(1024);
}