void TestKill()
	{
	RTestProcess process;
	RTestProcess process2;
	TRequestStatus logonStatus;
	TRequestStatus logonStatus2;

	process2.Create(0,ETestProcessNull);
	process2.Logon(logonStatus2);

	// Test RProcess::Kill()

	test.Start(_L("Test killing an un-resumed process created by us"));
	process.Create(0,ETestProcessNull);
	process.Logon(logonStatus);
	process.Kill(999);
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitKill);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try killing un-resumed process not created by self"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessKill,process2.Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	test(logonStatus2==KRequestPending); // the process should still be alive
	CLOSE_AND_WAIT(process);

	test.Next(_L("Test a process killing itself"));
	process.Create(0,ETestProcessKillSelf);
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitKill);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try killing running process"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessKill,RProcess().Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	CLOSE_AND_WAIT(process);

	// Test RProcess::Teminate()

	test.Next(_L("Test terminating an un-resumed process created by us"));
	process.Create(0,ETestProcessNull);
	process.Logon(logonStatus);
	process.Terminate(999);
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitTerminate);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try terminating un-resumed process not created by self"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessTerminate,process2.Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	test(logonStatus2==KRequestPending); // the process should still be alive
	CLOSE_AND_WAIT(process);

	test.Next(_L("Test a process terminating itself"));
	process.Create(0,ETestProcessTerminateSelf);
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitTerminate);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try terminating running process"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessTerminate,RProcess().Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	CLOSE_AND_WAIT(process);

	// Test RProcess::Panic()

	test.Next(_L("Test panicking an un-resumed process created by us"));
	process.Create(0,ETestProcessNull);
	process.Logon(logonStatus);
	process.Panic(KTestPanicCategory,999);
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try panicking un-resumed process not created by self"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessPanic,process2.Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	test(logonStatus2==KRequestPending); // the process should still be alive
	CLOSE_AND_WAIT(process);

	test.Next(_L("Test a process panicking itself"));
	process.Create(0,ETestProcessPanicSelf);
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic);
	test(logonStatus==999);
	CLOSE_AND_WAIT(process);

	test.Next(_L("Try panicking running process"));
	process.Create(~(1u<<ECapabilityPowerMgmt),ETestProcessPanic,RProcess().Id());
	process.Logon(logonStatus);
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitPanic); // Process should have got a Platform Security panic
	test(logonStatus==EPlatformSecurityTrap);
	CLOSE_AND_WAIT(process);

	// 

	test(logonStatus2==KRequestPending); // the process should still be alive
	process2.Resume();
	User::WaitForRequest(logonStatus2);
	test(logonStatus2==KErrNone);
	CLOSE_AND_WAIT(process2);

	// Checks with ECapabilityPowerMgmt

	test.Next(_L("Test kill running process ECapabilityPowerMgmt"));
	process2.Create(0,ETestProcessNull);
	process2.Logon(logonStatus2);
	process.Create((1<<ECapabilityPowerMgmt),ETestProcessKill,process2.Id());
	process.Logon(logonStatus);
	SyncMutex.Wait();
	process2.Resume();
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitKill);
	test(logonStatus==0);
	CLOSE_AND_WAIT(process);
	User::WaitForRequest(logonStatus2);
	test(process2.ExitType()==EExitKill);
	test(logonStatus2==999);
	process2.Close();
	SyncMutex.Signal();

	test.Next(_L("Test terminating running process ECapabilityPowerMgmt"));
	process2.Create(0,ETestProcessNull);
	process2.Logon(logonStatus2);
	process.Create((1<<ECapabilityPowerMgmt),ETestProcessTerminate,process2.Id());
	process.Logon(logonStatus);
	SyncMutex.Wait();
	process2.Resume();
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitKill);
	test(logonStatus==0);
	CLOSE_AND_WAIT(process);
	User::WaitForRequest(logonStatus2);
	test(process2.ExitType()==EExitTerminate);
	test(logonStatus2==999);
	CLOSE_AND_WAIT(process2);
	SyncMutex.Signal();

	test.Next(_L("Test panicking running process ECapabilityPowerMgmt"));
	process2.Create(0,ETestProcessNull);
	process2.Logon(logonStatus2);
	process.Create((1<<ECapabilityPowerMgmt),ETestProcessPanic,process2.Id());
	process.Logon(logonStatus);
	SyncMutex.Wait();
	process2.Resume();
	process.Resume();
	User::WaitForRequest(logonStatus);
	test(process.ExitType()==EExitKill);
	test(logonStatus==0);
	CLOSE_AND_WAIT(process);
	User::WaitForRequest(logonStatus2);
	test(process2.ExitType()==EExitPanic);
	test(logonStatus2==999);
	CLOSE_AND_WAIT(process2);
	SyncMutex.Signal();

	//

	test.End();
	}