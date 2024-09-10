void dxThreadPoolThreadInfo::ExecuteThreadCommand(dxTHREADCOMMAND command, void *param, bool wait_response)
{
    bool acknowledgement_wait_result = m_acknowledgement_event.WaitInfinitely();
    dICHECK(acknowledgement_wait_result);

    m_acknowledgement_event.ResetEvent();

    m_command_code = command;
    m_command_param = param;

    m_command_event.SetEvent();

    if (wait_response)
    {
        bool new_acknowledgement_wait_result = m_acknowledgement_event.WaitInfinitely();
        dICHECK(new_acknowledgement_wait_result);
    }
}