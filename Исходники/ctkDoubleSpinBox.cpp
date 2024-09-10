//-----------------------------------------------------------------------------
void ctkDoubleSpinBoxPrivate::init()
{
  Q_Q(ctkDoubleSpinBox);
  this->SpinBox = new ctkQDoubleSpinBox(this, q);
  this->SpinBox->setInvertedControls(this->InvertedControls);
  // ctkQDoubleSpinBox needs to be first to receive textChanged() signals.
  QLineEdit* lineEdit = new QLineEdit(q);
  QObject::connect(lineEdit, SIGNAL(textChanged(QString)),
                   this, SLOT(editorTextChanged(QString)));
  this->SpinBox->setLineEdit(lineEdit);
  lineEdit->setObjectName(QLatin1String("qt_spinbox_lineedit"));

  QObject::connect(this->SpinBox, SIGNAL(valueChanged(double)),
    q, SIGNAL(valueChanged(double)));
  QObject::connect(this->SpinBox, SIGNAL(valueChanged(const QString&)),
    q, SIGNAL(valueChanged(const QString &)));
  QObject::connect(this->SpinBox, SIGNAL(editingFinished()),
    q, SIGNAL(editingFinished()));

  QHBoxLayout* l = new QHBoxLayout(q);
  l->addWidget(this->SpinBox);
  l->setContentsMargins(0,0,0,0);
  q->setLayout(l);
  q->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,
    QSizePolicy::Fixed, QSizePolicy::ButtonBox));

  this->SpinBox->installEventFilter(q);
}