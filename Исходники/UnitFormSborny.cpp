double TfSbornyZakaz::Sum() {
	LockWindowUpdate(Handle);
	double sum = 0;

	// здесь сбрасываем использование принтеров
	for (int i = 0; i < listOfTools->Count; i++) {
		TTool *tool = (TTool*)listOfTools->Items[i];
		tool->SetUse(false);
	}

	// чистим
	slgoods->Clear();
	Memo1->Clear();
	sldescription->Clear();

	if (sbForSelFrame->ControlCount == 0) {
		sum = 0;
	}
	else {
		// поищем что есть посчитать, все фреймы, виртуальная функция Sum
		for (int i = 0; i < listOfIzdelies->Count; i++) {
			TfrSelectable *izdelie =
				dynamic_cast<TfrSelectable*>(listOfIzdelies->Items[i]);
			sum += izdelie->Sum();
		}

		double zakazCount = spCount->Value;
		// подсчитаем использование оборудования
		for (int i = 0; i < listOfTools->Count; i++) {
			TToolPrepareTool *tool =
				dynamic_cast<TToolPrepareTool*>(listOfTools->Items[i]);
			if (tool && tool->GetUse() == true) {
				Memo1->Lines->Add(tool->prepareTool->myToString(zakazCount));
				sum += Ceil(tool->prepareTool->price * zakazCount);
			}
		}

	}

	lbAllPrice->Caption = "Сумма: " + FloatToStrF(sum, ffFixed, 10, 2) +
		" руб.";

	allsum = sum;

	LockWindowUpdate(NULL);
	return sum;
}