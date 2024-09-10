DisplayDialog::DisplayDialog(QWidget *parent)
                     : QDialog(parent)
{
  vLayout = new QVBoxLayout(this);
  setAttribute( Qt::WA_DeleteOnClose  );
  Text = new QTextEdit(this);
  //Text->setTextFormat(Qt::PlainText);
  Text->setReadOnly(true);
  Text->setMinimumSize(200, 100);
  vLayout->addWidget(Text);

  QHBoxLayout *h = new QHBoxLayout(this);
  vLayout->addLayout(h);

	QWidget *w1 = new QWidget(this);
	h->addWidget( w1 );
  h->setStretchFactor(w1,5); // stretchable placeholder

  QPushButton *ButtonClose = new QPushButton(tr("Close"), this);
	h->addWidget( ButtonClose );
  connect(ButtonClose, SIGNAL(clicked()), SLOT(slotClose()));
  ButtonClose->setFocus();

	QWidget *w2= new QWidget(this);
	h->addWidget( w2 );
  h->setStretchFactor(w2,5); // stretchable placeholder
}