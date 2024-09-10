TSTR CompositeMatPBAccessor::GetLocalName(ReferenceMaker* owner, ParamID id, int tabIndex)
{
	CompositeMat* p = (CompositeMat*)owner;
	TSTR out;
	switch (id)
		{
		case compmat_amount:
			{
			out.printf(_T("%s %d"),GetString(IDS_PW_AMOUNT),tabIndex+1);
			break;
			}
		case compmat_mtls:
			{
			TSTR name;
			Mtl *sm1 = NULL;
			Interval iv;
			if ((p) && (p->pblock2)) p->pblock2->GetValue(compmat_mtls,0,sm1,iv,tabIndex);
			name = sm1->GetFullName();

			if (tabIndex == 0)
				{
				out.printf(_T("%s: %s"),GetString(IDS_PW_BASE),name);
				}
			else
				{
				out.printf(_T("%s %d: %s"),GetString(IDS_RB_MATERIAL2),tabIndex,name);
				}
			break;
			}
		}
	return out;

}