bool QextSerialPortPrivate::open_sys(QIODevice::OpenMode mode)
{
    Q_Q(QextSerialPort);
    DWORD confSize = sizeof(COMMCONFIG);
    commConfig.dwSize = confSize;
    DWORD dwFlagsAndAttributes = 0;
    if (queryMode == QextSerialPort::EventDriven)
        dwFlagsAndAttributes += FILE_FLAG_OVERLAPPED;

    /*open the port*/
    handle = CreateFileW((wchar_t *)fullPortNameWin(port).utf16(), GENERIC_READ|GENERIC_WRITE,
                           0, nullptr, OPEN_EXISTING, dwFlagsAndAttributes, nullptr);
    if (handle != INVALID_HANDLE_VALUE) {
        q->setOpenMode(mode);
        /*configure port settings*/
        GetCommConfig(handle, &commConfig, &confSize);
        GetCommState(handle, &(commConfig.dcb));

        /*set up parameters*/
        commConfig.dcb.fBinary = TRUE;
        commConfig.dcb.fInX = FALSE;
        commConfig.dcb.fOutX = FALSE;
        commConfig.dcb.fAbortOnError = FALSE;
        commConfig.dcb.fNull = FALSE;
        /* Dtr default to true. See Issue 122*/
        commConfig.dcb.fDtrControl = TRUE;
        /*flush all settings*/
        settingsDirtyFlags = DFE_ALL;
        updatePortSettings();

        //init event driven approach
        if (queryMode == QextSerialPort::EventDriven) {
            if (!SetCommMask(handle, EV_TXEMPTY | EV_RXCHAR | EV_DSR)) {
                QESP_WARNING()<<"failed to set Comm Mask. Error code:"<<GetLastError();
                return false;
            }
            winEventNotifier = new QWinEventNotifier(overlap.hEvent, q);
            qRegisterMetaType<HANDLE>("HANDLE");
            q->connect(winEventNotifier, SIGNAL(activated(HANDLE)), q, SLOT(_q_onWinEvent(HANDLE)), Qt::DirectConnection);
            WaitCommEvent(handle, &eventMask, &overlap);
        }
        return true;
    }
    return false;
}