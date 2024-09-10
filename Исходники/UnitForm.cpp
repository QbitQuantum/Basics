bool TForm1::VarMi(UnicodeString bunda1, UnicodeString bundan1) {

	char* bunda = AnsiString(bunda1).c_str();
	char* bundan = AnsiString(bundan1).c_str();

	for (int i = 0; i < bunda1.Length(); i++) {

		for (int j = 0; j < bundan1.Length(); j++) {
			if (bunda[i] == bundan[j])
				return true;
		}
	}
	return false;
}