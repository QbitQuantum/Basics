logicalaccess::PCSCConnection::~PCSCConnection()
{
    if (handle_)
    {
        SCardDisconnect(handle_, SCARD_LEAVE_CARD);
    }
}