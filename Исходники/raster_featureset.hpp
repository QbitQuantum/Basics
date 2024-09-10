    const_iterator query(const Envelope<double>& box)
    {
	if (box.intersects(info_.envelope()))
	{
	    return begin();
	}
	return end();
    }