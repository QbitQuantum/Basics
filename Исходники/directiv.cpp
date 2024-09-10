void FunctionPROC (const Symbol *sym, vector<Token *> &Tokens, vector<Byte> &Encoding)
{
	if (sym == 0)
		throw NameMissing ();

	Procedure *NewProc;

	if (Tokens.empty())
	{
		NewProc = new Procedure (sym->GetName());
	}
	else
	{
		if (Tokens.size() > 1)
		{
			cout << "Extra characters on line" << endl;
			throw 0;
		}

		Operator *op = dynamic_cast<Operator *> (Tokens[0]);
		if (op == 0)
		{
			cout << "Procedures must be either NEAR or FAR." << endl;
			throw 0;
		}

		if (op->GetName() == "NEAR")
		{
			NewProc = new Procedure (sym->GetName(), NEAR);
		}
		else if (op->GetName() == "FAR")
		{
			NewProc = new Procedure (sym->GetName(), FAR);
		}
		else
		{
			cout << "Procedures must be either NEAR or FAR." << endl;
			throw 0;
		}
	}

	CurrentAssembler->AddProcedure (NewProc);
}