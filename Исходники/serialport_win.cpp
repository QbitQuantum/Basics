void EIO_Open(uv_work_t* req) {
  OpenBaton* data = static_cast<OpenBaton*>(req->data);

  char originalPath[1024];
  strncpy_s(originalPath, sizeof(originalPath), data->path, _TRUNCATE);
  // data->path is char[1024] but on Windows it has the form "COMx\0" or "COMxx\0"
  // We want to prepend "\\\\.\\" to it before we call CreateFile
  strncpy(data->path + 20, data->path, 10);
  strncpy(data->path, "\\\\.\\", 4);
  strncpy(data->path + 4, data->path + 20, 10);

  HANDLE file = CreateFile(
    data->path,
    GENERIC_READ | GENERIC_WRITE,
    0, // dwShareMode 0 Prevents other processes from opening if they request delete, read, or write access
    NULL,
    OPEN_EXISTING,
    FILE_FLAG_OVERLAPPED, // allows for reading and writing at the same time and sets the handle for asynchronous I/O
    NULL
  );
  if (file == INVALID_HANDLE_VALUE) {
    DWORD errorCode = GetLastError();
    char temp[100];
    _snprintf_s(temp, sizeof(temp), _TRUNCATE, "Opening %s", originalPath);
    ErrorCodeToString(temp, errorCode, data->errorString);
    return;
  }

  bufferSize = data->bufferSize;
  if (bufferSize > MAX_BUFFER_SIZE) {
    bufferSize = MAX_BUFFER_SIZE;
  }

  DCB dcb = { 0 };
  SecureZeroMemory(&dcb, sizeof(DCB));
  dcb.DCBlength = sizeof(DCB);

  if (!GetCommState(file, &dcb)) {
    ErrorCodeToString("GetCommState", GetLastError(), data->errorString);
    return;
  }

  if (data->hupcl) {
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
  } else {
    dcb.fDtrControl = DTR_CONTROL_DISABLE;  // disable DTR to avoid reset
  }

  dcb.Parity = NOPARITY;
  dcb.ByteSize = 8;
  dcb.StopBits = ONESTOPBIT;
  dcb.fInX = FALSE;
  dcb.fOutX = FALSE;
  dcb.fOutxDsrFlow = FALSE;
  dcb.fOutxCtsFlow = FALSE;
  dcb.fRtsControl = RTS_CONTROL_ENABLE;

  dcb.fBinary = true;
  dcb.BaudRate = data->baudRate;
  dcb.ByteSize = data->dataBits;

  switch (data->parity) {
  case SERIALPORT_PARITY_NONE:
    dcb.Parity = NOPARITY;
    break;
  case SERIALPORT_PARITY_MARK:
    dcb.Parity = MARKPARITY;
    break;
  case SERIALPORT_PARITY_EVEN:
    dcb.Parity = EVENPARITY;
    break;
  case SERIALPORT_PARITY_ODD:
    dcb.Parity = ODDPARITY;
    break;
  case SERIALPORT_PARITY_SPACE:
    dcb.Parity = SPACEPARITY;
    break;
  }

  switch (data->stopBits) {
  case SERIALPORT_STOPBITS_ONE:
    dcb.StopBits = ONESTOPBIT;
    break;
  case SERIALPORT_STOPBITS_ONE_FIVE:
    dcb.StopBits = ONE5STOPBITS;
    break;
  case SERIALPORT_STOPBITS_TWO:
    dcb.StopBits = TWOSTOPBITS;
    break;
  }

  if (!SetCommState(file, &dcb)) {
    ErrorCodeToString("SetCommState", GetLastError(), data->errorString);
    return;
  }

  // Set the com port read/write timeouts
  DWORD serialBitsPerByte = 8/*std data bits*/ + 1/*start bit*/;
  serialBitsPerByte += (data->parity == SERIALPORT_PARITY_NONE) ? 0 : 1;
  serialBitsPerByte += (data->stopBits == SERIALPORT_STOPBITS_ONE) ? 1 : 2;
  DWORD msPerByte = (data->baudRate > 0) ?
                    ((1000 * serialBitsPerByte + data->baudRate - 1) / data->baudRate) :
                    1;
  if (msPerByte < 1) {
    msPerByte = 1;
  }
  COMMTIMEOUTS commTimeouts = {0};
  commTimeouts.ReadIntervalTimeout = msPerByte;  // Minimize chance of concatenating of separate serial port packets on read
  commTimeouts.ReadTotalTimeoutMultiplier = 0;  // Do not allow big read timeout when big read buffer used
  commTimeouts.ReadTotalTimeoutConstant = 1000;  // Total read timeout (period of read loop)
  commTimeouts.WriteTotalTimeoutConstant = 1000;  // Const part of write timeout
  commTimeouts.WriteTotalTimeoutMultiplier = msPerByte;  // Variable part of write timeout (per byte)
  if (!SetCommTimeouts(file, &commTimeouts)) {
    ErrorCodeToString("SetCommTimeouts", GetLastError(), data->errorString);
    return;
  }

  // Remove garbage data in RX/TX queues
  PurgeComm(file, PURGE_RXCLEAR);
  PurgeComm(file, PURGE_TXCLEAR);

  data->result = (int)file;
}