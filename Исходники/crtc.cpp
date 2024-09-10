//---------------------------------------------------------------------------
//
//	バイト書き込み
//
//---------------------------------------------------------------------------
void FASTCALL CRTC::WriteByte(uint32_t addr, uint32_t data)
{
	int reg;

	ASSERT(this);
	ASSERT((addr >= memdev.first) && (addr <= memdev.last));

	// $800単位でループ
	addr &= 0x7ff;

	// ウェイト
	scheduler->Wait(1);

	// $E80000-$E803FF : レジスタエリア
	if (addr < 0x400) {
		addr &= 0x3f;
		if (addr >= 0x30) {
			return;
		}

		// 書き込み(エンディアンを反転させる)
		addr ^= 1;
		if (crtc.reg[addr] == data) {
			return;
		}
		crtc.reg[addr] = (uint8_t)data;

		// GVRAMアドレス構成
		if (addr == 0x29) {
			if (data & 0x10) {
				crtc.tmem = TRUE;
			}
			else {
				crtc.tmem = FALSE;
			}
			if (data & 0x08) {
				crtc.gmem = TRUE;
			}
			else {
				crtc.gmem = FALSE;
			}
			crtc.siz = (data & 4) >> 2;
			crtc.col = (data & 3);

			// グラフィックVRAMへ通知
			gvram->SetType(data & 0x0f);
			return;
		}

		// 解像度変更
		if ((addr <= 15) || (addr == 40)) {
			// スプライトメモリの接続・切断は瞬時に行う(OS-9/68000)
			if (addr == 0x28) {
				if ((crtc.reg[0x28] & 3) >= 2) {
					sprite->Connect(FALSE);
				}
				else {
					sprite->Connect(TRUE);
				}
			}

			// 次の周期で再計算
			crtc.changed = TRUE;
			return;
		}

		// ラスタ割り込み
		if ((addr == 18) || (addr == 19)) {
			crtc.raster_int = (crtc.reg[19] << 8) + crtc.reg[18];
			crtc.raster_int &= 0x3ff;
			CheckRaster();
			return;
		}

		// テキストスクロール
		if ((addr >= 20) && (addr <= 23)) {
			crtc.text_scrlx = (crtc.reg[21] << 8) + crtc.reg[20];
			crtc.text_scrlx &= 0x3ff;
			crtc.text_scrly = (crtc.reg[23] << 8) + crtc.reg[22];
			crtc.text_scrly &= 0x3ff;
			render->TextScrl(crtc.text_scrlx, crtc.text_scrly);

			CRTC_LOG(LOG2(Log::Normal, "テキストスクロール x=%d y=%d", crtc.text_scrlx, crtc.text_scrly));
			return;
		}

		// グラフィックスクロール
		if ((addr >= 24) && (addr <= 39)) {
			reg = addr & ~3;
			addr -= 24;
			addr >>= 2;
			ASSERT(addr <= 3);
			crtc.grp_scrlx[addr] = (crtc.reg[reg+1] << 8) + crtc.reg[reg+0];
			crtc.grp_scrly[addr] = (crtc.reg[reg+3] << 8) + crtc.reg[reg+2];
			if (addr == 0) {
				crtc.grp_scrlx[addr] &= 0x3ff;
				crtc.grp_scrly[addr] &= 0x3ff;
			}
			else {
				crtc.grp_scrlx[addr] &= 0x1ff;
				crtc.grp_scrly[addr] &= 0x1ff;
			}
			render->GrpScrl(addr, crtc.grp_scrlx[addr], crtc.grp_scrly[addr]);
			return;
		}