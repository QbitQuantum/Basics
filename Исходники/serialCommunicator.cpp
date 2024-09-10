int serialCommunicator::SerialBreak()
{

#if defined WIN32

    // Asio library doesn't support serial breaks on windows, so use win api
    boost::asio::deadline_timer timer(IO_service);

    // Set serial break
    SetCommBreak(newSerial->native_handle());

    // Wait for defined period
    timer.expires_from_now(boost::posix_time::milliseconds(serialBreakms));
    timer.wait();	// Blocks till the timer expires

    // Clear serial break
    ClearCommBreak(newSerial->native_handle());

#else
    // Otherwise send using the asio interface -NOTE this hasn't been tested yet.
    newSerial->send_break();
#endif

    return 1;
}