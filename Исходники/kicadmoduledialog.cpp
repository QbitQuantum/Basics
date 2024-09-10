KicadModuleDialog::KicadModuleDialog(const QString & partType, const QString & filename, const QStringList & modules, QWidget *parent) : QDialog(parent) 
{
	this->setWindowTitle(QObject::tr("Select %1").arg(partType));

	QVBoxLayout * vLayout = new QVBoxLayout(this);

	QFrame * frame = new QFrame(this);

	QFormLayout * formLayout = new QFormLayout();

	m_comboBox = new QComboBox(this);
	m_comboBox->addItems(modules);
	formLayout->addRow(QString("%1:").arg(partType), m_comboBox );

	frame->setLayout(formLayout);

	QLabel * label = new QLabel(QString("There are %1 %3 descriptions in '%2'.  Please select one.").arg(modules.count()).arg(filename).arg(partType));
	vLayout->addWidget(label);

	vLayout->addWidget(frame);

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
	buttonBox->button(QDialogButtonBox::Ok)->setText(tr("OK"));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	vLayout->addWidget(buttonBox);

	this->setLayout(vLayout);
}