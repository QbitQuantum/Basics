void FirewireSignalMonitor::RunTableMonitor(void)
{
    stb_needs_to_wait_for_pat = true;
    stb_wait_for_pat_timer.start();
    dtvMonitorRunning = true;

    LOG(VB_CHANNEL, LOG_INFO, LOC + "RunTableMonitor(): -- begin");

    FirewireChannel *lchan = dynamic_cast<FirewireChannel*>(channel);
    if (!lchan)
    {
        LOG(VB_CHANNEL, LOG_INFO, LOC + "RunTableMonitor(): -- err");
        while (dtvMonitorRunning)
            usleep(10000);
        LOG(VB_CHANNEL, LOG_INFO, LOC + "RunTableMonitor(): -- err end");
        return;
    }

    FirewireDevice *dev = lchan->GetFirewireDevice();

    dev->OpenPort();
    dev->AddListener(this);

    while (dtvMonitorRunning && GetStreamData())
        usleep(10000);

    LOG(VB_CHANNEL, LOG_INFO, LOC + "RunTableMonitor(): -- shutdown ");

    dev->RemoveListener(this);
    dev->ClosePort();

    while (dtvMonitorRunning)
        usleep(10000);

    LOG(VB_CHANNEL, LOG_INFO, LOC + "RunTableMonitor(): -- end");
}