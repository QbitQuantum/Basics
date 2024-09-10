void StaticTextScreen::LoadResources()
{
	Font::SetDPI(160);

	Font *fnt;
	fnt = FTFont::Create(FilePath("~res:/Fonts/yikes.ttf"));
//	fnt = GraphicsFont::Create("~res:/Fonts/korinna.def", "~res:/Gfx/Fonts2/korinna");
	fnt->SetSize(7.5f);
//	fnt->SetSize(12);
//	fnt->SetVerticalSpacing(-1);
//	fnt->SetColor(.82f, .81f, 0.73f, 1.0f);
	float32 sizeX = 50;
	float32 sizeY = 80;

    
	UIControl *tc = new UIControl(Rect(0, 0, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	UIStaticText *tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
//	tx->SetMultiline(true);
//	tx->SetAlign(ALIGN_LEFT|ALIGN_TOP);
	tx->SetText(L"Management");
//	tx->SetText(L"This text is aligned by the Left and Top borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect((size.x - sizeX)/2, 0, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_HCENTER|ALIGN_TOP);
//	tx->SetText(L"abab.");
	tx->SetText(L"This text is aligned byyyi the Center and Top borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect(size.x - sizeX, 0, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_RIGHT|ALIGN_TOP);
//	tx->SetText(L"apap.");
	tx->SetText(L"This text is aligned by the Right and Top borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);

	
	
	tc = new UIControl(Rect(0, (size.y - sizeY)/2, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_LEFT|ALIGN_VCENTER);
//	tx->SetText(L"apap.");
	tx->SetText(L"This text is aligned by the Left and Center borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect((size.x - sizeX)/2, (size.y - sizeY)/2, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_HCENTER|ALIGN_VCENTER);
//	tx->SetText(L"abpbs");
	tx->SetText(L"This text is aligned by the Center and Center borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect(size.x - sizeX, (size.y - sizeY)/2, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_RIGHT|ALIGN_VCENTER);
//	tx->SetText(L"aaaa.");
	tx->SetText(L"This text is aligned by the Right and Center borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);

	
	tc = new UIControl(Rect(0, size.y - sizeY, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_LEFT|ALIGN_BOTTOM);
	tx->SetText(L"This text is aligned by the Left and Bottom borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect((size.x - sizeX)/2, size.y - sizeY, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_HCENTER|ALIGN_BOTTOM);
	tx->SetText(L"This text is aligned by the Center and Bottom borders.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	tc = new UIControl(Rect(size.x - sizeX, size.y - sizeY, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_RIGHT|ALIGN_BOTTOM);
	tx->SetText(L"No desc elems.uj");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);
	
	
	
	tc = new UIControl(Rect((size.x - sizeX)/2, (size.y - sizeY)/2 - 70, sizeX, sizeY));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	//tc->GetBackground()->color = Color(0,0,0.4f,1.0f);
	tx = new UIStaticText(Rect(0, 0, sizeX, sizeY));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_HJUSTIFY|ALIGN_TOP);
	tx->SetText(L"This text is Justify and it's looks little better than the others. aja. AVA.");
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);


	//fnt->SetColor(1.0f, 0.3f, 0.3f, 1.0f);
	fnt->SetVerticalSpacing(5);
	tc = new UIControl(Rect(100, 100, 600, 400));
	tc->SetSpriteDrawType(UIControlBackground::DRAW_FILL);
	tc->GetBackground()->color = Color(0.5f,0.5,0.5f,1.0f);
	tx = new UIStaticText(Rect(10, 10, 400, 200));
	tx->SetFont(fnt);
	tx->SetMultiline(true);
	tx->SetAlign(ALIGN_HJUSTIFY|ALIGN_TOP);
	tx->SetText(L"Test test shadow, shadow test ABCDEFGHJIKLMNOPQRSTUVWXYZ\nTest test shadow, shadow test ABCDEFGHJIKLMNOPQRSTUVWXYZ\nTest test shadow, shadow test ABCDEFGHJIKLMNOPQRSTUVWXYZ");
	tx->SetTextColor(Color(0.0f, 1.0f, 0.0f, 1.0f));
	tx->SetShadowColor(Color(0.0f, 0.0f, 0.0f, 0.25f));
	tx->SetShadowOffset(Vector2(2.0f, 2.0f));
	tc->AddControl(tx);
	AddControl(tc);
	SafeRelease(tc);
	SafeRelease(tx);

	
	SafeRelease(fnt);
}