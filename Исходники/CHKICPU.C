/************************************************************************
	module		:[システムイニシャルメイン処理]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC(V.3.0C)]
	keyword		:[INI]
	date		:[1997/05/10]
	author		:[野瀬敏弘]
************************************************************************/
void InitializeSystemProcess(void)
{
	UBYTE *start_address;
	UBYTE *end_address;
#if (PRO_EXT_DMAC == ENABLE)	/* 一時的に入れる */
	UBYTE dbg_sw;
#endif
	UWORD command;
	
	/*--------------------------------------------------------------*/
	/* ＣＳ０を２ウェイトに設定し直します。                         */
	/* 内蔵ＲＯＭ内でのＣＳ０設定は、遅いフラッシュを使うことがある */
	/* かもしれないので３ウェイト設定にしておきます。               */
	/* T.Nose 1997/09/05                                            */
	/* ・ＣＳ３空間は３ウェイト設定                                 */
	/* ・ＣＳ２空間はノーウェイト設定                               */
	/* ・ＣＳ１空間は２ウェイト設定 <-３ 1997/08/27                 */
	/* ・ＣＳ０空間は２ウェイト設定 <-３ 1997/09/05                 */
	/* 特殊テストパターンプリントの時はＣＳ０空間５ウェイト T.Nose  */
	/*--------------------------------------------------------------*/
#if !defined(POPLAR_H)
	if (CheckerModeRomSw == 0x70) {
	/*	SH__WCR1 = (WCR1_CS3_3WAIT + WCR1_CS2_NO_WAIT + WCR1_CS1_2WAIT + WCR1_CS0_5WAIT);*/
		SH__WCR1 = (WCR1_CS3_3WAIT + WCR1_CS2_NO_WAIT + WCR1_CS1_2WAIT + 0x0003);
	}
	else {
		/* SH__WCR1 = (WCR1_CS3_3WAIT + WCR1_CS2_NO_WAIT + WCR1_CS1_2WAIT + WCR1_CS0_2WAIT); */
		SH__WCR1 = (WCR1_CS3_3WAIT + WCR1_CS2_NO_WAIT + WCR1_CS1_2WAIT + WCR1_CS0_3WAIT);
	}
#else
	SH__WCR1 = (WCR1_CS3_3WAIT + WCR1_CS2_NO_WAIT + WCR1_CS1_2WAIT + WCR1_CS0_2WAIT);
#endif

	/*--------------------------------------------------------------*/
	/* ＤＣＲ（ＤＲＡＭエリアコントロールレジスタ）の設定し直し     */
	/* ・ＲＡＳ−ＣＡＳ遅延サイクル数２サイクル                     */
	/*--------------------------------------------------------------*/
	SH__DCR |= DCR_RAS_DELAY_2CYCLE;

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
	/* ＰＯＰＬＡＲ＿Ｈは漢字ＬＣＤのＬＣＤ＿ＢＵＳＹがこのポートに入っているので、
	** Ｂｕｓｙがくれば、Ｗａｉｔするように設定する。
	** By O.Kimoto 1997/09/24
	*/
	PFC__PACRH |= PACRH_PA17MD_WAIT;	/**  ＰＡ１７はＷＡＩＴ             */
#endif

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jul.9,1998 */
	/* 拡張ＲＯＭが未接続でＲＳ２３２Ｃ基板のみ接続のとき呼ばれるべきINT_MPSC()が拡張ＲＯＭ側にあるので
    ** 拡張ＲＯＭがない場合(CL1_IsExClass1ROM == FALSE)はINT_MPSC()をCALLしない事とする 
    */
	CL1_IsExClass1ROM = FALSE;
#endif

	/*--------------------------------------------*/
	/* ＳＨ７０４３ 内蔵Ｉ／Ｏ初期設定            */
	/*--------------------------------------------*/
	InitializeInternalDevice();

	/* if (SYB_MaintenanceSwitch[MNT_SW_A8] & SH_PA15MD_CK) { 1997/12/24  By T.Yamaguchi */
		PFC__PACRL1 |= PACRL1_PA15MD_CK; /* SH CPU の PA15 を CK出力にする T.Nose 1997/08/28 */
	/* } */

	/*--------------------------------------------*/
	/* 外部追加割込制御ポートの初期設定           */
	/*--------------------------------------------*/
	INT_InitializeExternalInterrupt();

#if (PRO_EXT_DMAC == ENABLE)
	/*--------------------------------------------*/
	/* 外部ＤＭＡＣ初期設定                       */
	/*--------------------------------------------*/
	INI_ExternalDMAC();
#endif

#if !defined(POPLAR_H)
	/*--------------------------------------------*/
	/* チェッカーモードのコピー                   */
	/*--------------------------------------------*/
	CheckerMode = CheckerModeRomSw;
#endif

	/* 念のためヒーターをＯＦＦします */
#if (PRO_PRINT_TYPE == LED)
	outpw(MODEM2_PORT, 0);
#endif

	/*--------------------------------------------*/
	/* アナログファンクションチェッカーの時       */
	/*--------------------------------------------*/
#if defined(POPLAR_B) || defined(POPLR_BN) || defined(POPLAR_L)	/* Add By O.Kimoto 1998/03/09 */
	if (CheckerMode == 0x00) {
		/* command = inpw(0x00C20200);	 */ /** コマンド読み込み */
		command = inpw(COMMAND_PORT);	/** コマンド読み込み */
		command &= 0x00ff;
		if ((command == CHECK_MODEM_TX) 
		|| (command == CHECK_MODEM_RX) 
#if (PRO_PRINT_TYPE == LED)
 #if defined(POPLAR_B) || defined(POPLR_BN)
		|| (command == CHECK_MD9509)
 #endif
#endif
		|| (command == CHECK_SHADING)
		|| (command == CHECK_TX_OUT_1080HZ)
		|| (command == CHECK_TX_OUT_5000HZ)
		|| (command == CHECK_RS232C)) {	/* モデム送受信チェックでない、CLAAS1も追加,MD9509追加 */
			/* TX,RXﾃｽﾄ時はman_main()で呼ばれる */
		}
		else {
			AnalogFunctionCheckerMain();				
		}
	}
#endif
#if (PRO_EXT_DMAC == ENABLE)	/* 一時的に入れる */
	/*--------------------------------------------*/
	/* デバッグ用にＳＲＡＭをクリアする			  */
	/*--------------------------------------------*/
	/*	ＳＲＡＭ書き込み、読み出し、比較	*/
	dbg_sw = 0;
	if (dbg_sw == 1) {
		start_address = (UBYTE *)(0x00400000);
		end_address = (UBYTE *)(0x0040ffff);
		for (; start_address <= end_address; start_address++) {	/** 終了アドレスまでループ */
			*start_address = 0xff;					/** テストコードの書き込み */
		}
		start_address = (UBYTE *)(0x00440000);
		end_address = (UBYTE *)(0x0044ffff);
		for (; start_address <= end_address; start_address++) {	/** 終了アドレスまでループ */
			*start_address = 0xff;					/** テストコードの書き込み */
		}
	}
#endif

	/*--------------------------------------------*/
	/** １０ｍｓタイマー割込みスタート			  */
	/*--------------------------------------------*/
	INI_Start10msTimer();

	/*--------------------------------------------*/
	/*  モニタテーブル初期化                      */
	/*--------------------------------------------*/
	InitializeMonitor();

	return;
}