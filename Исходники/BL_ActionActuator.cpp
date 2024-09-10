bool BL_ActionActuator::Update(double curtime, bool frame)
{
	bool bNegativeEvent = false;
	bool bPositiveEvent = false;
	bool bUseContinue = false;
	KX_GameObject *obj = (KX_GameObject*)GetParent();
	short playtype = BL_Action::ACT_MODE_PLAY;
	float start = m_startframe;
	float end = m_endframe;

	// If we don't have an action, we can't do anything
	if (!m_action)
		return false;

	// Convert our playtype to one that BL_Action likes
	switch(m_playtype)
	{
		case ACT_ACTION_LOOP_END:
		case ACT_ACTION_LOOP_STOP:
			playtype = BL_Action::ACT_MODE_LOOP;
			break;

		case ACT_ACTION_PINGPONG:
			// We handle ping pong ourselves to increase compabitility
			// with files made prior to animation changes from GSoC 2011.
			playtype = BL_Action::ACT_MODE_PLAY;
		
			if (m_flag & ACT_FLAG_REVERSE)
			{
				start = m_endframe;
				end = m_startframe;
			}

			break;
		case ACT_ACTION_FROM_PROP:
			CValue* prop = GetParent()->GetProperty(m_propname);

			// If we don't have a property, we can't do anything, so just bail
			if (!prop) return false;

			playtype = BL_Action::ACT_MODE_PLAY;
			start = end = prop->GetNumber();

			break;
	}

	if (m_flag & ACT_FLAG_CONTINUE)
		bUseContinue = true;
	
	
	// Handle events
	if (frame)
	{
		bNegativeEvent = m_negevent;
		bPositiveEvent = m_posevent;
		RemoveAllEvents();
	}

	// "Active" actions need to keep updating their current frame
	if (bUseContinue && (m_flag & ACT_FLAG_ACTIVE))
		m_localtime = obj->GetActionFrame(m_layer);

	if (m_flag & ACT_FLAG_ATTEMPT_PLAY)
		SetLocalTime(curtime);
	else
		ResetStartTime(curtime);

	// Handle a frame property if it's defined
	if ((m_flag & ACT_FLAG_ACTIVE) && m_framepropname[0] != 0)
	{
		CValue* oldprop = obj->GetProperty(m_framepropname);
		CValue* newval = new CFloatValue(obj->GetActionFrame(m_layer));
		if (oldprop)
			oldprop->SetValue(newval);
		else
			obj->SetProperty(m_framepropname, newval);

		newval->Release();
	}

	// Handle a finished animation
	if ((m_flag & ACT_FLAG_PLAY_END) && (m_flag & ACT_FLAG_ACTIVE) && obj->IsActionDone(m_layer))
	{
		m_flag &= ~ACT_FLAG_ACTIVE;
		m_flag &= ~ACT_FLAG_ATTEMPT_PLAY;

		if (m_playtype == ACT_ACTION_PINGPONG)
			m_flag ^= ACT_FLAG_REVERSE;
		return false;
	}
	
	// If a different action is playing, we've been overruled and are no longer active
	if (obj->GetCurrentAction(m_layer) != m_action && !obj->IsActionDone(m_layer))
		m_flag &= ~ACT_FLAG_ACTIVE;

	if (bPositiveEvent || (m_flag & ACT_FLAG_ATTEMPT_PLAY && !(m_flag & ACT_FLAG_ACTIVE)))
	{
		if (bPositiveEvent && m_playtype == ACT_ACTION_PLAY)
		{
			if (obj->IsActionDone(m_layer))
				m_localtime = start;
			ResetStartTime(curtime);
		}

		if (obj->PlayAction(m_action->id.name+2, start, end, m_layer, m_priority, m_blendin, playtype, m_layer_weight, m_ipo_flags))
		{
			m_flag |= ACT_FLAG_ACTIVE;
			if (bUseContinue)
				obj->SetActionFrame(m_layer, m_localtime);

			if (m_playtype == ACT_ACTION_PLAY || m_playtype == ACT_ACTION_PINGPONG)
				m_flag |= ACT_FLAG_PLAY_END;
			else
				m_flag &= ~ACT_FLAG_PLAY_END;
		}
		m_flag |= ACT_FLAG_ATTEMPT_PLAY;
	}
	else if ((m_flag & ACT_FLAG_ACTIVE) && bNegativeEvent)
	{	
		m_flag &= ~ACT_FLAG_ATTEMPT_PLAY;
		m_localtime = obj->GetActionFrame(m_layer);
		bAction *curr_action = obj->GetCurrentAction(m_layer);
		if (curr_action && curr_action != m_action)
		{
			// Someone changed the action on us, so we wont mess with it
			// Hopefully there wont be too many problems with two actuators using
			// the same action...
			m_flag &= ~ACT_FLAG_ACTIVE;
			return false;
		}

		switch(m_playtype)
		{
			case ACT_ACTION_LOOP_STOP:
				obj->StopAction(m_layer); // Stop the action after getting the frame

				// We're done
				m_flag &= ~ACT_FLAG_ACTIVE;
				return false;
			case ACT_ACTION_LOOP_END:
				// Convert into a play and let it finish
				obj->SetPlayMode(m_layer, BL_Action::ACT_MODE_PLAY);

				m_flag |= ACT_FLAG_PLAY_END;
				break;
	
			case ACT_ACTION_FLIPPER:
				// Convert into a play action and play back to the beginning
				end = start;
				start = obj->GetActionFrame(m_layer);
				obj->PlayAction(m_action->id.name+2, start, end, m_layer, m_priority, 0, BL_Action::ACT_MODE_PLAY, m_layer_weight, m_ipo_flags);

				m_flag |= ACT_FLAG_PLAY_END;
				break;
		}
	}

	return m_flag & ACT_FLAG_ACTIVE;
}