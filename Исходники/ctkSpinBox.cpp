//-----------------------------------------------------------------------------
void ctkSpinBoxPrivate::init()
{
  Q_Q(ctkSpinBox);
  this->SpinBox = new QDoubleSpinBox(q);
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
}