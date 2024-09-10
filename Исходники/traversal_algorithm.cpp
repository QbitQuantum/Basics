void traversal_algorithm::add_requests()
{
	while (m_invoke_count < m_branch_factor)
	{
		// Find the first node that hasn't already been queried.
		// TODO: Better heuristic
		std::vector<result>::iterator i = std::find_if(
			m_results.begin()
			, last_iterator()
			, bind(
				&bitwise_nand
				, bind(&result::flags, _1)
				, (unsigned char)result::queried
			)
		);
#ifdef TORRENT_DHT_VERBOSE_LOGGING
		TORRENT_LOG(traversal) << "nodes left (" << this << "): " << (last_iterator() - i);
#endif

		if (i == last_iterator()) break;

		try
		{
			invoke(i->id, i->addr);
			++m_invoke_count;
			i->flags |= result::queried;
		}
		catch (std::exception& e) {}
	}
}