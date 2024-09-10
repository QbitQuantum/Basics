void DXFrame::CPUCounter::Update(DXManager* manager, Font* font)
{
	PDH_FMT_COUNTERVALUE value;
	if ((m_LastSampleTime + 1000) < GetTickCount64())
	{
		m_LastSampleTime = (unsigned long)GetTickCount64();
		PdhCollectQueryData(m_HandleQuery);
		PdhGetFormattedCounterValue(m_HandleCounter, PDH_FMT_LONG, NULL, &value);
		m_CPUUsage = (int)value.longValue;
		m_CPUText->SetText(manager, font, "CPU:" + std::to_string(m_CPUUsage) + "%");

		if (m_CPUUsage <= 30)
			m_CPUText->SetColor(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		else if (m_CPUUsage >= 30 && m_CPUUsage < 60)
			m_CPUText->SetColor(D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.9f));
		else if (m_CPUUsage >= 60)
			m_CPUText->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.9f));
	}
}