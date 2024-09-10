//セルデータの出力
void outputcelldata(void)
{
	FILE *fp;
	wchar_t buf[1024];
	// ファイルのオープン
	fopen_s(&fp, output_filename.c_str(), "w,ccs=UTF-8");
	if (fp == NULL)
	{
		//エラー
		printf("file open error!!\n");
		err = true;
	}
	if (err == false)
	{
		//ロケール指定
		setlocale(LC_ALL, "japanese");

		//ヘッダ出力
		fputws(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"), fp);
		fputws(_T("<root version=\"1.0\">\n"), fp);

		swprintf_s(buf, 1024, _T("  <info w=\"%d\" h=\"%d\" />\n"), tex_size_w, tex_size_h);
		fputws(buf, fp);
		fputws(_T("  <textures>\n"), fp);

		int i;
		for (i = 0; i < cell_count; i++ )
		{
			//変換
			wchar_t	name[50];
			size_t wLen = 0;
			mbstowcs_s(&wLen, name, 20, celldata[i].name.c_str(), _TRUNCATE);

			//セルデータの出力
			if (option_offset == false)
			{
				swprintf_s(buf, 1024, _T("    <texture filename=\"%s\" x=\"%d\" y=\"%d\" w=\"%d\" h=\"%d\" />\n"), name, celldata[i].x, celldata[i].y, celldata[i].w, celldata[i].h);
			}
			else
			{
				swprintf_s(buf, 1024, _T("    <texture filename=\"%s\" x=\"%d\" y=\"%d\" w=\"%d\" h=\"%d\" offset_x=\"%d\" offset_y=\"%d\" />\n"), name, celldata[i].x, celldata[i].y, celldata[i].w, celldata[i].h, celldata[i].offset_x, celldata[i].offset_y);
			}

			fputws(buf, fp);
		}
		//フッダ出力
		fputws(_T("  </textures>\n"), fp);
		fputws(_T("</root>\n"), fp);
		fputws(_T("\n"), fp);

	}
	fclose(fp);	//ファイルのクローズ
}