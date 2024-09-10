VideoDisplay::VideoDisplay(
	wxToolBar *visualSubToolBar,
	bool freeSize,
	wxComboBox *zoomBox,
	wxWindow* parent,
	agi::Context *c)
: wxGLCanvas(parent, -1, attribList)
, autohideTools(OPT_GET("Tool/Visual/Autohide"))
, con(c)
, zoomValue(OPT_GET("Video/Default Zoom")->GetInt() * .125 + .125)
, toolBar(visualSubToolBar)
, zoomBox(zoomBox)
, freeSize(freeSize)
, retina_helper(agi::util::make_unique<RetinaHelper>(this))
, scale_factor(retina_helper->GetScaleFactor())
, scale_factor_connection(retina_helper->AddScaleFactorListener([=](int new_scale_factor) {
	double new_zoom = zoomValue * new_scale_factor / scale_factor;
	scale_factor = new_scale_factor;
	SetZoom(new_zoom);
}))
{
	zoomBox->SetValue(wxString::Format("%g%%", zoomValue * 100.));
	zoomBox->Bind(wxEVT_COMBOBOX, &VideoDisplay::SetZoomFromBox, this);
	zoomBox->Bind(wxEVT_TEXT_ENTER, &VideoDisplay::SetZoomFromBoxText, this);

	con->videoController->Bind(EVT_FRAME_READY, &VideoDisplay::UploadFrameData, this);
	slots.push_back(con->videoController->AddVideoOpenListener(&VideoDisplay::UpdateSize, this));
	slots.push_back(con->videoController->AddARChangeListener(&VideoDisplay::UpdateSize, this));

	slots.push_back(con->subsController->AddFileSaveListener(&VideoDisplay::OnSubtitlesSave, this));

	Bind(wxEVT_PAINT, std::bind(&VideoDisplay::Render, this));
	Bind(wxEVT_SIZE, &VideoDisplay::OnSizeEvent, this);
	Bind(wxEVT_CONTEXT_MENU, &VideoDisplay::OnContextMenu, this);
	Bind(wxEVT_ENTER_WINDOW, &VideoDisplay::OnMouseEvent, this);
	Bind(wxEVT_CHAR_HOOK, &VideoDisplay::OnKeyDown, this);
	Bind(wxEVT_LEAVE_WINDOW, &VideoDisplay::OnMouseLeave, this);
	Bind(wxEVT_LEFT_DCLICK, &VideoDisplay::OnMouseEvent, this);
	Bind(wxEVT_LEFT_DOWN, &VideoDisplay::OnMouseEvent, this);
	Bind(wxEVT_LEFT_UP, &VideoDisplay::OnMouseEvent, this);
	Bind(wxEVT_MOTION, &VideoDisplay::OnMouseEvent, this);
	Bind(wxEVT_MOUSEWHEEL, &VideoDisplay::OnMouseWheel, this);

	SetCursor(wxNullCursor);

	c->videoDisplay = this;

	if (con->videoController->IsLoaded())
		con->videoController->JumpToFrame(con->videoController->GetFrameN());
}