Components::Deployment::ComponentServer_ptr
ServerActivatorImpl::create_component_server (const ::Components::ConfigValues& config)
throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException)
{
	QedoLock lock (cs_activation_mutex_);
	std::cout << "ServerActivatorImpl: create_component_server() called" << std::endl;

	CORBA::String_var my_string_ref;


	try
	{
		my_string_ref = orb_->object_to_string (this->_this());
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ServerActivatorImpl: Cannot stringify my object reference" << std::endl;
		throw Components::CreateFailure();
	}

#ifdef _WIN32
	int component_server_pid;
	char *args[17];
	const char* prog;
	int args_nr=0;

	if (enable_terminal_)
	{
		prog = "c:/winnt/system32/cmd.exe";
		args[args_nr++] = "cmd";
		args[args_nr++] = "/c";
		args[args_nr++] = "start";
		args[args_nr++] = "qcs.exe";
	}
	else
	{
		prog = "qcs.exe";
		args[args_nr++] = "qcs.exe";
	}

	if (debug_mode_)
	{
		args[args_nr++] = "--debug";
	}

	if (verbose_mode_)
	{
		args[args_nr++] = "--verbose";
	}

	args[args_nr++] = "--csa_ref";
	args[args_nr++] = my_string_ref.inout();

	args[args_nr] = 0;

	component_server_pid = _spawnv(_P_NOWAIT, prog, args);

	if (component_server_pid < 0)
	{
		std::cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << std::endl;
		std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
		throw Components::CreateFailure();
	}

#else

	pid_t component_server_pid;

	switch (component_server_pid = fork())
	{
		case 0 : /* child process */
		{
			char *args[17];
			const char* prog;
			int args_nr=0;


			if (enable_terminal_)
			{
				args[args_nr++] = "xterm";
				args[args_nr++] = "-e";
				args[args_nr++] = "qcs.sh";
				prog = "xterm";
			}
			else
			{
				args[args_nr++] = "qcs";
				prog = "qcs";
			}

			if (debug_mode_)
			{
				args[args_nr++] = "--debug";
			}

			if (verbose_mode_)
			{
				args[args_nr++] = "--verbose";
			}

			args[args_nr++] = "--csa_ref";
			args[args_nr++] = my_string_ref.inout();

			args[args_nr] = 0;

			long err = execvp (prog,args);
			if (err == -1) 
			{
				std::cerr << "ServerActivatorImpl: execvp() for component server failed" << std::endl;
				std::cerr << "ServerActivatorImpl: Error  was: " << strerror (errno) << std::endl;
				throw Components::CreateFailure();
			}

		}
			break;
		default : /* parent process */
			break;
		case -1 : /* error in fork */
			{
				std::cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << std::endl;
				std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
				throw Components::CreateFailure();
			}
			break;
	}

#endif

	cs_activation_cond_.wait (cs_activation_mutex_);

//#endif

	if (CORBA::is_nil (last_created_component_server_))
	{
		// cerr << "ServerActivatorImpl: Component Server has not been created" << endl;
		throw Components::CreateFailure();
	}

	ComponentServerEntry e;
	e.server = Components::Deployment::ComponentServer::_duplicate(last_created_component_server_);
	e.pid = component_server_pid;

	Qedo::QedoLock l(component_servers_mutex_);

	component_servers_.push_back(e);

	return Components::Deployment::ComponentServer::_duplicate(last_created_component_server_);
}