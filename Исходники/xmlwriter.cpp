void xmlwriter::Createtag(LPTSTR  sTag)
{
	fwprintf(fp,_T("\n"));
	//Indent properly
	for(int iTmp =0;iTmp<iLevel;iTmp++)
		fwprintf(fp,_T("\t"));
	fwprintf(fp,_T("<%s"),sTag);
	//Add Attributes
	while(0 < vectAttrData.size()/2)
	{
		LPTSTR sTmp = vectAttrData.back();
		fwprintf(fp,_T(" %s="), sTmp);
		vectAttrData.pop_back();
		sTmp = vectAttrData.back();
		fwprintf(fp,_T("\"%s\""), sTmp);
		vectAttrData.pop_back();
	}
	vectAttrData.clear();
	fwprintf(fp,_T(">"));
	sTagStack.push(sTag);
	iLevel++;

}