//---------------------------------------------------------------------------
void __fastcall TPntDialog::FormShow(TObject *Sender)
{
	TGridRect r={0};
	AnsiString s;
	double pos[3];
	int width[]={90,90,80,90};
	
	FontScale=Screen->PixelsPerInch;
	for (int i=0;i<4;i++) {
		PntList->ColWidths[i]=width[i]*FontScale/96;
	}
	PntList->DefaultRowHeight=17*FontScale/96;
	
	for (int i=0;i<PntList->RowCount;i++) {
		if (i<Plot->NWayPnt) {
			ecef2pos(Plot->PntPos[i],pos);
			PntList->Cells[0][i]=s.sprintf("%.9f",pos[0]*R2D);
			PntList->Cells[1][i]=s.sprintf("%.9f",pos[1]*R2D);
			PntList->Cells[2][i]=s.sprintf("%.4f",pos[2]);
			PntList->Cells[3][i]=Plot->PntName[i];
		}
		else {
			for (int j=0;j<PntList->ColCount;j++) PntList->Cells[j][i]="";
		}
	}
	r.Top=r.Bottom=PntList->RowCount;
	PntList->Selection=r;
}