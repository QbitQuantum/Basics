void FontManager::DrawCenter(FontSet font, int x, int y, char *string, int color)
{
	// fontをまだ作っていなかった場合ロードする
	if( m_FontData[font].handle == 0)
	{
		Load(font);
	}
	char buffer[256];
	int count = 0;				// 現在保存中の文字数
	int length = 0;				// 文字列の横ピクセル
	// 終端文字までループ
	while(string[count] != '\0')
	{
		char c = string[count];
		// ２バイト文字なら
		//if((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		if( _mbclen((BYTE*)&string[count]) == 2)
		{
			buffer[count] = c;
			buffer[count + 1] = string[count + 1];
			count += 2;
			length += m_FontData[font].stringWidth;
		}
		else
		{
			buffer[count] = c;
			count++;
			length += m_FontData[font].halfStringWidth;
		}
	}
	buffer[count] = '\0';
	DrawStringToHandle(x - length / 2, y, buffer, color, m_FontData[font].handle);
}