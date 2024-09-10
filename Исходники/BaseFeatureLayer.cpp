bool BaseFeatureLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());

	TextureButton* returnButton = NodeFactory::Instance().CreateTextureButton("Close.png", "CloseSelected.png");
	returnButton->OnTap += Bind(&BaseFeatureLayer::OnReturn,this);
	returnButton->SetDock(DockPoint::LeftTop);
	returnButton->SetAnchor(0.f, 1.f);
	AddChild(returnButton);

	TextureButton* refreshButton = NodeFactory::Instance().CreateTextureButton("Refresh.png", "RefreshSelected.png");
	refreshButton->OnTap += Bind(&BaseFeatureLayer::OnRefresh, this);
	refreshButton->SetDock(DockPoint::MiddleBottom);
	refreshButton->SetAnchor(0.5f, 0.f);
	AddChild(refreshButton);


	float xPadding = refreshButton->Size().Width*0.5f + 100.f;

	TextureButton* leftButton = NodeFactory::Instance().CreateTextureButton("Left.png", "LeftSelected.png");
	leftButton->OnTap += Bind(&BaseFeatureLayer::OnLeft, this);
	leftButton->SetDock(DockPoint::MiddleBottom);
	leftButton->SetAnchor(0.5f, 0.f);
	leftButton->SetRelativePosition(Point2F(-xPadding, 0.f));
	AddChild(leftButton);


	TextureButton* rightButton = NodeFactory::Instance().CreateTextureButton("Left.png", "LeftSelected.png");
	rightButton->OnTap += Bind(&BaseFeatureLayer::OnRight, this);
	rightButton->SetDock(DockPoint::MiddleBottom);
	rightButton->SetAnchor(0.5f, 0.f);
	rightButton->SetRelativePosition(Point2F(xPadding, 0.f));
	rightButton->SetFlipX(true);
	AddChild(rightButton);


	return true;
}