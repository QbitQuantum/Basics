/*
 * 功能: 场景相机状态自动更新
 * 摘要: 该函数功能主要实现,根据自身的当前状态自动更新相机内部数据,无须外部干预
 * 参数: -
 * 返回值: -
 * 作者: lpf
 * 创建日期: 2008.02.02
 * 修改日志:
 *	2008.03.08 - lpf
 *		修正了相机在执行水平旋转和垂直旋转,并到达目的位置时,会不停的震动问题
 *	2008.10.17 - lpf
 * 		暂时屏蔽了"处理垂直角度与距离的限制";
 */
void CRegionCamera::Update(void)
{
	CClientRegion * c = GetGame()->GetRegion();
	if (c == NULL) /*&& GetGame()->GetSetup()->bSound*/ 
		return;

	// 处理场景3D音效
	D3DXVECTOR3 * pos;
	D3DXVECTOR3	  face;
	D3DXVECTOR3   right;
	D3DXVECTOR3   up;

	pos = c->GetCamera()->GetPosition();

	//pos->z = -pos->z;
	GetGame()->GetAudioList()->SetListenerPosition(*pos);

	//pos->z = -pos->z;
	face = (*c->GetCamera()->GetView()) - (*pos);

	Vector3 v = face;
	D3DXVec3Normalize(&face, &face);
	D3DXVec3Cross(&right, &Vector3(0, 1, 0), &face);
	D3DXVec3Normalize(&right, &right);
	D3DXVec3Cross(&up, &face, &right);

	//face.z = -face.z;
	//up.z   = -up.z;
	GetGame()->GetAudioList()->SetListenerOritation(face, up);

	if (g_bDebug)
	{
		if (GetKeyboard()->IsKeyDown(DIK_TAB))
		{
			char t[255];
			sprintf(t, "距离平方:%f", (v.x) * (v.x) + v.y * v.y + (v.z) * (v.z));
			GetGame()->OutPutText(140, 40, t, 255, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	// 回到默认摄像机镜头角度H
	if (m_dwState & SCS_REPOS_H)
	{
		if (abs(m_iHoriAngle - m_iSourceHoriAngle) <= 5)
		{
			m_dwState	 &= ~SCS_REPOS_H;
			m_iHoriAngle = m_iSourceHoriAngle;
		}else
		{
			if (m_iHoriAngle > 180)
				m_iHoriAngle -= 360;
			else if(m_iHoriAngle < -180)
				m_iHoriAngle += 360;
			if (m_iHoriAngle > -45 && m_iHoriAngle < 135)
				m_iHoriAngle += 4;
			else if (m_iHoriAngle <= -45 || m_iHoriAngle >= 135)
				m_iHoriAngle -= 4;
		}
	}
	// 回到默认摄像机镜头角度V
	if (m_dwState & SCS_REPOS_V)
	{
		if (abs(m_iVertAngle - m_iSourceVertAngle) <= 5)
		{
			m_dwState	 &= ~SCS_REPOS_V;
			m_iVertAngle = m_iSourceVertAngle;
		}else
		{
			m_iVertAngle += (m_iSourceVertAngle - m_iVertAngle)/abs(m_iSourceVertAngle - m_iVertAngle) * 4;
		}
	}
	// 回到默认摄像机镜头角度V
	if (m_dwState & SCS_REPOS_D)
	{
		if (abs(s_fDistance - 17.0f) <= 1.0f)
		{
			m_dwState	 &= ~SCS_REPOS_D;
			s_fDistance = 17.0f;
		}else
		{
			s_fDistance += (17.0f - s_fDistance)/abs(17.0f - s_fDistance) * 0.5f;
		}
	}

	// 处理相机移动
	if (m_dwState & SCS_MOVE)
	{
		if (D3DXVec3Length(&m_vMoveDis) < m_fMoveDis)
			m_vMoveDis += m_vMoveSpeed;
		//else
		//	m_dwState &= ~SCS_MOVE;
	}

	// 处理相机水平旋转
	if (m_dwState & SCS_ROTATE_H)
	{
		if (m_iHoriAngle > m_iHDesAngle)
		{
			m_fHCurAngle -= m_fHRotateSpeed;
			m_iHoriAngle = (int)m_fHCurAngle;

			if (m_iHoriAngle < m_iHDesAngle)
				m_iHoriAngle = m_iHDesAngle;
		}else if (m_iHoriAngle < m_iHDesAngle)
		{
			m_fHCurAngle += m_fHRotateSpeed;
			m_iHoriAngle = (int)m_fHCurAngle;

			if (m_iHoriAngle > m_iHDesAngle)
				m_iHoriAngle = m_iHDesAngle;
		}else
			m_dwState &= ~SCS_ROTATE_H;
	}

	// 处理相机垂直旋转
	if (m_dwState & SCS_ROTATE_V)
	{
		if (m_iVertAngle > m_iVDesAngle)
		{
			m_fVCurAngle -= m_fVRotateSpeed;
			m_iVertAngle = (int)m_fVCurAngle;

			if (m_iVertAngle < m_iVDesAngle)
				m_iVertAngle = m_iVDesAngle;
		}else if (m_iVertAngle < m_iVDesAngle)
		{
			m_fVCurAngle += m_fVRotateSpeed;
			m_iVertAngle = (int)m_fVCurAngle;

			if (m_iVertAngle > m_iVDesAngle)
				m_iVertAngle = m_iVDesAngle;
		}else
			m_dwState &= ~SCS_ROTATE_V;
	}

	// 处理相机缩放
	if (m_dwState & SCS_ZOOM)
	{
		if (m_fZoomSpeed > 0.0f)
		{
			if (s_fDistance < m_fZoomDesDis)
				s_fDistance += m_fZoomSpeed;
			else
				m_dwState &= ~SCS_ZOOM;
		}else if (m_fZoomSpeed < 0.0f)
		{
			if (s_fDistance > m_fZoomDesDis)
				s_fDistance += m_fZoomSpeed;
			else
				m_dwState &= ~SCS_ZOOM;
		}

		if (s_fDistance > s_fMaxDistance)
		{
			s_fDistance = s_fMaxDistance;
			m_dwState	&= ~SCS_ZOOM;
		}else if (s_fDistance < s_fMinDistance)
		{
			s_fDistance = s_fMinDistance;
			m_dwState	&= ~SCS_ZOOM;
		}
	}

	// 处理相机震动
	if (m_dwState & SCS_SHOCK)
	{
		static const float fOffsetArray[6] = { 1.0f, -0.6f, 0.8f, -0.2f, 0.4f, 0.0f };
		static int		   iOffPos		   = 0;
		
		DWORD dwCurrentTime = timeGetTime();
		DWORD dwTimeElapse  = dwCurrentTime - m_dwShockStartTime;
		if (dwTimeElapse > m_dwShockDelayTime)
		{
			m_fShcokrOffset = fOffsetArray[iOffPos] * m_fShockMaxRatio;
			if (dwTimeElapse > m_dwShockTimeLength)
			{
				iOffPos	  = 0;
				m_dwState &= ~SCS_SHOCK;
			}

			if (iOffPos > 4)
				iOffPos = 0;
			else
				++iOffPos;
		}
	}

	// 处理垂直角度与距离的限制
	//float angle = s_fDistance/17.0f * 43.0f;
	//m_fMinVAngle = angle > 43.0f?43.0f:angle;
	//if (m_iVertAngle < m_fMinVAngle)
	//{
	//	m_iVertAngle = m_fMinVAngle;
	//	m_fVCurAngle = m_iVertAngle;
	//}

	if (s_fDistance > 0.0f)
		m_fDistance = s_fDistance;
}