vrpn_Atmel::~vrpn_Atmel()
{
#ifdef VRPN_ATMEL_SERIAL_VRPN
  vrpn_close_commport(serial_fd);
#else
  closePort(serial_fd , &init_params);      
#endif
  
  
}