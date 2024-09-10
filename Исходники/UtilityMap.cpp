void vtUtilityMap::GetPoleExtents(DRECT &rect)
{
	if (m_Poles.IsEmpty())
		return;

	rect.SetRect(1E9, -1E9, -1E9, 1E9);

	int i, size = m_Poles.GetSize();
	for (i = 0; i < size; i++)
	{
		vtPole *pole = m_Poles.GetAt(i);
		rect.GrowToContainPoint(pole->m_p);
	}
}