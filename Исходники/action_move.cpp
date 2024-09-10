/* virtual */ void COrder_Move::Save(CFile &file, const CUnit &unit) const
{
	file.printf("{\"action-move\",");

	if (this->Finished) {
		file.printf(" \"finished\", ");
	}
	file.printf(" \"range\", %d,", this->Range);
	file.printf(" \"tile\", {%d, %d}", this->goalPos.x, this->goalPos.y);

	file.printf("}");
}