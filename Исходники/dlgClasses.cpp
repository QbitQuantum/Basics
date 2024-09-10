void ExecutionDialog::OnCancel(wxCommandEvent &ev)
{
	if (thread)
	{
		btnCancel->Disable();
		Abort();
		btnCancel->Enable();
		btnOK->Enable();
	}
	else
	{
		delete conn;
		if (IsModal())
			EndModal(-1);
		else
			Destroy();
	}
}