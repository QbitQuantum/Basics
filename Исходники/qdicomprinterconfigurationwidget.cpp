// Private Methods
void QDicomPrinterConfigurationWidget::createConnections()
{
    connect(m_addPrinterPushButton, SIGNAL(clicked()), SLOT(addPrinter()));
    connect(m_applySettingsPushButton, SIGNAL(clicked()), SLOT(modifyPrinter()));
    connect(m_acceptSettingsPushButton, SIGNAL(clicked()), SLOT(accept()));
    connect(m_cancelSettingsPushButton, SIGNAL(clicked()), SLOT(cancel()));
    connect(m_deletePrinterPushButton, SIGNAL(clicked()), SLOT(deletePrinter()));
    connect(m_testPrinterPushButton, SIGNAL(clicked()), SLOT(testPrinter()));

    connect(m_listPrintersTreeWidget, SIGNAL(itemSelectionChanged()), SLOT(printerSelectionChanged()));
    connect(m_addPrinterWidget, SIGNAL(newPrinterAddedSignal(int)), SLOT(showNewPrinterAdded(int)));
    connect(m_magnifactionTypeComboBox, SIGNAL(currentIndexChanged (const QString)), SLOT(m_magnitifacationTypeComboBoxIndexChanged(const QString)));
    connect(m_supportsAnnotationBoxYesRadioButton, SIGNAL(toggled(bool)), SLOT(m_supportsAnnotationBoxYesRadioButtonToogled()));
}