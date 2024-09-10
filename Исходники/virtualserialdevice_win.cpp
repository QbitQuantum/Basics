void VirtualSerialDevice::commEventOccurred()
{
    DWORD event = d->commEventMask;
    if (event & EV_RXCHAR) {
        emit readyRead();
    }
    ResetEvent(d->commEventOverlapped.hEvent);
    WaitCommEvent(d->portHandle, &d->commEventMask, &d->commEventOverlapped);
}