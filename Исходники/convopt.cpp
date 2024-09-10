//---------------------------------------------------------------------------
void __fastcall TConvOptDialog::FormShow(TObject *Sender)
{
	AnsiString s;
	RnxVer->ItemIndex=MainWindow->RnxVer;
	RnxFile->Checked=MainWindow->RnxFile;
	RnxCode->Text=MainWindow->RnxCode;
	RunBy->Text=MainWindow->RunBy;
	Marker->Text=MainWindow->Marker;
	MarkerNo->Text=MainWindow->MarkerNo;
	MarkerType->Text=MainWindow->MarkerType;
	Name0->Text=MainWindow->Name[0];
	Name1->Text=MainWindow->Name[1];
	Rec0->Text=MainWindow->Rec[0];
	Rec1->Text=MainWindow->Rec[1];
	Rec2->Text=MainWindow->Rec[2];
	Ant0->Text=MainWindow->Ant[0];
	Ant1->Text=MainWindow->Ant[1];
	Ant2->Text=MainWindow->Ant[2];
	AppPos0->Text=s.sprintf("%.4f",MainWindow->AppPos[0]);
	AppPos1->Text=s.sprintf("%.4f",MainWindow->AppPos[1]);
	AppPos2->Text=s.sprintf("%.4f",MainWindow->AppPos[2]);
	AntDel0->Text=s.sprintf("%.4f",MainWindow->AntDel[0]);
	AntDel1->Text=s.sprintf("%.4f",MainWindow->AntDel[1]);
	AntDel2->Text=s.sprintf("%.4f",MainWindow->AntDel[2]);
	Comment0->Text=MainWindow->Comment[0];
	Comment1->Text=MainWindow->Comment[1];
	RcvOption->Text=MainWindow->RcvOption;
	for (int i=0;i<6;i++) CodeMask[i]=MainWindow->CodeMask[i];
	AutoPos->Checked=MainWindow->AutoPos;
	ScanObs->Checked=MainWindow->ScanObs;
	OutIono->Checked=MainWindow->OutIono;
	OutTime->Checked=MainWindow->OutTime;
	OutLeaps->Checked=MainWindow->OutLeaps;

	Nav1->Checked=MainWindow->NavSys&SYS_GPS;
	Nav2->Checked=MainWindow->NavSys&SYS_GLO;
	Nav3->Checked=MainWindow->NavSys&SYS_GAL;
	Nav4->Checked=MainWindow->NavSys&SYS_QZS;
	Nav5->Checked=MainWindow->NavSys&SYS_SBS;
	Nav6->Checked=MainWindow->NavSys&SYS_CMP;
	Obs1->Checked=MainWindow->ObsType&OBSTYPE_PR;
	Obs2->Checked=MainWindow->ObsType&OBSTYPE_CP;
	Obs3->Checked=MainWindow->ObsType&OBSTYPE_DOP;
	Obs4->Checked=MainWindow->ObsType&OBSTYPE_SNR;
	Freq1->Checked=MainWindow->FreqType&FREQTYPE_L1;
	Freq2->Checked=MainWindow->FreqType&FREQTYPE_L2;
	Freq3->Checked=MainWindow->FreqType&FREQTYPE_L5;
	Freq4->Checked=MainWindow->FreqType&FREQTYPE_L6;
	Freq5->Checked=MainWindow->FreqType&FREQTYPE_L7;
	Freq6->Checked=MainWindow->FreqType&FREQTYPE_L8;
	ExSats->Text=MainWindow->ExSats;
	TraceLevel->ItemIndex=MainWindow->TraceLevel;
	
	UpdateEnable();
}