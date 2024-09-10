void VNewFileDialog::setupUI(const QString &p_title,
                             const QString &p_info,
                             const QString &p_defaultName)
{
    QLabel *infoLabel = NULL;
    if (!p_info.isEmpty()) {
        infoLabel = new QLabel(p_info);
    }

    // Name.
    m_nameEdit = new VMetaWordLineEdit(p_defaultName);
    QValidator *validator = new QRegExpValidator(QRegExp(VUtils::c_fileNameRegExp),
                                                 m_nameEdit);
    m_nameEdit->setValidator(validator);
    int dotIndex = p_defaultName.lastIndexOf('.');
    m_nameEdit->setSelection(0, (dotIndex == -1) ? p_defaultName.size() : dotIndex);

    // Template.
    m_templateCB = VUtils::getComboBox();
    m_templateCB->setToolTip(tr("Choose a template (magic word supported)"));
    m_templateCB->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    QPushButton *templateBtn = new QPushButton(VIconUtils::buttonIcon(":/resources/icons/manage_template.svg"),
                                               "");
    templateBtn->setToolTip(tr("Manage Templates"));
    templateBtn->setProperty("FlatBtn", true);
    connect(templateBtn, &QPushButton::clicked,
            this, [this]() {
                QUrl url = QUrl::fromLocalFile(g_config->getTemplateConfigFolder());
                QDesktopServices::openUrl(url);
            });

    QHBoxLayout *tempBtnLayout = new QHBoxLayout();
    tempBtnLayout->addWidget(m_templateCB);
    tempBtnLayout->addWidget(templateBtn);
    tempBtnLayout->addStretch();

    m_templateEdit = new QTextEdit();
    m_templateEdit->setReadOnly(true);

    QVBoxLayout *templateLayout = new QVBoxLayout();
    templateLayout->addLayout(tempBtnLayout);
    templateLayout->addWidget(m_templateEdit);

    m_templateEdit->hide();

    // InsertTitle.
    m_insertTitleCB = new QCheckBox(tr("Insert note name as title (for Markdown only)"));
    m_insertTitleCB->setToolTip(tr("Insert note name into the new note as a title"));
    m_insertTitleCB->setChecked(g_config->getInsertTitleFromNoteName());
    connect(m_insertTitleCB, &QCheckBox::stateChanged,
            this, [this](int p_state) {
                g_config->setInsertTitleFromNoteName(p_state == Qt::Checked);
            });

    QFormLayout *topLayout = new QFormLayout();
    topLayout->addRow(tr("Note &name:"), m_nameEdit);
    topLayout->addWidget(m_insertTitleCB);
    topLayout->addRow(tr("Template:"), templateLayout);

    m_nameEdit->setMinimumWidth(m_insertTitleCB->sizeHint().width());

    m_warnLabel = new QLabel();
    m_warnLabel->setWordWrap(true);
    m_warnLabel->hide();

    // Ok is the default button.
    m_btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(m_btnBox, &QDialogButtonBox::accepted,
            this, [this]() {
                s_lastTemplateFile = m_templateCB->currentData().toString();
                QDialog::accept();
            });
    connect(m_btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QPushButton *okBtn = m_btnBox->button(QDialogButtonBox::Ok);
    okBtn->setProperty("SpecialBtn", true);
    m_templateCB->setMaximumWidth(okBtn->sizeHint().width() * 4);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    if (infoLabel) {
        mainLayout->addWidget(infoLabel);
    }

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_warnLabel);
    mainLayout->addWidget(m_btnBox);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    setWindowTitle(p_title);
}