static void get_bank_label(ArpCRef<AmBankI> bank, uint32 bankNumber, BString& out)
{
	if (bank) out = bank->Name().String();
	if (out.Length() < 1) out << "Bank " << bankNumber;
}