qint32 QUsbDevice::write(const QByteArray* buf, quint32 maxSize)
{
    UsbPrintFuncName();
    Q_CHECK_PTR(buf);
    if (mUsbHandle==INVALID_HANDLE_VALUE
            || !mConfig.writeEp
            || !mConnected)
    {
        return -1;
    }

    ulong cbSent = 0;
    if (mDebug) qDebug("Writing %d bytes to endpoint 0x%02x", maxSize,(uint)mConfig.writeEp);
    bool bResult = WinUsb_WritePipe(mUsbHandle, mConfig.writeEp, (uchar*)buf->data(), maxSize, &cbSent, NULL);

    if (mDebug) {
        QString datastr, s;
        for (qint64 i = 0; i < maxSize; i++) {
            datastr.append(s.sprintf("%02X:", (uchar)buf->at(i)));
        }
        datastr.remove(datastr.size()-1, 1); //remove last colon
        qDebug() << "Sent" << cbSent << "/" << maxSize << "bytes:" << datastr;
    }
    if (!bResult) {
        printUsbError("WinUsb_WritePipe");
        return -1;
    }
    return cbSent;
}