RETCODE StatusTeleport::Update()
{
	RETCODE ret = RETCODE_SUCCESS;

	Creature *pCre = (Creature *)IDPageQuery(m_owner);

	if(m_bGO)
	{
		if(pCre)
		{
			hOBJ obj = pCre->GetOBJ(); assert(obj);

			double t = TimeGetTime(&m_delay)/TimeGetDelay(&m_delay);

			if(t >= 1)
			{
				t = 1;
				TimeReset(&m_delay);
			}

			OBJSetAlpha(obj, m_bFading ? 1-t : t);

			//are we done?
			if(t == 1 && !m_bFading)
				ret = RETCODE_STATUS_DONE;
			else if(t == 1 && m_bFading)
			{
				m_bFading = false;

				//set to new location
				pCre->SetLoc(m_dest);

				D3DXVECTOR3 zeroVel(0,0,0);
				pCre->SetVel(zeroVel);

				pCre->CREPlaySound(38);
			}
		}
		else
			ret = RETCODE_STATUS_DONE;
	}

	return ret;
}