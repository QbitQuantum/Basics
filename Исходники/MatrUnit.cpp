//---------------------------------------------------------------------------
void __fastcall TMatrForm::dgDrawCell(TObject *Sender, int ACol, int ARow,
	  TRect &Rect, TGridDrawState State)
{
	AnsiString s, n1, n2, n3;
	int ball, PartCode;
	TDrawGrid* dg = (TDrawGrid*)Sender;
	TColor clr;
	TRect rect;
	TTaskTypeList *Tasks;
	TMatrArr *Grid;
	TColor clError = (TColor)0x00CCCCFF;
	
//	TTextFormat tf;

	try {

	if (!MatrixList->Count)
		return;

	Tasks = CurMatrix->Tasks;
	Grid = CurMatrix->Grid;

	//Нумерация
	if (ACol == 0) {
		s = ARow;
		DrawTextA(dg->Canvas->Handle, s.c_str(), s.Length(), &Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	//Номера заданий
	if (ARow == 0 && ACol >= TASK_COL && ACol < Tasks->Count + TASK_COL) {
//		if (Tasks->Number1[ACol - TASK_COL])
//			n1 = String((char)(Tasks->Number1[ACol - TASK_COL] - 1 + 'A'));
//		else
//			n1 = "";
//
//		if (Tasks->Number2[ACol - TASK_COL])
//			n2 = IntToStr(Tasks->Number2[ACol - TASK_COL]);
//		else
//			n2 = "";
//
//		if (Tasks->Number3[ACol - TASK_COL])
//			n3 = "." + IntToStr(Tasks->Number3[ACol - TASK_COL]);
//		else
//			n3 = "";
//
//		s = n1 + n2 + n3;
		s = Tasks->Caption[ACol - TASK_COL];
		DrawTextA(dg->Canvas->Handle, s.c_str(), s.Length(), &Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	//Код ученика
	if (ARow == 0 && ACol == 1) {
		rect = Rect;
		dg->Canvas->FillRect(Rect);
		rect.left += 2;
		s = "Код ученика";
		DrawTextA(dg->Canvas->Handle, s.c_str(), s.Length(), &rect, DT_WORDBREAK | DT_VCENTER);
	}

	//Заливка
	/*if (ARow > 0 && ACol >= TASK_COL) {
		if (Tasks->Number1[ACol - TASK_COL] == 0) {
			dg->Canvas->Brush->Color = (TColor)0xefffff;
			dg->Canvas->FillRect(Rect);
		}
		if (Tasks->Number1[ACol - TASK_COL] == 1) {
			dg->Canvas->Brush->Color = (TColor)0xffefff;
			dg->Canvas->FillRect(Rect);
		}
		if (Tasks->Number1[ACol - TASK_COL] == 2) {
			dg->Canvas->Brush->Color = (TColor)0xffffef;
			dg->Canvas->FillRect(Rect);
		}
	}*/

	if (ACol == 1 && ARow == 1) {
		s = s;
	}

	//Заполнение кодов учеников
	if (ACol == PARTICIPANT_COL && ARow >= START_ARR_ROW && (ACol - START_ARR_COL) < Grid->ColCount)	{
		PartCode = Grid->Cells[ARow - START_ARR_ROW][ACol - PARTICIPANT_COL].ToIntDef(0);
		if (Grid->Cells[ARow - START_ARR_ROW][ACol - PARTICIPANT_COL] != "" &&
			(PartCode <= 0 || MatrixList->ParticipantMatch(PartCode, ACol - PARTICIPANT_COL))) {
			dg->Canvas->Brush->Color = clError;
			dg->Canvas->FillRect(Rect);
//			ImageList1->Draw(dg->Canvas, 200, 200, 0, true);
		}
		s = Grid->Cells[ARow - START_ARR_ROW][ACol - START_ARR_COL];
		DrawTextA(dg->Canvas->Handle, s.c_str(), s.Length(), &Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	
	//Заполнение из массива
	if (ACol > START_ARR_COL && (ACol - START_ARR_COL) < Grid->ColCount &&
		ARow >= START_ARR_ROW && ARow <= Grid->RowCount)
	{
		s = Grid->Cells[ARow - START_ARR_ROW][ACol - START_ARR_COL];
		if (s != "" && ACol != PARTICIPANT_COL) {
			ball = s.ToIntDef(-1);
			if ((ball < 0 || ball > Tasks->BallMax[ACol - TASK_COL]) && ACol >= TASK_COL) {
				dg->Canvas->Brush->Color = clError;
				dg->Canvas->FillRect(Rect);
			}
		}
		DrawTextA(dg->Canvas->Handle, s.c_str(), s.Length(), &Rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	} catch (...) {
//		ShowMessage("Произошёл сбой программы. Программа будет закрыта.");
//		dg->OnDrawCell = dgDrawCell;
	}
}