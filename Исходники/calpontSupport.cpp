void reportThread(string reporttype)
{
	string reportType = reporttype;
	
	string installDir(startup::StartUp::installDir());
	Oam oam;

	pthread_mutex_lock( &mutex1 );
	runningThreads++;
//cout << "++ " << runningThreads << endl;
	pthread_mutex_unlock( &mutex1 );

	string outputFile = localModule + "_" + reportType + "Report.txt";

	// run on child servers and get report
	if (!LOCAL)
	{
		ChildModuleList::iterator list1 = childmodulelist.begin();
		for (; list1 != childmodulelist.end() ; list1++)
		{
			threadInfo_t *st = new threadInfo_t;
			*st = boost::make_tuple(list1, reportType);

			pthread_t childreportthread;
			int status = pthread_create (&childreportthread, NULL, (void*(*)(void*)) &childReportThread, st);
	
			if ( status != 0 ) {
				cout <<  "ERROR: childreportthread: pthread_create failed, return status = " + oam.itoa(status) << endl;
			}

			sleep(1);
		}
	}

	// run report on local server
	cout << "Get " + reportType + " report data for " + localModule  << endl;

	if (reportType == "log")
	{
			string cmd = installDir + "/bin/logReport.sh " + localModule + " " + installDir;
			system(cmd.c_str());

			cmd = "mv -f /tmp/" + localModule + "_logReport.tar.gz .";
			system(cmd.c_str());

			cmd = "tar -zcf " + localModule + "_mysqllogReport.tar.gz " + installDir + "/mysql/db/*.err* 2>/dev/null";
			system(cmd.c_str());
	
			// run log config on local server
			cout << "Get log config data for " + localModule << endl;
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** Log Configuration  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getLogConfig ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getLogConfig >> " + outputFile;
			system(cmd.c_str());
	}
	else
	{
		//get local report
		title(outputFile);
	
		string cmd = "echo '=======================================================================' >> " + outputFile;
		system(cmd.c_str());
		cmd = "echo '=                    " + reportType + " report                                  =' >> " + outputFile;
		system(cmd.c_str());
		cmd = "echo '=======================================================================' >> " + outputFile;
		system(cmd.c_str());
	
		cmd = installDir + "/bin/" + reportType + "Report.sh " + localModule + " " + installDir;
		system(cmd.c_str());
		cmd = " mv -f /tmp/" + localModule + "_" + reportType + "Report.txt .";
		system(cmd.c_str());

		if (reportType == "config" )
		{
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Network Configuration ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getSystemNetworkConfig ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getSystemNetworkConfig >> " + outputFile;
			system(cmd.c_str());
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Module Configure  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getModuleTypeConfig ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getModuleTypeConfig >> " + outputFile;
			system(cmd.c_str());
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Storage Configuration  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getStorageConfig ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getStorageConfig >> " + outputFile;
			system(cmd.c_str());
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Storage Status  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getStorageStatus ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getStorageStatus >> " + outputFile;
			system(cmd.c_str());
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Status  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# mcsadmin getSystemInfo ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = installDir + "/bin/mcsadmin getSystemInfo >> " + outputFile;
			system(cmd.c_str());
	
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '******************** System Configuration File  ********************' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo '################# cat /etc/Calpont.xml ################# ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "echo ' ' >> " + outputFile;
			system(cmd.c_str());
			cmd = "cat " + installDir + "/etc/Calpont.xml >> " + outputFile;
			system(cmd.c_str());
		}
	
		if (reportType == "resource" )
		{
			if (LOCAL) {
				cmd = "echo '################# mcsadmin getModuleResourceUsage ################# ' >> " + outputFile;
				system(cmd.c_str());
				cmd = "echo ' ' >> " + outputFile;
				system(cmd.c_str());
				string cmd = installDir + "/bin/mcsadmin getModuleResourceUsage " + localModule + " >> " + outputFile;
				system(cmd.c_str());
			}
			else
			{
				cmd = "echo '################# mcsadmin getSystemResourceUsage ################# ' >> " + outputFile;
				system(cmd.c_str());
				cmd = "echo ' ' >> " + outputFile;
				system(cmd.c_str());
				string cmd = installDir + "/bin/mcsadmin getSystemResourceUsage >> " + outputFile;
				system(cmd.c_str());
			}
		}
	}

	// exit thread
	pthread_mutex_lock( &mutex1 );
	runningThreads--;
//cout << "-- " << runningThreads << endl;
	pthread_mutex_unlock( &mutex1 );

	pthread_exit(0);
}