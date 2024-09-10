void CBCGPAppointmentDSMap::Add (const COleDateTime& date, const CRect& rect)
{
	CBCGPAppointmentDrawStruct* pDS = NULL;
	
	BOOL bEmpty = IsEmpty ();

	if (!bEmpty)
	{
		pDS = Get (date);
	}
	
	if (pDS == NULL)
	{
		if (!bEmpty)
		{
			XDateInterval& interval = m_DSMap[m_DSMap.GetSize () - 1];
			CBCGPAppointmentDrawStruct* pDSPrev = interval.m_pDS;
			
			if (IsConcatenate () &&
				interval.m_date2 < date && (date - interval.m_date2).GetTotalDays () <= 1.0)
			{
				if (pDSPrev->GetRect ().top    == rect.top &&
					pDSPrev->GetRect ().bottom == rect.bottom)
				{
					CRect rt;
					rt.UnionRect (pDSPrev->GetRect (), rect);

					pDSPrev->SetRect (rt);
					pDSPrev->SetBorder((CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER)
						(pDSPrev->GetBorder () | 
						 CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER_FINISH));

					interval.m_date2 = date;

					return;
				}
			}

			pDSPrev->SetBorder ((CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER)
				(pDSPrev->GetBorder () & ~CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER_FINISH));

			pDS = CreateStruct ();
			pDS->SetBorder (CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER_FINISH);
		}
		else
		{
			pDS = CreateStruct ();
			pDS->SetBorder (CBCGPAppointmentDrawStruct::BCGP_APPOINTMENT_DS_BORDER_START);
		}

		XDateInterval interval(date, pDS);
		m_DSMap.Add(interval);
	}

	pDS->SetRect (rect);
}