void DialogObjProp::OP_ZSCL()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_ZSCL);
	char s_zscl[512];
	pXPos->GetWindowTextA(s_zscl, 512);
	float xScl = objtransform->GetScale().x;
	float yScl = objtransform->GetScale().y;
	float zScl = atof(s_zscl);

	objtransform->SetScale(xScl, yScl, zScl);
}