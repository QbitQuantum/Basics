void dxThreadPoolThreadInfo::ReportInitStatus(bool init_result)
{
    m_command_param = (void *)(size_t)(init_result ? EOK : ((errno != EOK) ? errno : EFAULT));

    m_acknowledgement_event.SetEvent();
}