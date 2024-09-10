void wc(wc_info& wci) {

	char mbc[2];
	bool lead_byte = false;

	char* p = (char*)wci.m_p;

	for (size_t i = 0; i < wci.m_size; i++) {

		if (!lead_byte) {
			if (_ismbblead(p[i])) {
				// 2バイトコードの可能性があるので、フラグを立てて保留
				mbc[0] = p[i];
				lead_byte = true;
			} else {
				// 1バイトコードなので、カウント+1
				++wci.m_count_byte;
				++wci.m_count_char;
			}
		} else {
			if (_ismbbtrail(p[i])) {
				// 2バイトコード確定。フラグを落としてカウントアップ
				mbc[1] = p[i];
				lead_byte = false;
				wci.m_count_byte += 2;
				++wci.m_count_char;
			} else {
				// 異常な文字。カウントせずにフラグだけ戻す
				lead_byte = false;
			}
		}
	}
}