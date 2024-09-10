static asynStatus
setOption(void *drvPvt, asynUser *pasynUser, const char *key, const char *val)
{
    ttyController_t *tty = (ttyController_t *)drvPvt;
    DWORD commConfigSize = sizeof(tty->commConfig);
    BOOL ret;
    DWORD error;

    assert(tty);
    asynPrint(pasynUser, ASYN_TRACE_FLOW,
                    "%s setOption key %s val %s\n", tty->portName, key, val);
    if (tty->commHandle == INVALID_HANDLE_VALUE) {
        epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                "%s disconnected:", tty->serialDeviceName);
        return asynError;
    }

    ret = GetCommConfig(tty->commHandle, &tty->commConfig, &commConfigSize);
    if (ret == 0) {
        error = GetLastError();
        epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                            "%s error calling GetCommConfig %d", tty->serialDeviceName, error);
        return asynError;
    }

    if (epicsStrCaseCmp(key, "baud") == 0) {
        int baud;
        if(sscanf(val, "%d", &baud) != 1) {
            epicsSnprintf(pasynUser->errorMessage, pasynUser->errorMessageSize,
                                                                "Bad number");
            return asynError;
        }
        tty->commConfig.dcb.BaudRate = baud;
    }
    else if (epicsStrCaseCmp(key, "bits") == 0) {
        int bits;
        if(sscanf(val, "%d", &bits) != 1) {
            epicsSnprintf(pasynUser->errorMessage, pasynUser->errorMessageSize,
                                                                "Bad number");
            return asynError;
        }
        tty->commConfig.dcb.ByteSize = bits;
    }
    else if (epicsStrCaseCmp(key, "parity") == 0) {
        if (epicsStrCaseCmp(val, "none") == 0) {
            tty->commConfig.dcb.Parity = 0;
        }
        else if (epicsStrCaseCmp(val, "odd") == 0) {
            tty->commConfig.dcb.Parity = 1;
        }
        else if (epicsStrCaseCmp(val, "even") == 0) {
            tty->commConfig.dcb.Parity = 2;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                            "Invalid parity.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "stop") == 0) {
        if (epicsStrCaseCmp(val, "1") == 0) {
            tty->commConfig.dcb.StopBits = ONESTOPBIT;
        }
        else if (epicsStrCaseCmp(val, "2") == 0) {
            tty->commConfig.dcb.StopBits = TWOSTOPBITS;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                "Invalid number of stop bits.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "clocal") == 0) {
        if (epicsStrCaseCmp(val, "Y") == 0) {
            tty->commConfig.dcb.fOutxDsrFlow = FALSE;
            tty->commConfig.dcb.fDsrSensitivity = FALSE;
            tty->commConfig.dcb.fDtrControl = DTR_CONTROL_ENABLE;
        }
        else if (epicsStrCaseCmp(val, "N") == 0) {
            tty->commConfig.dcb.fOutxDsrFlow = TRUE;
            tty->commConfig.dcb.fDsrSensitivity = TRUE;
            tty->commConfig.dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                    "Invalid clocal value.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "crtscts") == 0) {
        if (epicsStrCaseCmp(val, "Y") == 0) {
            tty->commConfig.dcb.fOutxCtsFlow = TRUE;
            tty->commConfig.dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
        }
        else if (epicsStrCaseCmp(val, "N") == 0) {
            tty->commConfig.dcb.fOutxCtsFlow = FALSE;
            tty->commConfig.dcb.fRtsControl = RTS_CONTROL_ENABLE;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                      "Invalid crtscts value.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "ixon") == 0) {
        if (epicsStrCaseCmp(val, "Y") == 0) {
            tty->commConfig.dcb.fOutX = TRUE  ;
        }
        else if (epicsStrCaseCmp(val, "N") == 0) {
            tty->commConfig.dcb.fOutX = FALSE;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                    "Invalid ixon value.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "ixany") == 0) {
        epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                    "Option ixany not supported on Windows");
        return asynError;       
    }
    else if (epicsStrCaseCmp(key, "ixoff") == 0) {
        if (epicsStrCaseCmp(val, "Y") == 0) {
            tty->commConfig.dcb.fInX = TRUE;
        }
        else if (epicsStrCaseCmp(val, "N") == 0) {
            tty->commConfig.dcb.fInX = FALSE;
        }
        else {
            epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                    "Invalid ixoff value.");
            return asynError;
        }
    }
    else if (epicsStrCaseCmp(key, "") != 0) {
        epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                                                "Unsupported key \"%s\"", key);
        return asynError;
    }
    ret = SetCommConfig(tty->commHandle, &tty->commConfig, commConfigSize);
    if (ret == 0) {
        error = GetLastError();
        epicsSnprintf(pasynUser->errorMessage,pasynUser->errorMessageSize,
                            "%s error calling SetCommConfig %d", tty->serialDeviceName, error);
        return asynError;
    }
    return asynSuccess;
}