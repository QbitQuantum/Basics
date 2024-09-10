bool OpenCLTraceOptions::AreSettingsValid(gtString& invalidMessageStr)
{
    if (m_pAPIsToTraceRB->isChecked() &&
        (Util::ItemsSelectedInTreeWidget(m_pAPIsToTraceTW) == 0))
    {
        invalidMessageStr = L"At least one item under \"APIs to trace\" must be selected.";
        return false;
    }

    SaveCurrentSettings();
    return true;
}