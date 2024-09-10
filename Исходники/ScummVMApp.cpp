void CScummVMUi::HandleCommandL(TInt aCommand) {
	switch(aCommand) {
	case EEikCmdExit:
		{
			RThread thread;
			if(thread.Open(iThreadId) == KErrNone) {
				thread.Terminate(0);
				thread.Close();
			}
			Exit();
		}
		break;
	}
}