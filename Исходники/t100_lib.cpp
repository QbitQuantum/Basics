/*---------------------------------------------------------------------------*/
int t100::searchDevices()
{ 
  // Enumerate and print the HID devices on the system
  struct hid_device_info *devs, *cur_dev;

  t100_totalDevices = 0;
  
  devs = hid_enumerate(0x0, 0x0);
  cur_dev = devs; 
  while (cur_dev) 
  { 
    if((cur_dev->vendor_id == VID) && (cur_dev->product_id == PID))
    {     
      #if WIN
      t100_deviceSerials[t100_totalDevices] = _wcstoui64(cur_dev->serial_number,NULL,0);
      #else
      t100_deviceSerials[t100_totalDevices] = wcstoul(cur_dev->serial_number,NULL,0);
      #endif
      t100_totalDevices++;
    }   
    cur_dev = cur_dev->next;
  }
  hid_free_enumeration(devs);

  return t100_totalDevices;
}