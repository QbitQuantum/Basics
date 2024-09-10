void TagValueConfigurableSplitter::configureWithGUI()
{
    QDialog* dialog = new QDialog(qApp->activeWindow());
    dialog->setWindowTitle(QString("Configure"));
    QVBoxLayout* mainLayout = new QVBoxLayout();
    dialog->setLayout(mainLayout);
    dialog->setMinimumWidth(500);

    // Create tag selectors
    ::fwDicomIOFilterQt::widget::QTagSelectorWidget* tagSelector =
        new ::fwDicomIOFilterQt::widget::QTagSelectorWidget();
    tagSelector->setTagValue(m_tag);
    mainLayout->addWidget(tagSelector);

    // Create buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(dialog);
    mainLayout->addWidget(buttonBox);
    QPushButton* okButton     = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton* cancelButton = buttonBox->addButton(QDialogButtonBox::Cancel);

    QObject::connect(okButton, SIGNAL(clicked(void)), dialog, SLOT(accept(void)));
    QObject::connect(cancelButton, SIGNAL(clicked(void)), dialog, SLOT(reject(void)));


    int result = dialog->exec();
    if(result == QDialog::Accepted)
    {
        m_tag = tagSelector->getTag();
    }
}