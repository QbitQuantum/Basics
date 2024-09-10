/* virtual */ void COrder_Repair::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-repair\",");

	if (this->Finished) {
		file.printf(" \"finished\", ");
	}
	if (this->HasGoal()) {
		file.printf(" \"goal\", \"%s\",", UnitReference(this->GetGoal()).c_str());
	}
	file.printf(" \"tile\", {%d, %d},", this->goalPos.x, this->goalPos.y);

	if (this->ReparableTarget != NULL) {
		file.printf(" \"repair-target\", \"%s\",", UnitReference(this->GetReparableTarget()).c_str());
	}

	file.printf(" \"repaircycle\", %d,", this->RepairCycle);
	file.printf(" \"state\", %d", this->State);

	file.printf("}");
}