void View::Management::ProductDialog::createWidgets()
{
    _idLabel = new QLabel(tr("&Id:"));
    _idLineEdit = new QLineEdit;
    _idLineEdit -> setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]*"), this));
    _idLabel -> setBuddy(_idLineEdit);
    _autoIdCheckBox = new QCheckBox(tr("Auto &Generate"));

    _nameLabel = new QLabel(tr("&Name:"));
    _nameLineEdit = new QLineEdit;
    _nameLabel -> setBuddy(_nameLineEdit);

    _categoryLabel = new QLabel(tr("&Category:"));
    _categoryComboBox = new QComboBox;
    _categoryComboBox -> addItems(Model::Management::CategoryManager::getAllNames().keys());
    _categoryLabel -> setBuddy(_categoryComboBox);

    _descriptionLabel = new QLabel(tr("&Description:"));
    _descriptionTextEdit = new QTextEdit;
    _descriptionLabel -> setBuddy(_descriptionTextEdit);
    _descriptionTextEdit->setMaximumHeight(50);

    _priceLabel = new QLabel(tr("&Price:"));
    _priceLineEdit = new QLineEdit;
    _priceLineEdit -> setValidator(new QRegExpValidator(QRegExp("[0-9]+(.[0-9]+)?"), this));
    _priceLabel -> setBuddy(_priceLineEdit);

    _priceTypeLabel = new QLabel(tr("&Type:"));
    _priceTypeComboBox = new QComboBox;
    _priceTypeComboBox -> addItems(QStringList() << tr("Units") << tr("Weight"));
    _priceTypeLabel -> setBuddy(_priceTypeComboBox);

    QGridLayout *topLayout = new QGridLayout;
    topLayout -> addWidget(_idLabel, 0, 0, 1, 1);
    topLayout -> addWidget(_idLineEdit, 0, 1, 1, 1);
    topLayout -> addWidget(_autoIdCheckBox, 0, 2, 1, 2);
    topLayout -> addWidget(_nameLabel, 1, 0, 1, 1);
    topLayout -> addWidget(_nameLineEdit, 1, 1, 1, 3);
    topLayout -> addWidget(_categoryLabel, 2, 0, 1, 1);
    topLayout -> addWidget(_categoryComboBox, 2, 1, 1, 2);
    topLayout -> addWidget(_descriptionLabel, 3, 0, 1, 2);
    topLayout -> addWidget(_descriptionTextEdit, 4, 0, 1, 4);
    topLayout -> addWidget(_priceLabel, 5, 0, 1, 1);
    topLayout -> addWidget(_priceLineEdit, 5, 1, 1, 1);
    topLayout -> addWidget(_priceTypeLabel, 5, 2, 1, 1);
    topLayout -> addWidget(_priceTypeComboBox, 5, 3, 1, 1);

    _saveButton = new QPushButton(tr("&Save"));
    _saveButton -> setIcon(QIcon(":/images/save.png"));
    _saveButton -> setDefault(true);
    _saveButton -> setEnabled(false);
    _cancelButton = new QPushButton(tr("&Cancel"));
    _cancelButton -> setIcon(QIcon(":/images/cancel.png"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addStretch();
    bottomLayout -> addWidget(_saveButton);
    bottomLayout -> addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addLayout(topLayout);
    mainLayout -> addLayout(bottomLayout);

    setLayout(mainLayout);
}