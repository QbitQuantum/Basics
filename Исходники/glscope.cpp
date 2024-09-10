void GLScope::handleMode()
{
	switch(m_mode) {
		case ModeIQ:
			m_displayTrace = &m_rawTrace;
			m_amp1 = m_amp;
			m_amp2 = m_amp;
			m_ofs1 = 0.0;
			m_ofs2 = 0.0;
			break;

		case ModeMagLinPha: {
			m_mathTrace.resize(m_rawTrace.size());
			std::vector<Complex>::iterator dst = m_mathTrace.begin();
			for(std::vector<Complex>::const_iterator src = m_rawTrace.begin(); src != m_rawTrace.end(); ++src)
				*dst++ = Complex(abs(*src), arg(*src) / M_PI);
			m_displayTrace = &m_mathTrace;
			m_amp1 = m_amp;
			m_amp2 = 1.0;
			m_ofs1 = -1.0 / m_amp1;
			m_ofs2 = 0.0;
			break;
		}

		case ModeMagdBPha: {
			m_mathTrace.resize(m_rawTrace.size());
			std::vector<Complex>::iterator dst = m_mathTrace.begin();
			Real mult = (10.0f / log2f(10.0f));
			for(std::vector<Complex>::const_iterator src = m_rawTrace.begin(); src != m_rawTrace.end(); ++src) {
				Real v = src->real() * src->real() + src->imag() * src->imag();
				v = (96.0 + (mult * log2f(v))) / 96.0;
				*dst++ = Complex(v, arg(*src) / M_PI);
			}
			m_displayTrace = &m_mathTrace;
			m_amp1 = 2.0 * m_amp;
			m_amp2 = 1.0;
			m_ofs1 = -1.0 / m_amp1;
			m_ofs2 = 0.0;
			break;
		}

		case ModeDerived12: {
			if(m_rawTrace.size() > 3) {
				m_mathTrace.resize(m_rawTrace.size() - 3);
				std::vector<Complex>::iterator dst = m_mathTrace.begin();
				for(uint i = 3; i < m_rawTrace.size() ; i++) {
					*dst++ = Complex(
						abs(m_rawTrace[i] - m_rawTrace[i - 1]),
						abs(m_rawTrace[i] - m_rawTrace[i - 1]) - abs(m_rawTrace[i - 2] - m_rawTrace[i - 3]));
				}
				m_displayTrace = &m_mathTrace;
				m_amp1 = m_amp;
				m_amp2 = m_amp;
				m_ofs1 = -1.0 / m_amp1;
				m_ofs2 = 0.0;
			}
			break;
		}

		case ModeCyclostationary: {
			if(m_rawTrace.size() > 2) {
				m_mathTrace.resize(m_rawTrace.size() - 2);
				std::vector<Complex>::iterator dst = m_mathTrace.begin();
				for(uint i = 2; i < m_rawTrace.size() ; i++)
					*dst++ = Complex(abs(m_rawTrace[i] - conj(m_rawTrace[i - 1])), 0);
				m_displayTrace = &m_mathTrace;
				m_amp1 = m_amp;
				m_amp2 = m_amp;
				m_ofs1 = -1.0 / m_amp1;
				m_ofs2 = 0.0;
			}
			break;
		}

	}
}