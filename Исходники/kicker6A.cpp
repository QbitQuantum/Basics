// フラッシュを書き換える
bool clKicker6A::FlashWriteHEX(const std::wstring &file){
	if (m_Mode != MODE_DFU) return false;
	
	char *buf = new char[XMEGA_APP_SIZE];
	char *used = new char[XMEGA_APP_SIZE];
	char *and = new char[XMEGA_APP_PAGES];
	memset(and, 0, XMEGA_APP_PAGES);

	// HEXファイルを読み込む
	bool result;
	result = LoadIntelHEX(file.c_str(), buf, used, XMEGA_APP_SIZE, XMEGA_APP_START);
	if (result == true){
		bool exist = false;

		// 書き換えるページを調べる
		for(int page = 0; page < XMEGA_APP_PAGES; page++){
			char flag = 0;
			char *s = used + XMEGA_PAGE_SIZE * page;
			for(int cnt = 0; cnt < XMEGA_PAGE_SIZE; cnt++){
				flag |= *s++;
			}
			if (flag != 0){
				and[page] = 1;
				exist = true;
			}
		}

		if (exist == true){
			// 転送していく
			result = false;
			
			for(int page = 0; page < XMEGA_APP_PAGES; page++){
				if (and[page] != 0){
					// Write
					char *p = &buf[XMEGA_PAGE_SIZE * page];
					unsigned short page_w = page;
					unsigned int transfered = 0;
					Trace(L"Write(%d) %d bytes", page, XMEGA_PAGE_SIZE);

					// ページをセット
					result = Transmit(CMDID_SET_PAGE, 2, &page_w);
					if (result == false) break;

					// ライト
					result = Transmit(CMDID_WRITE, XMEGA_PAGE_SIZE, p, &transfered);
					if (result == false) break;

					Trace(L"Written %d bytes", transfered);

					Sleep(10);
				}
			}
			
			if (result == true){
				Trace(L"成功しました");
			}else{
				Trace(L"失敗しました");
			}
		}else{
			Trace(L"書き込むデータがありません");
		}
		result = exist;
	}

	delete [] buf;
	delete [] used;
	delete [] and;
	return result;
}