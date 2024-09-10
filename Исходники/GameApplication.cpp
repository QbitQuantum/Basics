void GameApplication::CreateUI()
{
	Input* input = GetSubsystem<Input>();
	input->SetMouseVisible(true);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();
    
    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will point the raycast target
    XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(style);
    ui->SetCursor(cursor);
    // Set starting position of the cursor at the rendering window center
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth() / 2, graphics->GetHeight() / 2);
    
    // Construct new Text object, set string to display and font to use
    scoreText = ui->GetRoot()->CreateChild<Text>();
    scoreText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    scoreText->SetTextAlignment(HA_CENTER);
	scoreText->SetColor(Color::BLUE);
	scoreText->SetTextEffect(TextEffect::TE_SHADOW);
    // Position the text relative to the screen center
    scoreText->SetHorizontalAlignment(HA_CENTER);
    scoreText->SetVerticalAlignment(VA_CENTER);
    scoreText->SetPosition(0, ui->GetRoot()->GetHeight() / 4 + 80);

	//开始按钮
	//UIButton* btnStart = new UIButton(context_);
	//btnStart->SetPosition(100,100);
	//btnStart->SetSize(120,50);

	//ui->GetRoot()->AddChild(btnStart);

	Button* btnStart = CreateButton(80,100,120,50,"Start");// ui->GetRoot()->CreateChild<Button>();
	btnStart->SetName("btnStart");
	btnStart->SetMinHeight(24);
	btnStart->SetStyleAuto();
	btnStart->SetPosition(100,100);
	btnStart->SetSize(120,50);

	Text* buttonText = btnStart->CreateChild<Text>();
	buttonText->SetAlignment(HA_CENTER, VA_CENTER);
	buttonText->SetColor(Color::BLUE);
	Font* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
	buttonText->SetFont(font, 12);
	buttonText->SetText("Start");

	SubscribeToEvent(btnStart,E_PRESSED,HANDLER(GameApplication,OnButtonStartClick));

	UpdateScore();
}