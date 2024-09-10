void EventProcessor::Update(uint32 p_time)
{
    // update time
    m_time += p_time;

    // main event loop
    std::multimap<uint64, BasicEvent*>::iterator i;
    while (((i = m_events.begin()) != m_events.end()) && i->first <= m_time)
    {
        // get and remove event from queue
        BasicEvent* event = i->second;
        m_events.erase(i);

        if (event->IsRunning())
        {
            if (event->Execute(m_time, p_time))
            {
                // completely destroy event if it is not re-added
                delete event;
            }
            continue;
        }

        if (event->IsAbortScheduled())
        {
            event->Abort(m_time);
            // Mark the event as aborted
            event->SetAborted();
        }

        if (event->IsDeletable())
        {
            delete event;
            continue;
        }

        // Reschedule non deletable events to be checked at
        // the next update tick
        AddEvent(event, CalculateTime(1), false);
    }
}