void call_ssh_timer(void * handle)
{
  if (((Ssh)handle)->version == 2)
  {
    ssh2_timer(handle, GETTICKCOUNT());
  }
}