void GetCoordInventory()
{
	std::map<std::wstring, AcGePoint3d> m_3dPoints;
	u_int startIndex = 1;

	ads_real textHeightResult = 1;
	ads_real pointSizeResult = 0.25;	
	ACHAR stringResult[2];
	ACHAR prompt[100];
	AcDbObjectId pObj;	


	selectObject(pObj);
	if (pObj)
	{
		acedInitGet(RSG_NONULL | RSG_NOZERO | RSG_NONEG, NULL);
		acedGetReal(_T("\nIntroduceti inaltime text: "), &textHeightResult);
		acedGetReal(_T("\nIntroduceti dimensiunea punctului: "), &pointSizeResult);

		extractVertexCoords(pObj, m_3dPoints);
		if (m_3dPoints.size() > 0)
		{
			if (insertPoints(m_3dPoints, 32, pointSizeResult, textHeightResult))
			{
				acedInitGet(RSG_NONULL, _T("Y N"));
				acedGetKword(_T("\nInseram tabel de coordonate? [Yes No]:"), stringResult);
				if (wcscmp(stringResult, _T("N")))
				generateInventarTable(m_3dPoints,textHeightResult);

				//swprintf(prompt, _T("\nExportam fisier de coordonate? [Y/N]<stringResult=%s>: "), stringResult);
				acedInitGet(RSG_NONULL, _T("Y N"));
				acedGetKword(_T("\nExportam fisier de coordonate? [Yes No]: " ), stringResult);
				if (wcscmp(stringResult, _T("N")))
				{
				
				struct resbuf* result = NULL;
				if (acedGetFileNavDialog(_T("Save coordonates file"), NULL, _T("csv;txt"), _T("Save Dialog"), 1, &result) != RTERROR)
				{
					ExportClass* csvExport = new ExportClass(result->resval.rstring);
					csvExport->exportInventarCSV(m_3dPoints, startIndex);

					//*****Release memory area*****/
					acutRelRb(result);
					delete csvExport;
				}
				}
			}
		}
	}

	else
	{
		acutPrintf(_T("\nError nici un obiect selectat!"));
	}

}