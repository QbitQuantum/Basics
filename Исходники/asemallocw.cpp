void
ase_install_malloc_hook()
{
  _set_new_mode(1);
  _set_new_handler(mhook_handle_oom);
}