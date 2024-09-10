/**
 * Tries to read from the serial device. Same as sio_read but returns
 * immediately if no data is available and never blocks.
 * 
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recvd = 0; //bytes received
  SerialBuf* pIf = (SerialBuf*) fd;
  pIf->setReadMode(false);
  while(len)
  {
   /* if(!pIf->readable())
    {
      wait_ms(4);
    }*/
    if(!pIf->readable())
    {
      return recvd;
    }
    *data = (u8_t) pIf->getc();
    data++;
    len--;
    recvd++;
  }
  return recvd;
}