// Fix to avoid black corners temorarily artifact
void Ctrl::Create0(Ctrl::CreateBox *cr)
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("Ctrl::Create(parent = " << (void *)parent << ") in " <<UPP::Name(this) << BeginIndent);
	ASSERT(!IsChild() && !IsOpen());
	Rect r = GetRect();
	AdjustWindowRectEx(r, cr->style, FALSE, cr->exstyle);
	isopen = true;
	top = new Top;
	ASSERT(!cr->parent || IsWindow(cr->parent));
	cr->style &= ~WS_VISIBLE;
	if(!IsWinXP())
		cr->dropshadow = false;
#ifdef PLATFORM_WINCE
		if(parent)
			top->hwnd = CreateWindowExW(cr->exstyle,
			                            cr->savebits ? cr->dropshadow ? L"UPP-CLASS-SB-DS-W" : L"UPP-CLASS-SB-W"
			                                         : cr->dropshadow ? L"UPP-CLASS-DS-W"    : L"UPP-CLASS-W",
			                            L"", cr->style, 0, 0, 0, 0,
			                            cr->parent, NULL, hInstance, this);
		else
			top->hwnd = CreateWindowW(L"UPP-CLASS-W",
			                          L"", WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			                          cr->parent, NULL, hInstance, this);
#else
	if(IsWinNT() && (!cr->parent || IsWindowUnicode(cr->parent)))
		top->hwnd = CreateWindowExW(cr->exstyle,
		                            cr->savebits ? cr->dropshadow ? L"UPP-CLASS-SB-DS-W" : L"UPP-CLASS-SB-W"
		                                         : cr->dropshadow ? L"UPP-CLASS-DS-W"    : L"UPP-CLASS-W",
		                            L"", cr->style, 0, 0, 0, 0,
		                            cr->parent, NULL, hInstance, this);
	else
		top->hwnd = CreateWindowEx(cr->exstyle,
		                           cr->savebits ? cr->dropshadow ? "UPP-CLASS-SB-DS-A" : "UPP-CLASS-SB-A"
		                                        : cr->dropshadow ? "UPP-CLASS-DS-A"    : "UPP-CLASS-A",
		                           "", cr->style, 0, 0, 0, 0,
		                           cr->parent, NULL, hInstance, this);
#endif

	inloop = false;

	ASSERT(top->hwnd);

	::MoveWindow(top->hwnd, r.left, r.top, r.Width(), r.Height(), false); // To avoid "black corners" artifact effect
	::ShowWindow(top->hwnd, visible ? cr->show : SW_HIDE);
//	::UpdateWindow(hwnd);
	StateH(OPEN);
	LLOG(EndIndent << "//Ctrl::Create in " <<UPP::Name(this));
	RegisterDragDrop(top->hwnd, (LPDROPTARGET) (top->dndtgt = NewUDropTarget(this)));
	CancelMode();
	RefreshLayoutDeep();
}