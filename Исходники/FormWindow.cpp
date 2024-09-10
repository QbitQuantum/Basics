void
FormWindow::CreateDefButton(CtrlDef& def)
{
	Button* ctrl = CreateButton(def.GetText(),
	def.GetX(),
	def.GetY(),
	def.GetW(),
	def.GetH(),
	def.GetID(),
	def.GetParentID());

	if (def.GetStandardImage().length()) {
		DataLoader* loader = DataLoader::GetLoader();
		loader->SetDataPath("Screens/");

		Bitmap* bmp = 0;
		loader->LoadTexture(def.GetStandardImage(), bmp);
		ctrl->SetStandardImage(bmp);

		if (def.GetActivatedImage().length()) {
			loader->LoadTexture(def.GetActivatedImage(), bmp);
			ctrl->SetActivatedImage(bmp);
		}

		if (def.GetTransitionImage().length()) {
			loader->LoadTexture(def.GetTransitionImage(), bmp);
			ctrl->SetTransitionImage(bmp);
		}

		loader->SetDataPath("");
	}

	ctrl->SetAltText(def.GetAltText());
	ctrl->SetEnabled(def.IsEnabled());
	ctrl->SetBackColor(def.GetBackColor());
	ctrl->SetForeColor(def.GetForeColor());
	ctrl->SetTextAlign(def.GetTextAlign());
	ctrl->SetSingleLine(def.GetSingleLine());

	ctrl->SetBevelWidth(def.GetBevelWidth());
	ctrl->SetDropShadow(def.GetDropShadow());
	ctrl->SetSticky(def.GetSticky());
	ctrl->SetTransparent(def.GetTransparent());
	ctrl->SetHidePartial(def.GetHidePartial());
	ctrl->SetPictureLocation(def.GetPictureLocation());

	ctrl->SetMargins(def.GetMargins());
	ctrl->SetTextInsets(def.GetTextInsets());
	ctrl->SetCellInsets(def.GetCellInsets());
	ctrl->SetCells(def.GetCells());
	ctrl->SetFixedWidth(def.GetFixedWidth());
	ctrl->SetFixedHeight(def.GetFixedHeight());

	if (def.GetPicture().length() > 0) {
		Bitmap pict;
		int    type = def.GetPictureType();

		DataLoader* loader = DataLoader::GetLoader();
		loader->SetDataPath("Screens/");
		loader->LoadBitmap(def.GetPicture(), pict, type);
		loader->SetDataPath("");

		ctrl->SetPicture(pict);
	}

	Font* f = FontMgr::Find(def.GetFont());
	if (f) ctrl->SetFont(f);
}