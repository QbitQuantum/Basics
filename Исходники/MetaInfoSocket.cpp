void MetainfoSocket::OnDelete()
{
	if (m_fil)
	{
		fclose(m_fil);
		m_fil = NULL;
		if (m_sz_read == m_sz)
		{
			InitSession();
		}
		else
		{
			
		}
	}
}