	void MenuControl::initialiseOverride()
	{
		Base::initialiseOverride();

		// инициализируем овнера
		Widget* parent = getParent();
		if (parent)
		{
			mOwner = parent->castType<MenuItem>(false);
			if (!mOwner)
			{
				Widget* client = parent;
				parent = client->getParent();
				if (parent && parent->getClientWidget())
				{
					mOwner = parent->castType<MenuItem>(false);
				}
			}
		}

		// FIXME нам нужен фокус клавы
		setNeedKeyFocus(true);

		///@wskin_child{MenuControl, Widget, Client} Клиентская зона.
		assignWidget(mClient, "Client");
		if (mClient != nullptr)
		{
			setWidgetClient(mClient);
		}

		//OBSOLETE
		if (isUserString("SkinLine"))
		{
			mItemNormalSkin = getUserString("SkinLine");
			mItemPopupSkin = mItemNormalSkin;
		}

		if (isUserString("SeparatorSkin"))
			mItemSeparatorSkin = getUserString("SeparatorSkin");

		if (isUserString("NormalSkin"))
			mItemNormalSkin = getUserString("NormalSkin");

		if (isUserString("PopupSkin"))
			mItemPopupSkin = getUserString("PopupSkin");

		if (isUserString("DistanceButton"))
			mDistanceButton = utility::parseValue<int>(getUserString("DistanceButton"));

		if (isUserString("SubMenuSkin"))
			mSubMenuSkin = getUserString("SubMenuSkin");

		if (isUserString("SubMenuLayer"))
			mSubMenuLayer = getUserString("SubMenuLayer");

		// FIXME добавленно, так как шетдаун вызывается и при смене скина
		mShutdown = false;
	}