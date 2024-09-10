int MTButton3D::Callback(unsigned int msg, unsigned int wParam, int lParam)
{
	switch(msg)
	{
	case MENU_ITM_MSG_UPDATE:
		{
			bool bDone = false;
			D3DXVECTOR3 curLoc; OBJGetLoc(m_btnOBJ, (float*)curLoc);

			switch(wParam)
			{
			case MITM_UPDATE_NORMAL:
				break;

			case MITM_UPDATE_ENTERING:
				{
					float alpha;
					double t = TimeGetTime(&m_delay)/TimeGetDelay(&m_delay);

					if(t >= 1)
					{
						t = 1;

						bDone = true;
					}

					D3DXVec3Lerp(&curLoc, &m_startLoc, &m_endLoc, t);
					
					alpha = m_startAlpha + t*(m_endAlpha - m_startAlpha);

					OBJTranslate(m_btnOBJ, (float*)curLoc, false);
					OBJSetAlpha(m_btnOBJ, alpha);
				}
				break;

			case MITM_UPDATE_EXITING:
				{
					float alpha;
					double t = TimeGetTime(&m_delay)/TimeGetDelay(&m_delay);

					if(t >= 1)
					{
						t = 1;

						bDone = true;
					}

					D3DXVec3Lerp(&curLoc, &m_endLoc, &m_startLoc, t);
					
					alpha = m_endAlpha + t*(m_startAlpha - m_endAlpha);

					OBJTranslate(m_btnOBJ, (float*)curLoc, false);
					OBJSetAlpha(m_btnOBJ, alpha);
				}
				break;
			}

			OBJUpdateFrame(m_btnOBJ);

			if(bDone)
				return RETCODE_BREAK;
		}
		break;

	case MENU_ITM_MSG_DRAW:
		OBJDisplay(m_btnOBJ);
		break;

	case MENU_ITM_MSG_SELECT:
		if(wParam)
		{
			OBJSetState(m_btnOBJ, BUTTON3D_ANIM_SELECT);
		}
		else
		{
			OBJSetState(m_btnOBJ, BUTTON3D_ANIM_UNSELECT);
		}
		break;

	case MENU_ITM_MSG_ACTIVATE:
		break;

	case MENU_ITM_MSG_STATECHANGE:
		TimeReset(&m_delay);
		break;
	}

	return RETCODE_SUCCESS;
}