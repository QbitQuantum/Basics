	CGameObject::~CGameObject()
	{
		//	Note, that here we adding children to parent in reverse order, i think it's not that important for now.
		//	That order is not important at all. Overall comment should be removed.
		while (!Children.empty())
			Children.back()->SetParent(Parent);

		SetParent(NULL);

		if (Created)
		{
			Scene->Remove(this);
			DestroyLuaObject();
		}
	}