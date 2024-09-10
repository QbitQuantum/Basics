/**
 * DIPSW をタップした
 */
void SndOptSpbPage::OnDipSw()
{
	RECT rect1;
	m_dipsw.GetWindowRect(&rect1);

	RECT rect2;
	m_dipsw.GetClientRect(&rect2);

	POINT p;
	::GetCursorPos(&p);
	p.x += rect2.left - rect1.left;
	p.y += rect2.top - rect1.top;
	p.x /= 9;
	p.y /= 9;
	if ((p.y < 1) || (p.y >= 3))
	{
		return;
	}

	UINT8 cValue = m_spb;
	UINT8 cVR = m_vr;
	if ((p.x >= 2) && (p.x < 5))
	{
		UINT8 cBit = 0x40 << (2 - p.y);
		switch (p.x)
		{
			case 2:
				cValue |= cBit;
				break;

			case 3:
				cValue ^= cBit;
				break;

			case 4:
				cValue &= ~cBit;
				break;
		}
	}
	else if (p.x == 7)
	{
		cValue ^= 0x20;
	}
	else if ((p.x >= 10) && (p.x < 12))
	{
		cValue = static_cast<UINT8>((cValue & (~0x10)) | ((p.x - 10) << 4));
	}
	else if ((p.x >= 14) && (p.x < 19))
	{
		cValue = static_cast<UINT8>((cValue & (~7)) | (p.x - 14));
	}
	else if ((p.x >= 21) && (p.x < 24))
	{
		cVR ^= (3 - p.y);
	}

	if ((m_spb != cValue) || (m_vr != cVR))
	{
		Set(cValue, cVR);
		m_dipsw.Invalidate();
	}
}