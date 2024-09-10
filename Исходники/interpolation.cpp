		glm::fquat GetOrient(const glm::fquat &initial, bool bSlerp) const
		{
			if(bSlerp)
			{
				return Slerp(initial, g_Orients[m_ixFinalOrient], m_currTimer.GetAlpha());
			}
			else
			{
				return Lerp(initial, g_Orients[m_ixFinalOrient], m_currTimer.GetAlpha());
			}

			return initial;
		}