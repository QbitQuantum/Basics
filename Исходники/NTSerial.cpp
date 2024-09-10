CNTSerial::~CNTSerial ()
{
    // If the device is already closed,
    // then we don't need to do anything.
    if (m_hFile)
    {
        // Display a warning
        _RPTF0(_CRT_WARN,"CNTSerial::~CNTSerial - Serial port not closed\n");

        // Close implicitly
        ClosePort();
    }
}