int SetSerialState(int nPortNum, int args, WCHAR *argv[])
{
    int arg;
    int value;
    DCB dcb;
    COMMTIMEOUTS CommTimeouts;
    WCHAR buf[MAX_COMPARAM_LEN+1];

    if (SerialPortQuery(nPortNum, &dcb, &CommTimeouts, FALSE))
    {
        for (arg = 2; arg < args; arg++)
        {
            if (wcslen(argv[arg]) > MAX_COMPARAM_LEN)
            {
                wprintf(L"Invalid parameter (too long) - %s\n", argv[arg]);
                return 1;
            }
            wcscpy(buf, argv[arg]);
            _wcslwr(buf);
            if (wcsstr(buf, L"baud="))
            {
                wscanf(buf+5, L"%lu", &dcb.BaudRate);
            }
            else if (wcsstr(buf, L"parity="))
            {
                if (wcschr(buf, L'D'))
                    dcb.Parity = 1;
                else if (wcschr(buf, L'V'))
                    dcb.Parity = 2;
                else if (wcschr(buf, L'M'))
                    dcb.Parity = 3;
                else if (wcschr(buf, L'S'))
                    dcb.Parity = 4;
                else
                    dcb.Parity = 0;
            }
            else if (wcsstr(buf, L"data="))
            {
                wscanf(buf+5, L"%lu", &dcb.ByteSize);
            }
            else if (wcsstr(buf, L"stop="))
            {
                if (wcschr(buf, L'5'))
                    dcb.StopBits = 1;
                else if (wcschr(buf, L'2'))
                    dcb.StopBits = 2;
                else
                    dcb.StopBits = 0;
            }
            else if (wcsstr(buf, L"to=")) // to=on|off
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"xon=")) // xon=on|off
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fOutX = value;
                    dcb.fInX = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"odsr=")) // odsr=on|off
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fOutxDsrFlow = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"octs=")) // octs=on|off
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fOutxCtsFlow = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"dtr=")) // dtr=on|off|hs
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fDtrControl = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"rts=")) // rts=on|off|hs|tg
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fRtsControl = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else if (wcsstr(buf, L"idsr=")) // idsr=on|off
            {
                value = ExtractModeSerialParams(buf);
                if (value != -1)
                {
                    dcb.fDsrSensitivity = value;
                }
                else
                {
                    goto invalid_serial_parameter;
                }
            }
            else
            {
invalid_serial_parameter:;
                wprintf(L"Invalid parameter - %s\n", buf);
                return 1;
            }
        }
        SerialPortQuery(nPortNum, &dcb, &CommTimeouts, TRUE);
    }
    return 0;
}