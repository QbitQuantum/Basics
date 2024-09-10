void eGTable::sectionRead(const __u8 *d)
{
	unsigned int last_section_number = d[7];
	m_table.flags &= ~eDVBTableSpec::tfAnyVersion;
	m_table.flags |= eDVBTableSpec::tfThisVersion;
	m_table.version = (d[5]>>1)&0x1F;

		/* if a section is missing, we retry reading the
		   whole data up to 5 times. if after that the
		   section is still missing, we timeout. */
	if (m_tries > 5 * (last_section_number+1))
	{
		timeout();
		return;
	}
	
	m_tries++;

	if (createTable(d[6], d, last_section_number + 1))
	{
		if (m_timeout)
			m_timeout->stop();
		if (m_reader)
		{
			m_reader->stop();
			m_reader=0;
		}
		m_sectionRead_conn=0;
		ready = 1;
		tableReady(error);
	} else if ((m_table.flags & eDVBTableSpec::tfHaveTimeout) && m_timeout)
		m_timeout->start(m_table.timeout, 1); // reset timeout
}