bool KX_IpoActuator::Update(double curtime, bool frame)
{
	// result = true if animation has to be continued, false if animation stops
	// maybe there are events for us in the queue !
	bool bNegativeEvent = false;
	bool numevents = false;
	bool bIpoStart = false;

	curtime -= KX_KetsjiEngine::GetSuspendedDelta();

	if (frame)
	{
		numevents = m_posevent || m_negevent;
		bNegativeEvent = IsNegativeEvent();
		RemoveAllEvents();
	}
	
	float  start_smaller_then_end = ( m_startframe < m_endframe ? 1.0f : -1.0f);

	bool result=true;
	if (!bNegativeEvent)
	{
		if (m_starttime < -2.0f*fabs(m_endframe - m_startframe))
		{
			// start for all Ipo, initial start for LOOP_STOP
			m_starttime = curtime;
			m_bIpoPlaying = true;
			bIpoStart = true;
		}
	}

	switch ((IpoActType)m_type)
	{
		
	case KX_ACT_IPO_PLAY:
	{
		// Check if playing forwards.  result = ! finished
		
		if (start_smaller_then_end > 0.f)
			result = (m_localtime < m_endframe && m_bIpoPlaying);
		else
			result = (m_localtime > m_endframe && m_bIpoPlaying);
		
		if (result)
		{
			SetLocalTime(curtime);
		
			/* Perform clamping */
			ClampLocalTime();
	
			if (bIpoStart)
				((KX_GameObject*)GetParent())->InitIPO(m_ipo_as_force, m_ipo_add, m_ipo_local);
			((KX_GameObject*)GetParent())->UpdateIPO(m_localtime,m_recurse);
		} else
		{
			m_localtime=m_startframe;
			m_direction=1;
		}
		break;
	}
	case KX_ACT_IPO_PINGPONG:
	{
		result = true;
		if (bNegativeEvent && !m_bIpoPlaying)
			result = false;
		else
			SetLocalTime(curtime);
			
		if (ClampLocalTime())
		{
			result = false;
			m_direction = -m_direction;
		}
		
		if (bIpoStart && m_direction > 0)
			((KX_GameObject*)GetParent())->InitIPO(m_ipo_as_force, m_ipo_add, m_ipo_local);
		((KX_GameObject*)GetParent())->UpdateIPO(m_localtime,m_recurse);
		break;
	}
	case KX_ACT_IPO_FLIPPER:
	{
		if (bNegativeEvent && !m_bIpoPlaying)
			result = false;
		if (numevents)
		{
			float oldDirection = m_direction;
			if (bNegativeEvent)
				m_direction = -1;
			else
				m_direction = 1;
			if (m_direction != oldDirection)
				// changing direction, reset start time
				SetStartTime(curtime);
		}
		
		SetLocalTime(curtime);
		
		if (ClampLocalTime() && m_localtime == m_startframe)
			result = false;

		if (bIpoStart)
			((KX_GameObject*)GetParent())->InitIPO(m_ipo_as_force, m_ipo_add, m_ipo_local);
		((KX_GameObject*)GetParent())->UpdateIPO(m_localtime,m_recurse);
		break;
	}

	case KX_ACT_IPO_LOOPSTOP:
	{
		if (numevents)
		{
			if (bNegativeEvent)
			{
				result = false;
				m_bNegativeEvent = false;
				numevents = false;
			}
			if (!m_bIpoPlaying)
			{
				// Ipo was stopped, make sure we will restart from where it stopped
				SetStartTime(curtime);
				if (!bNegativeEvent)
					// positive signal will restart the Ipo
					m_bIpoPlaying = true;
			}

		} // fall through to loopend, and quit the ipo animation immediatly 
	}
	case KX_ACT_IPO_LOOPEND:
	{
		if (numevents) {
			if (bNegativeEvent && m_bIpoPlaying) {
				m_bNegativeEvent = true;
			}
		}
		
		if (bNegativeEvent && !m_bIpoPlaying) {
			result = false;
		} 
		else
		{
			if (m_localtime*start_smaller_then_end < m_endframe*start_smaller_then_end)
			{
				SetLocalTime(curtime);
			}
			else {
				if (!m_bNegativeEvent) {
					/* Perform wraparound */
					SetLocalTime(curtime);
					if (start_smaller_then_end > 0.f)
						m_localtime = m_startframe + fmod(m_localtime - m_startframe, m_endframe - m_startframe);
					else
						m_localtime = m_startframe - fmod(m_startframe - m_localtime, m_startframe - m_endframe);
					SetStartTime(curtime);
					bIpoStart = true;
				}
				else
				{
					/* Perform clamping */
					m_localtime=m_endframe;
					result = false;
					m_bNegativeEvent = false;
				}
			}
		}
		
		if (m_bIpoPlaying && bIpoStart)
			((KX_GameObject*)GetParent())->InitIPO(m_ipo_as_force, m_ipo_add, m_ipo_local);
		((KX_GameObject*)GetParent())->UpdateIPO(m_localtime,m_recurse);
		break;
	}
	
	case KX_ACT_IPO_KEY2KEY:
	{
		// not implemented yet
		result = false;
		break;
	}
	
	case KX_ACT_IPO_FROM_PROP:
	{
		result = !bNegativeEvent;

		CValue* propval = GetParent()->GetProperty(m_propname);
		if (propval)
		{
			m_localtime = propval->GetNumber(); 
	
			if (bIpoStart)
				((KX_GameObject*)GetParent())->InitIPO(m_ipo_as_force, m_ipo_add, m_ipo_local);
			((KX_GameObject*)GetParent())->UpdateIPO(m_localtime,m_recurse);
		} else
		{
			result = false;
		}
		break;
	}
		
	default:
		result = false;
	}

	/* Set the property if its defined */
	if (m_framepropname[0] != '\0') {
		CValue* propowner = GetParent();
		CValue* oldprop = propowner->GetProperty(m_framepropname);
		CValue* newval = new CFloatValue(m_localtime);
		if (oldprop) {
			oldprop->SetValue(newval);
		} else {
			propowner->SetProperty(m_framepropname, newval);
		}
		newval->Release();
	}

	if (!result)
	{
		if (m_type != KX_ACT_IPO_LOOPSTOP)
			this->ResetStartTime();
		m_bIpoPlaying = false;
	}

	return result;
}