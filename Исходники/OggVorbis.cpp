//--------------------------------------------------------------------------------------------
//	チャンクがOggかどうかを調べる
//--------------------------------------------------------------------------------------------
bool ovIsOgg(const std::string& filename)
{
	FILE* fp = NULL;
	char c[3];

	fopen_s(&fp, filename.c_str(), "rb");
	if(fp == NULL) return false;
	fread_s(c, sizeof(c), 3, 1, fp);
	fclose(fp);

	return  (c[0] == 'O') &&
			(c[1] == 'g') &&
			(c[2] == 'g');
}