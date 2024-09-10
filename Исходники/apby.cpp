void mpk_import_add_named_pipe_instance(common_vars *common_vars) {
  HANDLE named_pipe_handle = CreateNamedPipeA("\\\\.\\pipe\\" m_mpk_import_named_pipe_name, PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, 0, nullptr);
  if (!named_pipe_handle) {
    m_last_error_str(err);
    m_die("cannot create mpk import named pipe instance, call to \"CreateNamedPipeA\" failed\nerr: %s", err);
  }
  HANDLE io_completion_port = CreateIoCompletionPort(named_pipe_handle, common_vars->io_completion_port, mpk_import_named_pipe_event, 0);
  if (!io_completion_port) {
    m_last_error_str(err_str);
    m_die("cannot connect mpk import named pipe to io completion port, call to \"CreateIoCompletionPort\" failed\nerr: %s", err_str);
  }
  mpk_import_named_pipe_instance *new_named_pipe_instance = (mpk_import_named_pipe_instance *)memory_pool_allocate(&common_vars->mpk_import_named_pipe_instance_memory_pool);
  *new_named_pipe_instance = {};
  new_named_pipe_instance->handle = named_pipe_handle;
  sllist_push(&common_vars->mpk_import_named_pipe_instance_list, new_named_pipe_instance);
  ConnectNamedPipe(named_pipe_handle, &new_named_pipe_instance->overlapped);
}