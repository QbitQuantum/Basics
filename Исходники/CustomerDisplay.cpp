STDMETHODIMP CCustomerDisplay::DisplayOn(ULONG ulCom, ULONG ulBaud, ULONG* pulErrorCode)
{
    // если порт дисплея открыт, выходим
    if (hComm != INVALID_HANDLE_VALUE)
    {
        *pulErrorCode = E_SUCCESS;
        return S_OK;
    }

    // преобразуем номер порта в имя файла
    CHAR c_CommFile[] = "COM1", c_CommNumber[2] = {0};
    _ultoa(ulCom, c_CommNumber, 10);
    c_CommFile[3] = c_CommNumber[0];
    // открываем порт
    hComm = CreateFile(c_CommFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        *pulErrorCode = E_PORT_IS_BUSY;
        return S_OK;
    }
    // задаем конфигурацию порта
    DCB dcb;
    GetCommState(hComm, &dcb);
    dcb.BaudRate = ulBaud;
    dcb.Parity = NOPARITY;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(hComm, &dcb);

    *pulErrorCode = E_SUCCESS;
    return S_OK;
}