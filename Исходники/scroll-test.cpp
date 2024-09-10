TView::TView(ERect frame, const char *name, euint32 resizingMode, euint32 flags)
	: EView(frame, name, resizingMode, flags)
{
	SetViewColor(216, 216, 216);

#if TEST_SCROLLBAR
	ERect cR = Bounds();
	ERect hR = Bounds();
	ERect vR = Bounds();

	cR.right -= 11;
	cR.bottom -= 11;

	hR.top = hR.bottom - 10;
	hR.right -= 10;
	vR.left = vR.right - 10;
	vR.bottom -= 10;

	EBox *box = new EBox(cR, NULL, E_FOLLOW_ALL);
	box->SetLabelAlignment(E_ALIGN_CENTER);
	box->SetLabel("装饰框框");
	AddChild(box);
#else
	EBox *box = new EBox(Bounds().InsetByCopy(-150, -150).OffsetToCopy(0, 0), NULL, E_FOLLOW_NONE);
	box->SetLabelAlignment(E_ALIGN_CENTER);
	box->SetLabel("装饰框框");
#endif

	ETextControl *edt = new ETextControl(ERect(10, 100, 250, 130), NULL,
					     "主题：", "这个世界日新月异", NULL,
					     E_FOLLOW_NONE, E_WILL_DRAW | E_FRAME_EVENTS | E_NAVIGABLE);
	edt->SetDivider(100);
	edt->SetAlignment(E_ALIGN_RIGHT, E_ALIGN_CENTER);
//	edt->HideTyping(true);
//	edt->HideTyping('*');
	edt->ResizeToPreferred();
	box->AddChild(edt);

	EButton *btn = new EButton(ERect(10, 280, 50, 300), NULL, "按钮", NULL);
	btn->SetFontSize(20);
	box->AddChild(btn);
	btn->ResizeToPreferred();

#if TEST_CHECKBOX
	ECheckBox *cbox = new ECheckBox(ERect(280, 60, 380, 90), NULL, "检查按钮", NULL);
	box->AddChild(cbox);
#endif

#if TEST_RADIOBUTTON
	EView *rbtns_group = new EView(ERect(430, 60, 530, 150), NULL, E_FOLLOW_NONE, 0);
	rbtns_group->AddChild(new ERadioButton(ERect(0, 0, 100, 30), NULL, "组合按钮1", NULL));
	rbtns_group->AddChild(new ERadioButton(ERect(0, 30, 100, 60), NULL, "组合按钮2", NULL));
	rbtns_group->AddChild(new ERadioButton(ERect(0, 60, 100, 90), NULL, "组合按钮3", NULL));
	box->AddChild(rbtns_group);
#endif

#if TEST_LISTVIEW
	EListView *listView = new EListView(ERect(0, 0, 200, 300), NULL, E_MULTIPLE_SELECTION_LIST, E_FOLLOW_NONE);
	listView->AddItem(new EStringItem("Item1"));
	listView->AddItem(new EStringItem("Item2", 1));
	listView->AddItem(new EStringItem("Item3"));
	listView->AddItem(new EStringItem("Item4", 2));
	listView->AddItem(new EStringItem("Item5"));
	listView->AddItem(new EStringItem("Item6"));
	listView->AddItem(new EStringItem("Item7"));
	listView->AddItem(new EStringItem("Item8"));
	listView->AddItem(new EStringItem("Item9"));
	listView->AddItem(new EStringItem("Item10"));
	listView->AddItem(new EStringItem("Item11"));
	listView->AddItem(new EStringItem("Item12"));
	listView->AddItem(new EStringItem("Item13"));
	box->AddChild(new EScrollView(ERect(100, 180, 250, 280), NULL, listView, E_FOLLOW_NONE));


	EOutlineListView *outline = new EOutlineListView(ERect(0, 0, 400, 300), NULL, E_SINGLE_SELECTION_LIST, E_FOLLOW_NONE);
	EListItem *region, *state, *locality;
	outline->AddItem(region = new EStringItem("United States of America"));
	outline->AddUnder(state = new EStringItem("California"), region);
	outline->AddUnder(new EStringItem("Menlo Park"), state);
	outline->AddUnder(new EStringItem("Los Angeles"), state);
	outline->AddUnder(locality = new EStringItem("New York"), region);
	outline->AddUnder(new EStringItem("Albany"), locality);
	outline->AddUnder(new EStringItem("Buffalo"), locality);
	outline->AddUnder(new EStringItem("New York City"), locality);
	outline->AddItem(region = new EStringItem("Europe"));
	outline->AddUnder(locality = new EStringItem("France"), region);
	outline->AddUnder(new EStringItem("Paris"), locality);
	outline->AddUnder(locality = new EStringItem("Germany"), region);
	outline->AddUnder(new EStringItem("Berlin"), locality);
	outline->AddUnder(new EStringItem("Hamburg"), locality);
	outline->AddUnder(locality = new EStringItem("Italy"), region);
	outline->AddUnder(new EStringItem("Milan"), locality);
	outline->AddUnder(new EStringItem("Rome"), locality);
	box->AddChild(new EScrollView(ERect(100, 300, 350, 450), NULL, outline, E_FOLLOW_NONE));
#endif


#if TEST_TEXTVIEW
	e_text_run_array array;
	array.count = 1;
	array.runs[0].font = *etk_plain_font;

	ETextView *textView = new ETextView(ERect(0, 0, 450, 200), NULL, ERect(0, 0, 450, 200));
//	textView->HideTyping(true);
//	textView->HideTyping('*');
	textView->SetAutoindent(true);

	array.runs[0].offset = 16;
	array.runs[0].font.SetSize(16);
	array.runs[0].color.set_to(0, 0, 200, 255);
	array.runs[0].background.set_to(255, 255, 0, 255);
	array.runs[0].underline = false;
	textView->Insert("This is a test, Be", &array);

	array.runs[0].offset = 0;
	array.runs[0].color.set_to(200, 0, 0, 255);
	textView->Insert(-1, "OS", -1, &array);

	array.runs[0].offset = 0;
	array.runs[0].font.SetSize(12);
	array.runs[0].color.set_to(200, 0, 200, 255);
	array.runs[0].background.alpha = 0;
	textView->Insert(-1, " style TextView, just enjoy it. :)\n", -1, &array);

	array.runs[0].offset = 0;
	array.runs[0].font = *etk_bold_font;
	array.runs[0].font.SetSize(20);
	array.runs[0].color.set_to(200, 0, 0, 255);
	array.runs[0].underline = true;
	textView->Insert(-1, "多行", -1, &array);

	array.runs[0].offset = 0;
	array.runs[0].font.SetSize(16);
	array.runs[0].color.set_to(0, 50, 0, 255);
	array.runs[0].underline = true;
	textView->Insert(-1, "文本", -1, &array);

	array.runs[0].offset = 0;
	array.runs[0].font.SetSize(30);
	array.runs[0].color.set_to(0, 0, 200, 255);
	array.runs[0].underline = false;
	textView->Insert(-1, "编辑", -1, &array);

	array.runs[0].offset = 0;
	array.runs[0].font = *etk_plain_font;
	array.runs[0].font.SetSize(10);
	array.runs[0].color.set_to(0, 0, 0, 255);
	textView->Insert(-1, "测试...", -1, &array);

	textView->Select(5, 20, true);

	box->AddChild(new EScrollView(ERect(100, 500, 350, 650), NULL, textView, E_FOLLOW_NONE));
#endif


#if TEST_TABVIEW
	ETabView *tabView = new ETabView(ERect(360, 300, 700, 500), NULL, E_WIDTH_FROM_LABEL, E_FOLLOW_NONE);
	ERect tabVR = tabView->ContainerView()->Bounds();

	ETab *tab = new ETab(new EStringView(tabVR, NULL, "Hello, This is the TAB 1.\nShow it...", E_FOLLOW_ALL));
	tab->SetLabel("Tab 1");
	tabView->AddTab(NULL, tab);

	tab = new ETab(new EColorControl(EPoint(5, 5), NULL, NULL, true));
	tab->SetLabel(">> ColorControl <<");
	tabView->AddTab(NULL, tab);

	tab = new ETab(new EStringView(tabVR, NULL, "Hello, This is the ** TAB 3 **.\nShow it...", E_FOLLOW_ALL));
	tab->SetLabel("  Tab 3  ");
	tabView->AddTab(NULL, tab);

	box->AddChild(tabView);
#endif

#if TEST_SCROLLBAR
	EScrollBar *hScrollBar = new EScrollBar(hR, NULL, 0, -100, 100, E_HORIZONTAL);
	EScrollBar *vScrollBar = new EScrollBar(vR, NULL, 0, -100, 100, E_VERTICAL);
	AddChild(hScrollBar);
	AddChild(vScrollBar);

	hScrollBar->SetTarget(box);
	vScrollBar->SetTarget(box);
#else
	EScrollView *scv = new EScrollView(Bounds(), NULL, box, E_FOLLOW_ALL);
	AddChild(scv);
#endif

#if TEST_STATUSBAR
	fStatusBar = new EStatusBar(ERect(280, 250, 500, 290), NULL, "进度条示例:", "/100");
	box->AddChild(fStatusBar);
	SetFlags(Flags() | E_PULSE_NEEDED);
#endif

#if TEST_MENUFIELD
	EMenu *menu = new EMenu("Options", E_ITEMS_IN_COLUMN);
	menu->SetLabelFromMarked(true);

	menu->AddItem(new EMenuItem("First Item", NULL));
	menu->AddSeparatorItem();
	menu->AddItem(new EMenuItem("Item", NULL));
	menu->AddItem(new EMenuItem("Item Item", NULL));
	menu->AddItem(new EMenuItem("Item Item Item", NULL));
	menu->AddItem(new EMenuItem("Item Item Item Item", NULL));
	menu->AddSeparatorItem();
	menu->AddItem(new EMenuItem("Last Item", NULL));
	menu->ItemAt(0)->SetMarked(true);

	EMenuField *menuField = new EMenuField(ERect(280, 150, 500, 200), NULL, "候选框:", menu, true);
	box->AddChild(menuField);
#endif
}