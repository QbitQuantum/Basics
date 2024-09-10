void __fastcall TAcquireThread::Draw() {
	switch(mm) {
	case 0:
//		StatusRecForm->Label1->Caption = s;
//		StatusRecForm->Label2->Caption = s1;
		break;
	case 1:
		StatusRecForm->Close();
		MainForm->StartMonitoring();
		break;
	case 2:
//		StatusRecForm->Label2->Caption = "Количество блоков " + IntToStr
//			(num_blocks);
		break;
	case 3:
//		StatusRecForm->ProgressBar1->Position = pos;
		break;
	case 4:
		TFormatSettings FormatSettings;
		GetLocaleFormatSettings(GetSystemDefaultLCID(), FormatSettings);
		FormatSettings.ThousandSeparator = 160;
		FormatSettings.CurrencyString = "";
		FormatSettings.CurrencyDecimals = 0;

		MainForm->ListView2->Items->Item[0]->SubItems[0].Text = FloatToStr(t)
			+ " нс";
		MainForm->ListView2->Items->Item[1]->SubItems[0].Text = FloatToStrF
			(AcfParams._time * 1e-6, ffFixed, 5, 2) + " с";
		MainForm->ListView2->Items->Item[2]->SubItems[0].Text = Format
			("%m", ARRAYOFCONST((double(AcfParams.vybr))), FormatSettings);
		MainForm->ListView2->Items->Item[3]->SubItems[0].Text = FloatToStr
			(AcfParams.zashk / n0 * 100) + "%";
		MainForm->ListView2->Items->Item[4]->SubItems[0].Text = Format
			("%m", ARRAYOFCONST((1e6 * n1 / AcfParams._time)), FormatSettings);
		MainForm->ListView2->Items->Item[5]->SubItems[0].Text = Format
			("%m", ARRAYOFCONST((double(n1))), FormatSettings);

		int ind = 0;
		for (int i = 0; i < n1; i++) {
			if (RawData_t.a[i] > 1e6) {
				ind = i - 1;
				break;
			}
		}

		int m = Floor(ind / 1e3);
		MainForm->Series1->Clear();
		for (int i = 0; i < 1e3; i++) {
			if (!(RawData.a[i * m] == 0)) {
				MainForm->Series1->AddXY(RawData_t.a[i * m] * 1e-6, 1e9 /
					(RawData.a[i * m] * t));
			}
			else {
				MainForm->Series1->AddNullXY(RawData_t.a[i * m] * 1e-6, 0);
			}
		}
		break;
	}

}