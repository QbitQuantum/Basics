bool Channel::CreatePipe(const IPC::ChannelHandle &channel_handle) {
  assert(INVALID_HANDLE_VALUE == pipe_);
  std::wstring pipe_name;
  // If we already have a valid pipe for channel just copy it.
  if (channel_handle.pipe.handle) {
    assert(channel_handle.name.empty());
    pipe_name = L"Not Available";  // Just used for LOG
    // Check that the given pipe confirms to the specified mode.  We can
    // only check for PIPE_TYPE_MESSAGE & PIPE_SERVER_END flags since the
    // other flags (PIPE_TYPE_BYTE, and PIPE_CLIENT_END) are defined as 0.
    DWORD flags = 0;
    GetNamedPipeInfo(channel_handle.pipe.handle, &flags, NULL, NULL, NULL);
    assert(!(flags & PIPE_TYPE_MESSAGE));
    if (!DuplicateHandle(GetCurrentProcess(),
                         channel_handle.pipe.handle,
                         GetCurrentProcess(),
                         &pipe_,
                         0,
                         FALSE,
                         DUPLICATE_SAME_ACCESS)) {
      //LOG(WARNING) << "DuplicateHandle failed. Error :" << GetLastError();
      return false;
    }
  } else {
	assert(!channel_handle.pipe.handle);
	pipe_name = PipeName(channel_handle.name, &client_secret_);

	//ÏÈ³¢ÊÔ´´½¨
    const DWORD open_mode = PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED |
                            FILE_FLAG_FIRST_PIPE_INSTANCE;
    validate_client_ = !!client_secret_;
    pipe_ = CreateNamedPipeW(pipe_name.c_str(),
                             open_mode,
                             PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
                             1,
                             kReadBufferSize,
                             kReadBufferSize,
                             5000,
                             NULL);
	if (pipe_ == INVALID_HANDLE_VALUE)
	{
		pipe_ = CreateFileW(pipe_name.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			SECURITY_SQOS_PRESENT | SECURITY_IDENTIFICATION |
			FILE_FLAG_OVERLAPPED,
			NULL);

		waiting_connect_ = false;
	}
  } 

  if (pipe_ == INVALID_HANDLE_VALUE) {
    // If this process is being closed, the pipe may be gone already.
    //LOG(WARNING) << "Unable to create pipe \"" << pipe_name <<
    //                "\" in " << (mode & MODE_SERVER_FLAG ? "server" : "client")
    //                << " mode. Error :" << GetLastError();
    return false;
  }

  // Create the Hello message to be sent when Connect is called
  Message* m = new Message(MSG_ROUTING_NONE,
                                    HELLO_MESSAGE_TYPE,
                                    IPC::Message::PRIORITY_NORMAL);
  m->AddRef();
  // Don't send the secret to the untrusted process, and don't send a secret
  // if the value is zero (for IPC backwards compatability).
  int32 secret = validate_client_ ? 0 : client_secret_;
  if (!m->WriteInt(GetCurrentProcessId()) ||
      (secret && !m->WriteUInt32(secret))) {
    CloseHandle(pipe_);
    pipe_ = INVALID_HANDLE_VALUE;
	m->Release();
    return false;
  }

  output_queue_.push(m);
  return true;
}