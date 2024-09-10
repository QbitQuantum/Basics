platycanvasdata::platycanvasdata()
{
	ViewOx = 0;
	ViewOy = 0;
	WacomDown = false;
	ScreenMode = true;
	IsZoomEnabled = false;
	CursorX = 0;
	CursorY = 0;
	CursorD = 0;
	CursorImage.Load("skin/cursor.png", BxImage::PNG, BxImage::PAD5);
	IsZoomScaling = false;
	OldCursorX = 0;
	OldCursorY = 0;
	CreateMin = 50;
	CreateRate = 10;
	CreateCanvasMode = false;
	CreateCanvasBegin = XY(0, 0);
	CreateCanvasEnd = XY(0, 0);
	HandImage.Load("skin/toolbar/button_hand.png", BxImage::PNG, BxImage::PAD5);
	SpoidImage.Load("skin/toolbar/button_spoid.png", BxImage::PNG, BxImage::PAD5);
	HandAnimation = 0;
	SpoidAnimation = 0;

	if(!BxCore::Font::IsExistNick("skin/cartoonstory.ttf"))
		BxCore::Font::NickOpen("skin/cartoonstory.ttf", "skin/cartoonstory.ttf");
	#ifdef ANDROID
		TitleFont = BxCore::Font::Open("skin/cartoonstory.ttf", 30);
	#else
		TitleFont = BxCore::Font::Open("skin/cartoonstory.ttf", 15);
	#endif

    IsOpenedPenTool = true;
    PenToolPosPercent = 100;
	PenDoor.Bind("platycanvas.ToolDoor", "FF7F27", 0);
	PenDoor.Clicked += OnClicked_PenDoor, this;
	PenTool.Bind("platycanvas.ToolBar.Pen", "FF7F27", 0);
	PenTool("Close").Clicked += OnClicked_PenClose, this;

	IsOpenedLayerTool = false;
	LayerToolPosPercent = 0;
	LayerDoor.Bind("platycanvas.ToolDoor", "B5E61D", 90);
	LayerDoor.Clicked += OnClicked_LayerDoor, this;
	LayerTool.Bind("platycanvas.ToolBar.Layer", "B5E61D", 90);
	LayerTool("Close").Clicked += OnClicked_LayerClose, this;

	const byte Thick = 64;
    const byte Opacity = 255;
	const byte Aqua = 0;
	const byte Hue = 128;
	const byte Lightness = 128;
	const byte Saturation = 255;
	const color_x888 RGB = ColorHLSToRGB(Hue, Lightness, Saturation);

	UpdateStroke(StrokeByAqua);
	Command::SetStrokeBy("aqua");
	Command::SetThick(THICK_SIZE * Thick / 255);
	Command::SetColor(Color(ColorToRed(RGB), ColorToGreen(RGB), ColorToBlue(RGB), Opacity, Aqua));

	PenTool("Stroke").Notify("SetThick", Thick);
	PenTool("Stroke").Notify("SetColor", RGB);
	PenTool("Stroke").Notify("SetOpacity", Opacity);
	PenTool("Stroke").Notify("SetAqua", Aqua);
	PenTool("Stroke").Updated += OnUpdated_Stroke, this;

	PenTool("Color").Notify("SetHue", Hue);
	PenTool("Color").Notify("SetLightness", Lightness);
    PenTool("Color").Notify("SetSaturation", Saturation);
    PenTool("Color").Updated += OnUpdated_Color, this;

	PenTool("PenButton").Clicked += OnClicked_PenButton, this;
	PenTool("EraserButton").Clicked += OnClicked_EraserButton, this;
	PenTool("HandButton").Clicked += OnClicked_HandButton, this;
	PenTool("SpoidButton").Clicked += OnClicked_SpoidButton, this;

    BxCore::File::SearchFiles("", platycanvasdata::OnFile, this, nullptr);
}