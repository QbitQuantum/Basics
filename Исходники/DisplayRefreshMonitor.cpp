void DisplayRefreshMonitor::displayDidRefresh()
{
    double monotonicAnimationStartTime;
    {
        MutexLocker lock(m_mutex);
        if (!m_scheduled)
            ++m_unscheduledFireCount;
        else
            m_unscheduledFireCount = 0;

        m_scheduled = false;
        monotonicAnimationStartTime = m_monotonicAnimationStartTime;
    }

    // The call back can cause all our clients to be unregistered, so we need to protect
    // against deletion until the end of the method.
    Ref<DisplayRefreshMonitor> protect(*this);

    // Copy the hash table and remove clients from it one by one so we don't notify
    // any client twice, but can respond to removal of clients during the delivery process.
    HashSet<DisplayRefreshMonitorClient*> clientsToBeNotified = m_clients;
    m_clientsToBeNotified = &clientsToBeNotified;
    while (!clientsToBeNotified.isEmpty()) {
        // Take a random client out of the set. Ordering doesn't matter.
        // FIXME: Would read more cleanly if HashSet had a take function.
        auto it = clientsToBeNotified.begin();
        DisplayRefreshMonitorClient* client = *it;
        clientsToBeNotified.remove(it);

        client->fireDisplayRefreshIfNeeded(monotonicAnimationStartTime);

        // This checks if this function was reentered. In that case, stop iterating
        // since it's not safe to use the set any more.
        if (m_clientsToBeNotified != &clientsToBeNotified)
            break;
    }
    if (m_clientsToBeNotified == &clientsToBeNotified)
        m_clientsToBeNotified = nullptr;

    {
        MutexLocker lock(m_mutex);
        m_previousFrameDone = true;
    }
    
    DisplayRefreshMonitorManager::sharedManager()->displayDidRefresh(this);
}