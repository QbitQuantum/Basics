/* virtual */ void COrder_Train::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-train\",");
	if (this->Finished) {
		file.printf(" \"finished\", ");
	}
	file.printf("\"type\", \"%s\",", this->Type->Ident.c_str());
	file.printf("\"ticks\", %d", this->Ticks);
	file.printf("}");
}