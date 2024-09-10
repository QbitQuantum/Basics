//---------------------------------------------------------------------------
/// Metoda odpowiedzialna za dostosowanie znaków specjalnych w tekœcie (apostrofy itp.),
/// poprzez dodanie dodanie "\"
void __fastcall ParsujDane::DostosujZnakiSpecjalne(AnsiString &AText)
{
	AnsiString str;
	int pozycjaZnacznik = 0;

	while(pozycjaZnacznik != AText.Length())
	{
		str = AText[pozycjaZnacznik];
		if (str == "\'" || str == "\"") AText.Insert("\\", pozycjaZnacznik - 1);
		pozycjaZnacznik++;
	}
}