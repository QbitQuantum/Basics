bool
AltairProDevice::PropertySetGet(Port *port, char *Buffer, size_t size)
{
  assert(port != NULL);
  assert(Buffer != NULL);

  // eg $PDVSC,S,FOO,BAR*<cr>\r\n
  PortWriteNMEA(port, Buffer);

  Buffer[6] = _T('A');
  char *comma = strchr(&Buffer[8], ',');

  if (comma != NULL){
    comma[1] = '\0';

    // expect eg $PDVSC,A,FOO,
    if (port->ExpectString(Buffer)){

      // read value eg bar
      while(--size){
        int ch = port->GetChar();
        if (ch == -1)
          break;

        if (ch == '*'){
          Buffer = '\0';
          return true;
        }

        *Buffer++ = (char) ch;

      }

    }
  }

  *Buffer = '\0';
  return false;
}