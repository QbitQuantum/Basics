void _Universe::reset(void)
{
	for (int i = 0; i < m_nObj; i++)
	{
		deleteObject(i);
	}
}