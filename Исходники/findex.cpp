	void set(CWindow& wnd, CWindow& owner)
	{
		wnd.GetWindowRect(this);
		owner.ScreenToClient(this);
	}