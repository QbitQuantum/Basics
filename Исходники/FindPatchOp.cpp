void FindPatchOp::RunHook()
{
	mPatchList.clear();

	GetDirOpPtr anOp = new GetDirOp(mDirServers);

	anOp->SetPath(GetVersionDir());
	DWORD aGetFlags = DIR_GF_DECOMPSERVICES | DIR_GF_SERVADDNAME | DIR_GF_ADDDISPLAYNAME | DIR_GF_SERVADDNETADDR 
		| DIR_GF_ADDDATAOBJECTS | DIR_GF_ADDDOTYPE | DIR_GF_ADDDODATA;

	if(mValidVersionSet.empty())
		aGetFlags |= DIR_GF_DECOMPROOT;

	anOp->SetFlags(aGetFlags);

	if(IsAsync())
	{
		Track(anOp);
		anOp->RunAsync(OP_TIMEOUT_INFINITE);
		return;
	}

	anOp->RunBlock(TimeLeft());
	DoFinish(anOp);
}