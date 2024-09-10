/*---------------------------------------------------------------------*//**
	開始
**//*---------------------------------------------------------------------*/
bool TxtEditorMode::notifyBegin(void* objParamRef)
{
	// テクスチャ、フォントを得る
	GameGui* gui = Game::getGame()->getGui();

	// テスト用テキストを読み込む
	VcString strTxt;
	#if defined(_WINDOWS)
	File file(CcString("test_txt.txt"), File::MODE_READ);
	if(file.isOpened())
	{
		file.readString(&strTxt, file.getLength());
	}
	#endif

	#if TEST_DIRECT_TB
		// テキストエディタを作成
		Texture* texGui = gui->getGuiTexture();
		Font* fontJp = gui->getFontSet()->getFont(GameFontSet::JP);
		TxtBox* txteditor = new TxtBox();
		RectF32 rect(0, 0, Game::getGame()->getLogicalWidth(), Game::getGame()->getLogicalHeight());
		if(!txteditor->create(fontJp, 10, texGui, &rect, TxtBox::MODE_SRCEDIT))
		{
			delete txteditor;
			ASSERT(false);
			return false;
		}
		_txtbox = txteditor;
	#else
		// ソースエディタを表示
		SourceEditWindow* wndSrcedt = Game::getGame()->getGui()->getSourceEditWindow();
		wndSrcedt->showWindow(true);
		wndSrcedt->setup(SourceEditWindow::ACTMODE_EDIT, &strTxt);
	#endif

	// 値の初期化
	_dispCnt = 0;

	return true;
}