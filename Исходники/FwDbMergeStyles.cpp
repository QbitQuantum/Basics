/*----------------------------------------------------------------------------------------------
	Change all the occurrences of the old styles names to the new names, and delete any
	obsolete names.
----------------------------------------------------------------------------------------------*/
bool FwDbMergeStyles::ProcessFormatting(ComVector<ITsTextProps> & vqttp,
	StrUni stuDelete)
{
	bool fAnyChanged = false;
	for (int ittp = 0; ittp < vqttp.Size(); ittp++)
	{
		SmartBstr sbstr;
		HRESULT hr;
		CheckHr(hr = vqttp[ittp]->GetStrPropValue(ktptNamedStyle, &sbstr));
		if (hr == S_OK && sbstr.Length() > 0)
		{
			ITsPropsBldrPtr qtpb = NULL;
			StrUni stuOld(sbstr.Chars());
			StrUni stuNew;
			if (Delete(stuOld))
			{
				CheckHr(vqttp[ittp]->GetBldr(&qtpb));
				if (stuDelete.Length() == 0)
				{
					// If the style name to delete is empty, we want to pass null
					// so that the named style string property is removed.
					CheckHr(qtpb->SetStrPropValue(ktptNamedStyle, NULL));
				}
				else
					CheckHr(qtpb->SetStrPropValue(ktptNamedStyle, stuDelete.Bstr()));

			}
			else if (Rename(stuOld, stuNew))
			{
				CheckHr(vqttp[ittp]->GetBldr(&qtpb));
				CheckHr(qtpb->SetStrPropValue(ktptNamedStyle, stuNew.Bstr()));
			}

			if (qtpb)
			{
				ITsTextPropsPtr qttpNew;
				CheckHr(qtpb->GetTextProps(&qttpNew));
				vqttp[ittp] = qttpNew;
				fAnyChanged = true;
			}
		}
	}

	return fAnyChanged;
}