void irtiny::CIRDriver::threadProc()
{
    Event overlappedEvent = Event::manualResetEvent();
    OVERLAPPED ov = { 0 };
    ov.hEvent = overlappedEvent.get();

    HANDLE const events[2] = { ov.hEvent, finishEvent_.get() };

    // Send a byte to force RTS
    ::WriteFile(serialPort_.get(), "x", 1, nullptr, &ov);

    ::Sleep(100);

    for (;;)
    {
        overlappedEvent.resetEvent();

        // We want to be notified of RX changes
        if (SetCommMask(serialPort_.get(), EV_RXCHAR) == 0)
        {
            //DEBUG("SetCommMask returned zero, error=%d\n",GetLastError());
        }
        // Start waiting for the event
        DWORD event;
        if (WaitCommEvent(serialPort_.get(), &event, &ov) == 0 && GetLastError() != 997)
        {
            //DEBUG("WaitCommEvent error: %d\n",GetLastError());
        }

        switch (WaitForMultipleObjects(2, events, FALSE, INFINITE))
        {
        default:
            continue;

        case WAIT_OBJECT_0:
            while (true)
            {
                uint8_t buf[2];
                DWORD bytesRead = 0;
                auto const readSuccessful = ReadFile(serialPort_.get(), buf, 2, &bytesRead, &ov);
                if (bytesRead == 2)
                {
                    uint16_t const val = MAKEWORD(buf[1], buf[0]) & 0x7FFF;
                    bool const level = (buf[0] & 0x80) != 0;
                    double const unit = 1.0 / 115200.0;
                    DWORD const deltv = static_cast<DWORD>(1.0e+6 * unit * double(val));
                    DWORD const data = level
                        ? (deltv | 0x1000000)
                        : deltv;
                    setData(data);
                }
                else
                {
                    ::ClearCommError(serialPort_.get(), nullptr, nullptr);
                    ::PurgeComm(serialPort_.get(), PURGE_RXABORT | PURGE_RXCLEAR);
                    break;
                }
            }
            break;

        case WAIT_OBJECT_0 + 1:
            return;
        }
    }
}