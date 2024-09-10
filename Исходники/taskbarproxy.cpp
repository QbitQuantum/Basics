	void TaskbarProxy::showMenu (const QString& widStr, int x, int y)
	{
		auto& w = Util::XWrapper::Instance ();

		const auto& wid = widStr.toULong ();

		const auto state = w.GetWindowState (wid);
		const auto actions = w.GetWindowActions (wid);

		auto menu = new QMenu;
		menu->setAttribute (Qt::WA_DeleteOnClose);

		{
			auto minimizeAct = menu->addAction (tr ("Minimize"));
			minimizeAct->setCheckable (true);
			if (state & Util::WinStateFlag::Hidden)
				minimizeAct->setChecked (true);
			else
				minimizeAct->setEnabled (actions & Util::AllowedActionFlag::Minimize);
			minimizeAct->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this, state] (const QString& wid)
							{
								state & Util::WinStateFlag::Hidden ?
										raiseWindow (wid) :
										minimizeWindow (wid);
							}));
		}

		{
			auto maximizeAct = menu->addAction (tr ("Maximize"));
			maximizeAct->setCheckable (true);
			const bool isMaximized = state & Util::WinStateFlag::MaximizedHorz ||
					state & Util::WinStateFlag::MaximizedVert;
			if (isMaximized)
				maximizeAct->setChecked (true);
			else
				maximizeAct->setEnabled (actions & Util::AllowedActionFlag::MaximizeHorz ||
						actions & Util::AllowedActionFlag::MaximizeVert);
			maximizeAct->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this, isMaximized] (const QString& wid)
							{
								isMaximized ? unmaximizeWindow (wid) : maximizeWindow (wid);
							}));
		}

		auto moreMenu = menu->addMenu (tr ("More"));

		{
			auto keepAbove = moreMenu->addAction (tr ("Keep above others"));
			keepAbove->setEnabled (actions & Util::AllowedActionFlag::MoveToTop);
			keepAbove->setCheckable (true);
			const bool isTop = state & Util::WinStateFlag::OnTop;
			keepAbove->setChecked (isTop);
			keepAbove->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this, isTop] (const QString& wid)
							{ moveWindowTo (wid, isTop ? "normal" : "top"); }));
			keepAbove->setIcon (Proxy_->GetIconThemeManager ()->GetIcon ("go-top"));
		}

		{
			auto keepBelow = moreMenu->addAction (tr ("Keep below others"));
			keepBelow->setEnabled (actions & Util::AllowedActionFlag::MoveToBottom);
			keepBelow->setCheckable (true);
			const bool isBottom = state & Util::WinStateFlag::OnBottom;
			keepBelow->setChecked (isBottom);
			keepBelow->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this, isBottom] (const QString& wid)
							{ moveWindowTo (wid, isBottom ? "normal" : "bottom"); }));
			keepBelow->setIcon (Proxy_->GetIconThemeManager ()->GetIcon ("go-bottom"));
		}

		{
			auto shadeAct = moreMenu->addAction (tr ("Shade"));
			shadeAct->setEnabled (actions & Util::AllowedActionFlag::Shade);
			shadeAct->setCheckable (true);
			shadeAct->setChecked (state & Util::WinStateFlag::Shaded);
			shadeAct->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this] (const QString& wid)
							{ toggleShadeWindow (wid); }));
		}

		QMenu *desksMenu = 0;

		{
			const auto numDesks = w.GetDesktopCount ();
			if (numDesks > 1)
			{
				desksMenu = menu->addMenu (tr ("Move to desktop"));

				const auto winDesk = w.GetWindowDesktop (wid);

				auto addAct = [this, actions, winDesk, desksMenu] (int num, const QString& name)
				{
					auto act = desksMenu->addAction (name);
					act->setEnabled (actions & Util::AllowedActionFlag::ChangeDesktop);
					act->setCheckable (true);
					act->setChecked (winDesk == num);
					act->setProperty ("Actor",
							QVariant::fromValue<Actor_f> ([this, num] (const QString& wid)
									{ moveToDesktop (wid, num); }));
				};

				const auto& deskNames = w.GetDesktopNames ();
				for (int i = 0; i < numDesks; ++i)
					addAct (i, deskNames.value (i, QString::number (i)));

				desksMenu->addSeparator ();

				addAct (0xFFFFFFFF, tr ("All desktops"));
			}
		}

		menu->addSeparator ();

		{
			auto closeAct = menu->addAction (tr ("Close"));
			closeAct->setEnabled (actions & Util::AllowedActionFlag::Close);
			closeAct->setProperty ("Actor",
					QVariant::fromValue<Actor_f> ([this] (const QString& wid)
							{ closeWindow (wid); }));
			closeAct->setIcon (Proxy_->GetIconThemeManager ()->GetIcon ("window-close"));
		}

		auto allActions = menu->actions () + moreMenu->actions ();
		if (desksMenu)
			allActions += desksMenu->actions ();
		for (auto act : allActions)
		{
			act->setProperty ("WID", widStr);
			connect (act,
					SIGNAL (triggered ()),
					this,
					SLOT (handleAction ()));
		}

		menu->popup ({ x, y });
	}