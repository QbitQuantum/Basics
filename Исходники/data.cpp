void Pdb::MemMenu(ArrayCtrl& array, Bar& bar, const String& exp)
{
	if(bar.IsScanKeys())
		return;
	CParser p(exp);
	try {
		Val v = Exp(p);
		bool sep = true;
		if(v.ref > 0) {
			if(sep)
				bar.Separator();
			sep = false;
			bar.Add("Memory at " + exp, THISBACK1(MemoryGoto, exp));
		}
		else
		if(v.rvalue) {
			if(sep)
				bar.Separator();
			sep = false;
			bar.Add("Memory at 0x" + FormatIntHex((dword)GetInt(v)), THISBACK1(MemoryGoto, "&" + exp));
		}
		if(!v.rvalue) {
			if(sep)
				bar.Separator();
			sep = false;
			bar.Add("Memory at &&" + exp, THISBACK1(MemoryGoto, "&" + exp));
		}
	}
	catch(CParser::Error e) {
	}
}