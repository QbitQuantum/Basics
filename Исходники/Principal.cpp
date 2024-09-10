void __fastcall TfrmPrincipal::Button4Click(TObject *Sender)
{
	Node meuPrimeiroNo;//Aloco memoria e consequentemente o endereço
	meuPrimeiroNo.b = 123;
	ShowMessage(String(meuPrimeiroNo.b));
	meuPrimeiroNo.calcularQuadrado();
	meuPrimeiroNo.setA(1);
	ShowMessage(String(meuPrimeiroNo.getA()));

	NoParrudo meuPrimeiroNoParrudo;

	meuPrimeiroNo.setB(2);
	ShowMessage(String(meuPrimeiroNo.getB()));

	meuPrimeiroNo.setC(3);
	ShowMessage(String(meuPrimeiroNo.getC()));

	ShowMessage(meuPrimeiroNo.getAStr() + " " + meuPrimeiroNo.getBStr() + " " + meuPrimeiroNo.getCStr());

	meuPrimeiroNo.minhaClasse();
	meuPrimeiroNoParrudo.minhaClasse();

	NoParrudo noMisterioso;
	noMisterioso = meuPrimeiroNoParrudo;

	noMisterioso.minhaClasse();
//	noMisterioso = <
}