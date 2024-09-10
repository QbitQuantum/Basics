	virtual void HandleMessage(const CMessage& msg, bool UNUSED(global))
	{
		switch (msg.GetType())
		{
		case MT_Interpolate:
		{
			const CMessageInterpolate& msgData = static_cast<const CMessageInterpolate&> (msg);

			float rotY = m_RotY.ToFloat();

			if (rotY != m_InterpolatedRotY)
			{
				float delta = rotY - m_InterpolatedRotY;
				// Wrap delta to -M_PI..M_PI
				delta = fmodf(delta + (float)M_PI, 2*(float)M_PI); // range -2PI..2PI
				if (delta < 0) delta += 2*(float)M_PI; // range 0..2PI
				delta -= (float)M_PI; // range -M_PI..M_PI
				// Clamp to max rate
				float deltaClamped = clamp(delta, -m_RotYSpeed*msgData.deltaSimTime, +m_RotYSpeed*msgData.deltaSimTime);
				// Calculate new orientation, in a peculiar way in order to make sure the
				// result gets close to m_orientation (rather than being n*2*M_PI out)
				m_InterpolatedRotY = rotY + deltaClamped - delta;
				
				// update the visual XZ rotation
				if (m_InWorld)
				{
					m_LastInterpolatedRotX = m_InterpolatedRotX;
					m_LastInterpolatedRotZ = m_InterpolatedRotZ;

					UpdateXZRotation();
				}
			}
			
			if (m_InWorld && m_NeedInitialXZRotation)
			{
				// the terrain probably wasn't loaded last time we tried, so update the XZ rotation without interpolation
				UpdateXZRotation();

				m_LastInterpolatedRotX = m_InterpolatedRotX;
				m_LastInterpolatedRotZ = m_InterpolatedRotZ;
			}

			break;
		}
		case MT_TurnStart:
		{
			m_LastInterpolatedRotX = m_InterpolatedRotX;
			m_LastInterpolatedRotZ = m_InterpolatedRotZ;

			if (m_InWorld && (m_LastX != m_X || m_LastZ != m_Z))
				UpdateXZRotation();

			// Store the positions from the turn before
			m_PrevX = m_LastX;
			m_PrevZ = m_LastZ;

			m_LastX = m_X;
			m_LastZ = m_Z;

			break;
		}
	}
};