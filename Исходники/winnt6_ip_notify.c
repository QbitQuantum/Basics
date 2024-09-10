void
ssh_cancel_ip_notifications(SshInterceptor generic_interceptor)
{
  SshNt6Interceptor interceptor = (SshNt6Interceptor)generic_interceptor;

  if (interceptor->route_change_handle)
    {
      CancelMibChangeNotify2(interceptor->route_change_handle);
      interceptor->route_change_handle = NULL;
    }

  if (interceptor->address_change_handle)
    {
      CancelMibChangeNotify2(interceptor->address_change_handle);
      interceptor->address_change_handle = NULL;
    }
}