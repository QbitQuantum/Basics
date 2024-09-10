void PatchDeformPW::BeginEditParams( IObjParam *ip, ULONG flags,Animatable *prev )
{
	this->ip = ip;
	PatchDeformPWDesc.BeginEditParams(ip, this, flags, prev);
	patchdeformpw_param_blk.SetUserDlgProc(new PatchDeformParamsMapDlgProc(this));

	TSTR name;
	name.printf(_T("%s"),GetString(IDS_PICK));
	SetWindowText(GetDlgItem(hWnd,IDC_STATUS),name);

}