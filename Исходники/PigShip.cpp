void CPigShip::KillAutoAction()
{
    // Reset the AutoPilot flag
    m_pPig->BaseClient::SetAutoPilot(false);

    // Disconnect any current action event object
    if (NULL != m_spAutoAction && m_spDummyEvent != m_spAutoAction)
    {
        // Release external references to the object
        CoDisconnectObject(m_spAutoAction, 0);

        // Kill the action event object
        m_spAutoAction->Kill();

        // Release the object and replace it with the dummy event
        m_spAutoAction = m_spDummyEvent;
    }
}