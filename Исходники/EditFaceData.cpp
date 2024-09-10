void EditFaceDataMod::UpdateDialog () {	
	TSTR buf;
	int numFaces=0, whichFace=0;
	float value = 1.0f;
	bool valueDetermined = true;

	if (!hParams) return;

	ModContextList mcList;
	INodeTab nodes;
	ip->GetModContexts(mcList,nodes);

	if (selLevel) {
		for (int i = 0; i < mcList.Count(); i++) {
			EditFaceDataModData *meshData = (EditFaceDataModData*)mcList[i]->localData;
			if (!meshData) continue;
			int numSelectedHere;
			meshData->DescribeSelection (numSelectedHere, whichFace, value, valueDetermined);
			numFaces += numSelectedHere;
		}
	}

	ISpinnerControl *spin = GetISpinner (GetDlgItem (hParams, IDC_VALUE_SPIN));
	ICustButton *but = GetICustButton (GetDlgItem (hParams, IDC_RESET_SELECTION));

	switch (selLevel) {
	case SEL_FACE:
		if (numFaces==1) {
			buf.printf (GetString(IDS_FACE_SELECTED), whichFace+1);
		} else {
			if (numFaces) buf.printf (GetString (IDS_FACES_SELECTED), numFaces);
			else buf = GetString (IDS_NO_FACE_SELECTED);
		}
		but->Enable (numFaces);
		spin->Enable (numFaces);
		if (numFaces && valueDetermined) {
			spin->SetIndeterminate (false);
			spin->SetValue (value, FALSE);
		} else {
			spin->SetIndeterminate (true);
		}
		break;

	case SEL_OBJECT:
		buf = GetString (IDS_OBJECT_SELECTED);
		spin->Disable();
		but->Disable ();
		break;
	}

	SetDlgItemText(hParams,IDC_FACE_SELECTED,buf);
	ReleaseISpinner (spin);
	ReleaseICustButton (but);
}