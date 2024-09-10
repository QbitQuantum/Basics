int KSGProcess::run(int argc,char ** argv)
{
	KSG_SERVICE::instance()->name(ACE_TEXT("ykt_gateway"),
		ACE_TEXT("ykt_gateway"));
	parse_args(argc,argv);
	if(_opt_install && !_opt_remove)
	{
		KSGService * svr = KSG_SERVICE::instance();
		if(-1 == svr->insert(SERVICE_DEMAND_START))
		{
			ACE_OS::printf("install NT Service error[%d]!\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_remove && !_opt_install)
	{
		if(-1 == KSG_SERVICE::instance()->remove())
		{
			ACE_OS::printf("remove from Service Manager error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_start && _opt_kill)
		print_usage();
	if(_opt_start)
	{
		ACE_OS::printf("正在启动前置机...\n");
		g_top_level_exception = SetUnhandledExceptionFilter(KSG_UnhandledExceptionFilter);
		if(-1 == KSG_SERVICE::instance()->start_svc())
		{
			ACE_OS::printf("start service error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_kill)
	{
		ACE_OS::printf("正在停止前置机...\n");
		if(-1 == KSG_SERVICE::instance()->stop_svc())
		{
			ACE_OS::printf("stop service error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_debug)
	{
		// 直接启动
		SetConsoleCtrlHandler (&ConsoleHandler, 1);
		g_top_level_exception = SetUnhandledExceptionFilter(KSG_UnhandledExceptionFilter);
		int ret = KSG_SERVICE::instance()->svc();
		//system("pause");
		return ret;
	}
	else
	{
		/*std::ofstream *output_file = new std::ofstream("ntsvc.log", std::ios::out);
		if (output_file && output_file->rdstate() == std::ios::goodbit)
			ACE_LOG_MSG->msg_ostream(output_file, 1);
		
		ACE_LOG_MSG->open(argv[0],
			ACE_Log_Msg::STDERR | ACE_Log_Msg::OSTREAM,
			0);

		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%T (%t): Starting service.\n")));*/
		ACE_NT_SERVICE_RUN (ykt_gateway,KSG_SERVICE::instance (),
			ret);
		if(ret == 0)
		{
			ACE_OS::printf("Couldn't start service!\n");
		}
		else
		{
			ACE_OS::printf("Service exits [%d]!\n",ACE_OS::last_error());
		}
		return 0;
	}
	return 0;
}