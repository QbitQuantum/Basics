static bool is_himddevice(QString devID, QString & name)
{
    DEVINST devinst;
    DEVINST devinstparent;
    unsigned long buflen;
    QString recname, devicepath;

    CM_Locate_DevNodeA(&devinst, devID.toLatin1().data(), NULL);
    CM_Get_Parent(&devinstparent, devinst, NULL);

    if(devID.contains("RemovableMedia", Qt::CaseInsensitive))    // on Windows XP: get next parent device instance
        CM_Get_Parent(&devinstparent, devinstparent, NULL);

    CM_Get_Device_ID_Size(&buflen, devinstparent, 0);
    wchar_t *buffer = new wchar_t[buflen];
    CM_Get_Device_ID(devinstparent, buffer, buflen, 0);
    devicepath = QString::fromWCharArray(buffer);
    delete[] buffer;

    if(identified( devicepath, recname))
    {
        name = recname;
        return true;
    }
    return false;
}