long ndiSerialOpen(const char *device)
{
  short serial_out, serial_in; /* macintosh device handles */
  long serial_port; /* hold them both, packed into 32 bits */
  char namein[64], nameout[64];
  int i;

  sprintf(namein,"%sIn",device);
  sprintf(nameout,"%sOut",device);

  if (OpenDriver(namein, &serial_in) != noErr) {
    return -1;
  }
  if (OpenDriver(nameout,&serial_out) != noErr) {
    CloseDriver(serial_in);
    return -1;
  }

  /* combine the two shorts into one long */
  serial_port = ((serial_in << 0) | (serial_out << 16));
  
  /* save the serial port state so that it can be restored when
     the serial port is closed in ndiSerialClose() */
  for (i = 0; i < NDI_MAX_SAVE_STATE; i++) {
    if (ndi_open_handles[i] == serial_port || ndi_open_handles[i] == -1) {
      ndi_open_handles[i] = serial_port;
      break;
    }
  }

  return serial_port;
}