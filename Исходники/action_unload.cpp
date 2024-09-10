/* virtual */ void COrder_Unload::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-unload\",");
	if (this->Finished) {
		file.printf(" \"finished\", ");
	}
	file.printf(" \"range\", %d,", this->Range);
	if (this->HasGoal()) {
		file.printf(" \"goal\", \"%s\",", UnitReference(this->GetGoal()).c_str());
	}
	file.printf(" \"tile\", {%d, %d}, ", this->goalPos.x, this->goalPos.y);
	file.printf("\"state\", %d", this->State);
	file.printf("}");
}