	void TimedFadeAction::Update(const Context & context)
	{
		float32 dt = float32(context.mTimeManager->GetSeconds());
		m_CurrentSeconds += dt;
		m_pSpriteComponent->SetColorMultiplier(
			Lerp(m_StartColor, m_EndColor, m_CurrentSeconds / m_Seconds)
			);
	}