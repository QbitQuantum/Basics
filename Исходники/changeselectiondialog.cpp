ChangeSelectionDialog::~ChangeSelectionDialog()
{
    terminateProcess();
    delete m_ui;
}