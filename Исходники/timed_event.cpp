    MyApplication(int argc, char **argv)
        : Application(argc, argv, "timed_event", false)
    {
        // Touch
        Touch();
        m_controllerInThread.Touch();

        // Run thread
        m_thread.Run();
        m_controllerInThread.SwitchToThread(&m_thread);

        // Emit thread timed events
        m_controllerInThread.DPL::ControllerEventHandler<SecondEvent>::PostTimedEvent(SecondEvent(), 3);
        m_controllerInThread.DPL::ControllerEventHandler<FirstEvent>::PostTimedEvent(FirstEvent(), 2);

        // Emit framework timed quit event
        DPL::ControllerEventHandler<QuitEvent>::PostTimedEvent(QuitEvent(), 5);
    }