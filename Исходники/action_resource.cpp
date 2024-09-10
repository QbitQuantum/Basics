/**
**  Move to resource depot
**
**  @param unit  Pointer to unit.
**
**  @return      TRUE if reached, otherwise FALSE.
*/
int COrder_Resource::MoveToDepot(CUnit &unit)
{
	const ResourceInfo &resinfo = *unit.Type->ResInfo[this->CurrentResource];
	CUnit &goal = *this->GetGoal();
	CPlayer &player = *unit.Player;
	Assert(&goal);

	switch (DoActionMove(unit)) { // reached end-point?
		case PF_UNREACHABLE:
			//Wyrmgus start
			//if is unreachable and is on a raft, see if the raft can move closer
			if ((Map.Field(unit.tilePos)->Flags & MapFieldBridge) && !unit.Type->BoolFlag[BRIDGE_INDEX].value && unit.Type->UnitType == UnitTypeLand) {
				std::vector<CUnit *> table;
				Select(unit.tilePos, unit.tilePos, table);
				for (size_t i = 0; i != table.size(); ++i) {
					if (!table[i]->Removed && table[i]->Type->BoolFlag[BRIDGE_INDEX].value && table[i]->CanMove()) {
						if (table[i]->CurrentAction() == UnitActionStill) {
							CommandStopUnit(*table[i]);
							CommandMove(*table[i], this->HasGoal() ? this->GetGoal()->tilePos : this->goalPos, FlushCommands);
						}
						return 0;
					}
				}
			}
			//Wyrmgus end
			return -1;
		case PF_REACHED:
			break;
		case PF_WAIT:
			if (unit.Player->AiEnabled) {
				this->Range++;
				if (this->Range >= 5) {
					this->Range = 0;
					AiCanNotMove(unit);
				}
			}
		default:
			if (unit.Anim.Unbreakable || goal.IsVisibleAsGoal(player)) {
				return 0;
			}
			break;
	}

	//
	// Target is dead, stop getting resources.
	//
	if (!goal.IsVisibleAsGoal(player)) {
		DebugPrint("%d: Worker %d report: Destroyed depot\n" _C_ player.Index _C_ UnitNumber(unit));

		unit.CurrentOrder()->ClearGoal();

		CUnit *depot = FindDeposit(unit, 1000, unit.CurrentResource);

		if (depot) {
			UnitGotoGoal(unit, depot, SUB_MOVE_TO_DEPOT);
			DebugPrint("%d: Worker %d report: Going to new deposit.\n" _C_ player.Index _C_ UnitNumber(unit));
		} else {
			DebugPrint("%d: Worker %d report: Can't find a new resource deposit.\n"
					   _C_ player.Index _C_ UnitNumber(unit));

			// FIXME: perhaps we should choose an alternative
			this->Finished = true;
		}
		return 0;
	}

	// If resource depot is still under construction, wait!
	if (goal.CurrentAction() == UnitActionBuilt) {
		unit.Wait = 10;
		return 0;
	}

	this->ClearGoal();
	unit.Wait = resinfo.WaitAtDepot;

	// Place unit inside the depot
	if (unit.Wait) {
		int selected = unit.Selected;
		unit.Remove(&goal);
		if (selected && !Preference.DeselectInMine) {
			unit.Removed = 0;
			SelectUnit(unit);
			SelectionChanged();
			unit.Removed = 1;
		}
		unit.Anim.CurrAnim = NULL;
	}

	// Update resource.
	const int rindex = resinfo.FinalResource;
	//Wyrmgus start
//	player.ChangeResource(rindex, (unit.ResourcesHeld * player.Incomes[rindex]) / 100, true);
//	player.TotalResources[rindex] += (unit.ResourcesHeld * player.Incomes[rindex]) / 100;
	player.ChangeResource(rindex, (unit.ResourcesHeld * resinfo.FinalResourceConversionRate / 100 * player.Incomes[rindex]) / 100, true);
	player.TotalResources[rindex] += (unit.ResourcesHeld * resinfo.FinalResourceConversionRate / 100 * player.Incomes[rindex]) / 100;
	//Wyrmgus end
	unit.ResourcesHeld = 0;
	unit.CurrentResource = 0;

	if (unit.Wait) {
		//Wyrmgus start
//		unit.Wait /= std::max(1, unit.Player->SpeedResourcesReturn[resinfo.ResourceId] / SPEEDUP_FACTOR);
		unit.Wait /= std::max(1, (unit.Player->SpeedResourcesReturn[resinfo.ResourceId] + goal.Variable[TIMEEFFICIENCYBONUS_INDEX].Value) / SPEEDUP_FACTOR);
		//Wyrmgus end
		if (unit.Wait) {
			unit.Wait--;
		}
	}
	return 1;
}