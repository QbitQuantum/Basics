/* virtual */ void COrder_Die::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-die\"");
	if (this->Finished) {
		file.printf(", \"finished\"");
	}
	file.printf("}");
}