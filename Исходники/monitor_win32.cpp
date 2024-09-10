	std::shared_ptr<osd_monitor_info> monitor_from_rect(const osd_rect& rect) override
	{
		if (!m_initialized)
			return nullptr;

		RECT p;
		p.top = rect.top();
		p.left = rect.left();
		p.bottom = rect.bottom();
		p.right = rect.right();

		auto nearest = monitor_from_handle(reinterpret_cast<std::uintptr_t>(MonitorFromRect(&p, MONITOR_DEFAULTTONEAREST)));
		assert(nearest != nullptr);
		return nearest;
	}