void UIVMCloseDialog::configure()
{
    /* Get actual machine-state: */
    KMachineState machineState = m_machine.GetState();

    /* Assign pixmap: */
    setPixmap(vboxGlobal().vmGuestOSTypeIcon(m_machine.GetOSTypeId()));

    /* Check which close-actions are resticted: */
    bool fIsDetachAllowed = vboxGlobal().isSeparateProcess() && !(m_restictedCloseActions & MachineCloseAction_Detach);
    bool fIsStateSavingAllowed = !(m_restictedCloseActions & MachineCloseAction_SaveState);
    bool fIsACPIShutdownAllowed = !(m_restictedCloseActions & MachineCloseAction_Shutdown);
    bool fIsPowerOffAllowed = !(m_restictedCloseActions & MachineCloseAction_PowerOff);
    bool fIsPowerOffAndRestoreAllowed = fIsPowerOffAllowed && !(m_restictedCloseActions & MachineCloseAction_PowerOff_RestoringSnapshot);

    /* Make 'Detach' button visible/hidden depending on restriction: */
    setDetachButtonVisible(fIsDetachAllowed);
    /* Make 'Detach' button enabled/disabled depending on machine-state: */
    setDetachButtonEnabled(machineState != KMachineState_Stuck);

    /* Make 'Save state' button visible/hidden depending on restriction: */
    setSaveButtonVisible(fIsStateSavingAllowed);
    /* Make 'Save state' button enabled/disabled depending on machine-state: */
    setSaveButtonEnabled(machineState != KMachineState_Stuck);

    /* Make 'Shutdown' button visible/hidden depending on restriction: */
    setShutdownButtonVisible(fIsACPIShutdownAllowed);
    /* Make 'Shutdown' button enabled/disabled depending on console and machine-state: */
    setShutdownButtonEnabled(m_fIsACPIEnabled && machineState != KMachineState_Stuck);

    /* Make 'Power off' button visible/hidden depending on restriction: */
    setPowerOffButtonVisible(fIsPowerOffAllowed);
    /* Make the Restore Snapshot checkbox visible/hidden depending on snapshot count & restrictions: */
    setDiscardCheckBoxVisible(fIsPowerOffAndRestoreAllowed && m_machine.GetSnapshotCount() > 0);
    /* Assign Restore Snapshot checkbox text: */
    if (!m_machine.GetCurrentSnapshot().isNull())
        m_strDiscardCheckBoxText = m_machine.GetCurrentSnapshot().GetName();

    /* Check which radio-button should be initially chosen: */
    QRadioButton *pRadioButtonToChoose = 0;
    /* If choosing 'last choice' is possible: */
    m_lastCloseAction = gEDataManager->lastMachineCloseAction(vboxGlobal().managedVMUuid());
    if (m_lastCloseAction == MachineCloseAction_Detach && fIsDetachAllowed)
    {
        pRadioButtonToChoose = m_pDetachRadio;
    }
    else if (m_lastCloseAction == MachineCloseAction_SaveState && fIsStateSavingAllowed)
    {
        pRadioButtonToChoose = m_pSaveRadio;
    }
    else if (m_lastCloseAction == MachineCloseAction_Shutdown && fIsACPIShutdownAllowed && m_fIsACPIEnabled)
    {
        pRadioButtonToChoose = m_pShutdownRadio;
    }
    else if (m_lastCloseAction == MachineCloseAction_PowerOff && fIsPowerOffAllowed)
    {
        pRadioButtonToChoose = m_pPowerOffRadio;
    }
    else if (m_lastCloseAction == MachineCloseAction_PowerOff_RestoringSnapshot && fIsPowerOffAndRestoreAllowed)
    {
        pRadioButtonToChoose = m_pPowerOffRadio;
        m_pDiscardCheckBox->setChecked(true);
    }
    /* Else 'default choice' will be used: */
    else
    {
        if (fIsDetachAllowed)
            pRadioButtonToChoose = m_pDetachRadio;
        else if (fIsStateSavingAllowed)
            pRadioButtonToChoose = m_pSaveRadio;
        else if (fIsACPIShutdownAllowed && m_fIsACPIEnabled)
            pRadioButtonToChoose = m_pShutdownRadio;
        else if (fIsPowerOffAllowed)
            pRadioButtonToChoose = m_pPowerOffRadio;
    }

    /* If some radio-button chosen: */
    if (pRadioButtonToChoose)
    {
        /* Check and focus it: */
        pRadioButtonToChoose->setChecked(true);
        pRadioButtonToChoose->setFocus();
        sltUpdateWidgetAvailability();
        m_fValid = true;
    }
}