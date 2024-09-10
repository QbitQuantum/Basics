void CDShowControl::RemoveGraphFromRot(DWORD pRegister)
{
	IRunningObjectTable *pRot;
	if(SUCCEEDED(GetRunningObjectTable(0, &pRot)))
	{
		pRot->Revoke(pRegister);
		pRot->Release();
	}
}