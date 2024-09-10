	long   SmtTinFclsAdoLayer::GetTinNodes(SmtTin *&pTin)
	{
		int nPoints = 0;
		m_SmtRecordset.GetCollect("geom_pointnum",nPoints);

		long lDataSize = m_SmtRecordset.GetField("geom_points")->ActualSize;
		if(lDataSize > 0)
		{
			_variant_t varBLOB;
			varBLOB = m_SmtRecordset.GetField("geom_points")->GetChunk(lDataSize);
			if(varBLOB.vt == (VT_ARRAY | VT_UI1)) 
			{
				RawPoint *pRawPointBuf = NULL;
				SmtPoint *pPointBuf = new SmtPoint[nPoints];
				SafeArrayAccessData(varBLOB.parray,(void **)&pRawPointBuf);
				
				for (int i = 0 ; i < nPoints;i++)
				{
					pPointBuf[i].SetX(pRawPointBuf[i].x);
					pPointBuf[i].SetY(pRawPointBuf[i].y);
				}
			
				SafeArrayUnaccessData (varBLOB.parray);	

				//
				pTin->AddPointCollection(pPointBuf,nPoints);

				SMT_SAFE_DELETE_A(pPointBuf);
			}
		}
		
		return SMT_ERR_NONE;
	}