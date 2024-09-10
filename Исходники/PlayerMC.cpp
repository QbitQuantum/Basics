void PlayerMC::Dispatch()
{
	// set player to look at boss
	DE::Vector3 direction = ((Player*)m_pOwner)->GetBoss()->GetPosition() - m_pOwner->GetPosition();
	if (!direction.iszero())
	{
		float length = direction.Length();
		DE::Vector3 cross = Cross(m_pOwner->GetTransform()->GetForward().Normal(), direction.Normal());
		float dot = cross.Dot(DE::Vector3::UnitY);
		float theta = asinf(cross.Length());
		int y = 1;
		if (dot < 0.0f)
		{
			y = -1;
		}
		float speedUp = (theta > PI) ? 3.0f : 1.0f;
		DE::Quaternion quat(DE::Vector3(0, y, 0), theta * m_fDeltaTime * speedUp);
		m_pOwner->TransformBy(quat.GetRotationMatrix());
	}

	// only send new animation event when player is not being impacted
	if (((Player*)m_pOwner)->GetState() != Player::IMPACTING)
	{
		if (m_vTrans.iszero() && ((Player*)m_pOwner)->GetState() == Player::LOCOMOTION && m_bWalk)
		{
			DE::Handle h(sizeof(Player_Walk_END_Event));
			new (h) Player_Walk_END_Event;
			DE::EventQueue::GetInstance()->Add(h, DE::GAME_EVENT);
			m_bWalk = false;
		}
		else if (m_bDodge && !m_vTrans.iszero() && ((Player*)m_pOwner)->GetStamina() >= 20.0f)
		{
			m_vDodgeDir = m_vTrans.Normal();
			m_bDodge = false;

			((Player*)m_pOwner)->SetState(Player::DOGDING);
			((Player*)m_pOwner)->AddStamina(-20.0f);
			DE::Handle h(sizeof(Player_Dodge_START_Event));
			new (h) Player_Dodge_START_Event;
			((Player_Dodge_START_Event*)h.Raw())->m_vDir = m_vTrans.Normal();
			DE::EventQueue::GetInstance()->Add(h, DE::GAME_EVENT);
		}
		else if (!m_vTrans.iszero() && ((Player*)m_pOwner)->GetState() == Player::LOCOMOTION)
		{
			Move(m_vTrans);
			m_bWalk = true;
			if (m_bRun)
			{
				if (!m_bRunLock && ((Player*)m_pOwner)->GetStamina() >= 4.0f)
				{
					((Player*)m_pOwner)->AddStamina(-2.0f);
				}
				else
				{
					m_bRunLock = true;
					m_bRun = false;
				}
			}

			DE::Handle h(sizeof(Player_Walk_PLAYING_Event));
			new (h) Player_Walk_PLAYING_Event;
			((Player_Walk_PLAYING_Event*)h.Raw())->m_vDir = m_vTrans.Normal();
			((Player_Walk_PLAYING_Event*)h.Raw())->m_bRun = m_bRun;
			DE::EventQueue::GetInstance()->Add(h, DE::GAME_EVENT);
		}
		if (((Player*)m_pOwner)->GetState() == Player::DOGDING)
		{
			Move(m_vDodgeDir * m_fSpeed * m_fDeltaTime * 3.0f);
		}
		if (m_ComboSequence[0] || m_ComboSequence[1])
		{
			m_fComboTime += m_fDeltaTime;
		}
		if (m_ComboSequence[2])
		{
			DE::Vector3 vForward = DE::Vector3::UnitZ;
			Move(vForward * m_fSpeed * m_fDeltaTime * 0.5f);
		}
	}
	m_vTrans = DE::Vector3::Zero;
	m_bDodge = false;
	m_bRun = false;
}