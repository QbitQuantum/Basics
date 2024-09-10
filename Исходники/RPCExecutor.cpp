void RPCExecutor::Execute()
{
	// tempting to throw an exception here
	if (!m_callObserver)
	{
		setExecutionStatus(waInitialiseFailed);
		return;
	}
	if (!m_winamp)
	{
		m_callObserver->notifyException("winamp implementation is not set");
		setExecutionStatus(waInitialiseFailed);
		return;
	}

	std::string str;
    RPC_STATUS status;
    // "ncacn_np" for named pip
    // "ncacn_ip_tcp" for tcpip

    m_callObserver->notifyStatus("initialising...");

    m_callObserver->notifyMessage(m_winamp->WinampVersion().c_str());

	setExecutionStatus(waServerStarting);
    status = RpcServerUseProtseqEp((unsigned char *) m_protocolSequence.c_str(),
                                   20,
                                   (unsigned char *) m_endPoint.c_str(),
                                   NULL);

    if (status == RPC_S_OK){
      status = RpcServerRegisterIf(winamp_v1_0_s_ifspec, NULL, NULL);
      if (status == RPC_S_OK){
    	  m_callObserver->notifyMessage("listening...");
  		setExecutionStatus(waListening);
        status = RpcServerListen(1, 20, FALSE);
        if (status != RPC_S_OK){
      		setExecutionStatus(waInitialiseFailed);
        	m_callObserver->notifyException("error in listening");
        	m_callObserver->notifyException(RPCError(status));
          }
        }
    else{
  		setExecutionStatus(waInitialiseFailed);
    	m_callObserver->notifyException("failed to register interface");
    	m_callObserver->notifyException(RPCError(status));
    	m_callObserver->notifyException("initialise failed");
      }
    }
  else{
	  setExecutionStatus(waInitialiseFailed);
	  m_callObserver->notifyException("failed to create protocol sequence");
	  m_callObserver->notifyException(RPCError(status));
	  m_callObserver->notifyException("initialise failed");
  }
  setExecutionStatus(waServerStopped);

}