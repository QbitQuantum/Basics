void Updatable::loop()
{
    struct timeval last;
    struct timeval start;
    struct timeval profile; // last time a profile update happened
    Usec sleep_time;
    Usec offset;

    // This call determines the time it takes for a gettimeofday call
    // This makes the calls more accurate
    gettimeofday(&last, NULL);
    gettimeofday(&start, NULL);
    offset = timeval_diff(&start, &last);

    // Get time of day for profiling
    gettimeofday(&profile, NULL);
    m_profileCount = 0;

    // Zero last so we can check
    last.tv_usec = 0;
    
    while (1)
    {
        // Grab current time
        gettimeofday(&start, NULL);

        // Grab our running state
        bool in_background = false;
        int interval = 10;
        getState(in_background, interval);

        // Change thread state if needed
        {
            boost::mutex::scoped_lock lock(m_upStateMutex);
            if (m_settingChange & PRIORITY)
                setThreadPriority();

            if (m_settingChange & AFFINITY)
                setThreadAffinity();

            m_settingChange = 0;
        }
        
        if (in_background)
        {
            // On the first loop through, set the step to ideal
            double diff = (double)(interval *(double)1000);
            if (0 != last.tv_usec)
                diff = (double)(timeval_diff(&start, &last) + offset);

            // Record time for next run 
            last = start;
            
            // Call our update function
            update(diff / (double)1000000);
            m_profileCount += 1;

            Usec profile_time = timeval_diff(&last, &profile);
            // If 1 second has passed since the last profile, publish and reset
            if (profile_time > 1000000)
            {
                if (m_publisher) {
                    IntEventPtr event(new IntEvent());
                    event->data = m_profileCount;
                    m_publisher->publish(IUpdatable::PROFILE, event);
                }
                profile = last;
                m_profileCount = 0;
            }

            // Only sleep if we aren't running all out
            if (interval > 0)
            {
                // Determine next time to awake
                struct timeval next = start;
                timeval_add(&next, (Usec)interval * USEC_PER_MILLISEC);
            
                // Sleep for the rest for the remainder of our time
                sleep_time = -age(&next);

                // Handle overrun
                if (sleep_time < 0)
                    sleep_time = interval * USEC_PER_MILLISEC;

                // If the wait ends early keep waiting
                while(sleep_time > SLEEP_THRESHOLD)
                {
                    waitForUpdate((long)sleep_time);
                    sleep_time = -age(&next);
                }
            }
        }
        // Time to quit
        else
        {
            break;
        }
    }

    // Release an threads waiting on
    m_threadStopped.countDown();
}