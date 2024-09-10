	double WegstueckSchlange::startDefinitionswert( double def )
	{
		double definitionswert = 0.0;
		for (deque<sWegstueck::Zeiger>::iterator iter = m_schlange.begin();iter < m_schlange.end();iter++)
		{
			double alterDefwert = definitionswert;
			definitionswert += (*iter)->weglaenge();
			if (def<definitionswert)
				return alterDefwert;
		}
		return NaN();
	}