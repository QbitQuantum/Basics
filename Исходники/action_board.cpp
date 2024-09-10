/**
**  Enter the transporter.
**
**  @param unit  Pointer to unit.
*/
static void EnterTransporter(CUnit &unit, COrder_Board &order)
{
	CUnit *transporter = order.GetGoal();

	Assert(transporter != NULL);

	if (!transporter->IsVisibleAsGoal(*unit.Player)) {
		DebugPrint("Transporter gone\n");
		return;
	}

	if (transporter->BoardCount < transporter->Type->MaxOnBoard) {
		// Place the unit inside the transporter.
		unit.Remove(transporter);
		transporter->BoardCount++;
		unit.Boarded = 1;
		if (!unit.Player->AiEnabled) {
			// Don't make anything funny after going out of the transporter.
			CommandStopUnit(unit);
		}

		if (IsOnlySelected(*transporter)) {
			SelectedUnitChanged();
		}
		return;
	}
	DebugPrint("No free slot in transporter\n");
}