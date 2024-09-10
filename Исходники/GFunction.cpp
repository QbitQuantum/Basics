	void MeasureTokenLength()
	{
		if(IsNameChar(*m_pNext))
		{
			for(m_len = 1; IsNameChar(m_pNext[m_len]) || IsDigit(m_pNext[m_len]); m_len++)
			{
			}
			m_type = name;
		}
		else if(IsDigit(*m_pNext) || *m_pNext == '.')
		{
			int exps = 0;
			int decimals = 0;
			if(*m_pNext == '.')
				decimals++;
			for(m_len = 1; m_pNext[m_len] != '\0'; m_len++)
			{
				if(IsDigit(m_pNext[m_len]))
					continue;
				if(m_pNext[m_len] == '.' && decimals == 0 && exps == 0)
				{
					decimals++;
					continue;
				}
				if(m_pNext[m_len] == 'e' && IsDigit(m_pNext[m_len + 1]) && exps == 0)
				{
					exps++;
					continue;
				}
				break;
			}
			m_type = number;
		}
		else
		{
			m_len = 1;
			m_type = symbol;
		}
	}