	int sample()
	{
		return (std::lower_bound(cumulative.begin(), cumulative.end(), disc_dist_ptr->operator()()) - cumulative.begin());
	}