int usb_control_msg(usb_dev_handle *dev, int requesttype, 
                    int request, int value, int index, 
                    char *bytes, int size, int timeout)
{
   // Format parameters into a ctrl setup packet
   // 'timeout' is ignored; WinUSB has a 5 second default timeout on the ctrl
   // pipe, which is good enough for us.
   WINUSB_SETUP_PACKET sp;
   sp.RequestType = requesttype;
   sp.Request = request;
   sp.Value = value;
   sp.Index = index;
   sp.Length = size;

   ULONG actlen = 0;
   if (!WinUsb_ControlTransfer(dev->fd, sp, (unsigned char*)bytes, size, &actlen, NULL))
      return -(int)GetLastError();

   return actlen;
}