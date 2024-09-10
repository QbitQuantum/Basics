/* virtual */ void COrder_Research::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-research\",");

	if (this->Finished) {
		file.printf(" \"finished\", ");
	}
	//Wyrmgus start
	file.printf("\"player\", %d,", this->Player);
	//Wyrmgus end
	if (this->Upgrade) {
		file.printf(" \"upgrade\", \"%s\"", this->Upgrade->Ident.c_str());
	}
	file.printf("}");
}