bool cSerialStream::isRinging()
{
    DWORD mask;
    CHECK(GetCommMask(m_serialHandle.getHandle()->getHandle(),
          &mask));
    return (mask & EV_RING) == EV_RING;
}