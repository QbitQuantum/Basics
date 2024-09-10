/*************************************************
            ITU0同期割り込み関数
--------------------------------------------------
* H8外部クロック25MHz
* 100Hzで割り込み発生
*
**************************************************/
void INT_IMIA1(void)
{
	unsigned char i;
	
	//生存信号
	if(itu1_cnt % ALV_PERIOD == 0)	SetFlags(flag_alive);
	
	// AD変換,マルチプレクサスイッチング
//	if((itu1_cnt % DIV_AD) % DIV_MPX == 0 && (itu1_cnt % DIV_AD) <=35){	// DIV_AD/10 * 7

	if((itu1_cnt % DIV_AD) % DIV_MPX == 0 && (itu1_cnt % DIV_AD) <=70){	// DIV_AD/10 * 7
		SetFlags(flag_ad);
	}
	
	// AD変換結果表示
	if(itu1_cnt % DIV_AD == 0)	SetFlags(flag_dispAD);
	
	//コマンド実行
	if(itu1_cnt % DIV_EXE == 0)	SetFlags(flag_exe);
	
	//渦電流検知テレメトリ
	if(itu1_cnt % DIV_OVERAMPARE == 0)	SetFlags(flag_overa);
	
	// 粗テレメトリ
	if(itu1_cnt % DIV_ROUGHTELEME == 0)	SetFlags(flag_rteleme);
	
	// 詳細テレメトリ
	if(itu1_cnt % DIV_DETAILEDTELEME == 0)	SetFlags(flag_dteleme);
	
	// APIテレメトリ
	if(itu1_cnt % DIV_APITELEME == 0)	SetFlags(flag_ateleme);
	
	// 初期化情報テレメトリ
	if(itu1_cnt % DIV_ITELEME == 0)	SetFlags(flag_iteleme);
	
	// パワーテレメトリ
	if(itu1_cnt % DIV_PTELEME == 0)	SetFlags(flag_pwrt);
	
	// ミッションテレメトリ
	if(itu1_cnt % DIV_MTELEME == 0) SetFlags(flag_misst);
	
	// シリアル通信メッセージチェック
	if(itu1_cnt % DIV_MESSAGE == 0)	SetFlags(flag_scirx);
	
	// RXチェック
	if(itu1_cnt % DIV_RX == 0)	SetFlags(flag_rx);
	
	// TXチェック
	if(itu1_cnt % DIV_TX == 0)	SetFlags(flag_tx);
	
	//パワーから返事が返って来ているかの確認
	if(itu1_cnt % DIV_CPR == 0)  SetFlags(flag_cpr);
	
	// 試験用テレメトリ出力
	if(itu1_cnt % DIV_OUTPUTTELEME == 0) SetFlags(flag_oteleme);
	
	//ミッションCPU起動(タイマ予約型、タイマ予約&作動時間指定型)
	if((smr_time>0)&&(itu1_cnt > smr_time)){
		SetFlags(flag_smr);
	}
	//ミッションCPUシャットダウン(タイマ予約&作動時間指定型)
	if((sms_time>0)&&(itu1_cnt > sms_time)){
		SetFlags(flag_sms);
	}
	//PICオン要求
	if(itu1_cnt % DIV_PIC == 0) SetFlags(flag_pic);
	
	/*デバッグ用*/
	mission_cnt=itu1_cnt;
	
	itu1_cnt++;
	
	if(itu1_cnt >= 0xFFFFFFFE)	// 0.001*4294967296(sec) = 500(day)でクリア
	{
		itu1_cnt = 0;
	}
	
	if(CheckFlags(ena_mywdt)){
		my_wdt++;		// main loopでクリア
		if(my_wdt >= OVERFLOW)	RequestMainShutdown();	// 自己リセット要求
	}
	
	status.obctime[3] =  itu1_cnt			& 0x00ff;
	status.obctime[2] = (itu1_cnt >>  8)	& 0x00ff;
	status.obctime[1] = (itu1_cnt >> 16)	& 0x00ff;
	status.obctime[0] = (itu1_cnt >> 24)	& 0x00ff;
	
	ITU.TISRA.BIT.IMFA1 = 0;				// 割り込みステータスフラグクリア
}