//---------------------------------------------------------------------------
void __fastcall TMapAreaDialog::UpdateField(void)
{
	AnsiString s;
	Caption=Plot->MapImageFile;
	MapSize1->Text=s.sprintf("%d",Plot->MapSize[0]);
	MapSize2->Text=s.sprintf("%d",Plot->MapSize[1]);
	ScaleX->Text=s.sprintf("%.5f",Plot->MapScaleX);
	ScaleY->Text=s.sprintf("%.5f",Plot->MapScaleY);
	Lat->Text=s.sprintf("%.7f",Plot->MapLat);
	Lon->Text=s.sprintf("%.7f",Plot->MapLon);
	ScaleEq->Checked=Plot->MapScaleEq;
}