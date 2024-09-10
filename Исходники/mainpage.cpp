MainPage::MainPage(Wt::WApplication* app): WContainerWidget()
{
	app_ = app;
	contentsStack_ = new Wt::WStackedWidget();
	contentsStack_->setOverflow(WContainerWidget::OverflowAuto);
	contentsStack_->setStyleClass("contents");

	/*
	* Setup the menu (and submenus)
	*/
	Wt::WMenu *menu = new Wt::WMenu(contentsStack_, Wt::Vertical, 0);
	menu->setRenderAsList(true);
	menu->setStyleClass("menu");
	menu->setInternalPathEnabled();
	menu->setInternalBasePath("/");
	menu->itemSelected().connect(this, &MainPage::selectedMenuItem);
	
	Wt::WContainerWidget *w = new Wt::WContainerWidget(this);
	Wt::WBorderLayout *layout = new Wt::WBorderLayout();
	layout->addWidget(new Wt::WText("North-side is best"), Wt::WBorderLayout::North);
	layout->addWidget(new Wt::WText("South-side is best"), Wt::WBorderLayout::South);
	layout->addWidget(menu, Wt::WBorderLayout::West);
	layout->addWidget(contentsStack_, Wt::WBorderLayout::Center);

	// use layout but do not justify vertically
	w->setLayout(layout, Wt::AlignTop | Wt::AlignJustify);
	
	menu->addItem("Basics", new ClientsPage(this, &session_));
	menu->addItem("Form Widgets", new CommonPage(this, &session_));
	menu->addItem("Form Validators", new CommonPage(this, &session_));

	Wt::WSubMenuItem *smi = new Wt::WSubMenuItem("Sub menu", new CommonPage(this, &session_));
	Wt::WMenu *subMenu = new Wt::WMenu(contentsStack_, Wt::Vertical, 0);
	subMenu->setRenderAsList(true);

	smi->setSubMenu(subMenu);
	
	menu->addItem(smi);

	subMenu->setInternalPathEnabled();
	subMenu->setInternalBasePath("/" + smi->pathComponent());
	subMenu->setStyleClass("menu submenu");
	subMenu->itemSelected().connect(this, &MainPage::selectedMenuItem);
	
	subMenu->addItem("Sub Item 1", new CommonPage(this, &session_));
	subMenu->addItem("Sub Item 2", new CommonPage(this, &session_));
}