DataSourceDialog::DataSourceDialog(DataDialog::EditMode mode, DataSourcePtr dataSource, QWidget *parent)
  : QDialog(parent), _dataSource(dataSource) {

  setWindowTitle(QString("Configure %1").arg(_dataSource->fileType()));

  QVBoxLayout *layout = new QVBoxLayout(this);

  _dataSource->readLock();
  QWidget *widget = _dataSource->configWidget();
  connect(this, SIGNAL(ok()), widget, SLOT(save()));

  if (mode == DataDialog::Edit) {
    connect(this, SIGNAL(ok()), this, SLOT(disableReuse()));
  }

  _dataSource->unlock();

  widget->setParent(this);
  layout->addWidget(widget);

  _buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  layout->addWidget(_buttonBox);

  connect(_buttonBox, SIGNAL(clicked(QAbstractButton *)),
          this, SLOT(buttonClicked(QAbstractButton *)));

  setLayout(layout);

  setMaximumSize(QSize(1024, 768));
  resize(minimumSizeHint());
}