tInt32 Serial::cRawSerialDevice::BytesAvailable()
{    
    int bytesAvailable = 0;
#ifndef     WIN32
    ioctl(m_FileDescriptorSerial, FIONREAD, &bytesAvailable);
#else
    DWORD status;
    COMSTAT comStat;
    ClearCommError((HWND)(m_hDevice),&status, &comStat);
    bytesAvailable = (tInt32)comStat.cbInQue;
#endif
    //std::cout << "Bytes available on FileDesc: " << FileDescriptorSerial << "\t Bytes: " << bytesAvailable << std::endl;
    return bytesAvailable;
}