void Talk::draw(void) {
	////////////////////////////////////////
	//キャラクターの画像を表示する。
	////////////////////////////////////////
	char image_id[256];
	memset(image_id, 0x00, sizeof(image_id));
	sprintf(image_id, "TALK_CHARACTER%s", id.c_str());
	Surface *image = Manager<Surface>::getInstance().get(image_id);
	
	if (image!=NULL) image->draw(Vector2<int>(30,500), Vector3<int>(255,255,255), Vector2<float>(0.25f,0.25f), 0.0f, 1.0f);
	
	////////////////////////////////////////
	//改行文字で文字列を分割する。
	////////////////////////////////////////
	//文字を表示する（現在の表示文字数）
	string displayText = text.substr(0, currentCount);
	//２バイト文字の先頭が来ていた場合は除去(表示されないため)
	for (int i = 0; i < currentCount; i++) {
		//２バイト文字の１バイト目かチェック
		if (displayText.size() > 0 &&
			(
				((unsigned char)displayText[displayText.size()-1] >= 0x81  &&
				 (unsigned char)displayText[displayText.size()-1] <= 0x9F) ||
				((unsigned char)displayText[displayText.size()-1] >= 0xE0  &&
				 (unsigned char)displayText[displayText.size()-1] <= 0xFC)
			))
		{
			//２バイト文字の１バイト目で文字列が終了していた。
			if (i == currentCount-1) {
				currentCount++;
				break;
			}
			i++;
		}
	}
	displayText = text.substr(0, currentCount);
	
	Vector4<float> color = Vector4<float>(1.0f, 0.0f, 0.3f, 1.0f);
	Font *font = Manager<Font>::getInstance().get("TalkFont");
	font->setColor(color);

	WCHAR wDrawText[256];
	memset(wDrawText, 0x00, sizeof(wDrawText));
	//swprintf(wDrawText, L"%s", drawText);
	size_t wLen = 0;
	errno_t err = 0;
	//ロケール指定
	setlocale(LC_ALL,"japanese");
	//変換
	err = mbstowcs_s(&wLen, wDrawText, 256, displayText.c_str(), _TRUNCATE);
	font->draw(200, 530, wDrawText);
	
}