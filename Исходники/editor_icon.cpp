	void refreshIcon(const ComponentUID& cmp)
	{
		destroyIcon(cmp.entity);
		createIcon(cmp.entity);
	}