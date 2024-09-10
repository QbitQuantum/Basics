void OperaMenuDialog::OnInit()
{ 
	int i;

	//don't save position, the dialog will be aligned automatically
	SetSavePlacementOnClose(FALSE);	

	// Listen to parent desktop window to get notified about movements
	if (GetParentDesktopWindow() && GetParentDesktopWindow()->GetParentDesktopWindow())
			GetParentDesktopWindow()->GetParentDesktopWindow()->AddListener(this);

	m_tabs =  static_cast<OpTabs *> (GetWidgetByType(WIDGET_TYPE_TABS));
	m_tabs->SetButtonStyle(OpButton::STYLE_IMAGE);
	m_tabs->SetXResizeEffect(RESIZE_FIXED);
	m_tabs->SetYResizeEffect(RESIZE_SIZE);

	OpWidget *w = (OpWidget*) m_tabs->childs.First();
	while (w)
	{
		w->SetListener(this);
		OpInputAction *action = OP_NEW(OpInputAction, (OpInputAction::ACTION_SHOW_MENU_SECTION));
		if (w->GetType() == WIDGET_TYPE_BUTTON)
			((OpButton*)w)->SetAction(action);
		w = (OpWidget*) w->Suc();
	}

	// Basic layout and initialization
	for(i = 0; i < (int)GetPageCount(); i++)
	{
		OpWidget *page = GetPageByNumber(i);
		OpWidget *w = page->GetFirstChild();
		int y = 0, row_add = 0;
		while (w)
		{
			if (w->GetType() == WIDGET_TYPE_BUTTON)
			{
				OpButton *b = static_cast<OpButton*> (w);
				b->SetButtonStyle(OpButton::STYLE_IMAGE_AND_TEXT_ON_RIGHT);
				b->SetButtonType(OpButton::TYPE_OMENU);
				b->SetFixedImage(FALSE);
				if (b->GetBounds().width >= 300)
					b->SetShowShortcut(TRUE);
			}
			// test of some really basic vertical layout so we don't have to do that by hand in ini.
			/*if (page->GetName().Compare("Menu Page") == 0 ||
				page->GetName().Compare("Menu Tools") == 0 ||
				page->GetName().Compare("Menu Closed Tabs") == 0)*/
			{
				int x = w->GetRect().x;
				int height = w->GetRect().height;

				if (x == 0)
					y += row_add;

				w->SetRect(OpRect(x, y, w->GetRect().width, height));
				w->SetOriginalRect(w->GetRect());
				row_add = height;
			}
			w = (OpWidget *) w->Suc();
		}
	}

	if (OpSlider *slider = static_cast<OpSlider*> (GetWidgetByName("zoom_slider")))
	{
		int zoom = 100;
		slider->SetMin(20);
		slider->SetMax(300);
		slider->SetValue(zoom);
		slider->SetStep(10);
		slider->ShowTickLabels(TRUE);

		OpSlider::TICK_VALUE tick_values[5] = {	{20, FALSE },
												{50, FALSE },
												{100, TRUE },
												{200, TRUE },
												{300, FALSE } };
		slider->SetTickValues(5, tick_values, 10);
	}

	// Create window animation for slider fade
	m_window_animation = OP_NEW(QuickAnimationWindowObject, ());
	if (!m_window_animation || OpStatus::IsError(m_window_animation->Init(this, NULL)))
	{
		OP_DELETE(m_window_animation);
		m_window_animation = NULL;
	}
}