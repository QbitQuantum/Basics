/**
**  Cast capture.
**
**  @param caster       Unit that casts the spell
**  @param spell        Spell-type pointer
**  @param target       Target unit that spell is addressed to
**  @param goalPos      coord of target spot when/if target does not exist
**
**  @return             =!0 if spell should be repeated, 0 if not
*/
/* virtual */ int Spell_Capture::Cast(CUnit &caster, const SpellType &spell, CUnit *target, const Vec2i &/*goalPos*/)
{
	if (!target || caster.Player == target->Player) {
		return 0;
	}

	if (this->DamagePercent) {
		if ((100 * target->Variable[HP_INDEX].Value) /
			target->Variable[HP_INDEX].Max > this->DamagePercent &&
			target->Variable[HP_INDEX].Value > this->Damage) {
			HitUnit(&caster, *target, this->Damage);
			if (this->SacrificeEnable) {
				// No corpse.
				caster.Remove(NULL);
				caster.Release();
			}
			return 1;
		}
	}
	caster.Player->Score += target->Variable[POINTS_INDEX].Value;
	if (caster.IsEnemy(*target)) {
		if (target->Type->Building) {
			caster.Player->TotalRazings++;
		} else {
			caster.Player->TotalKills++;
		}
		//Wyrmgus start
		caster.Player->UnitTypeKills[target->Type->Slot]++;
		/*
		if (UseHPForXp) {
			caster.Variable[XP_INDEX].Max += target->Variable[HP_INDEX].Value;
		} else {
			caster.Variable[XP_INDEX].Max += target->Variable[POINTS_INDEX].Value;
		}
		caster.Variable[XP_INDEX].Value = caster.Variable[XP_INDEX].Max;
		*/
		
		//distribute experience between nearby units belonging to the same player
		if (!target->Type->BoolFlag[BUILDING_INDEX].value) {
			std::vector<CUnit *> table;
			SelectAroundUnit(caster, 6, table, MakeAndPredicate(HasSamePlayerAs(*caster.Player), IsNotBuildingType()));

			if (UseHPForXp) {
				caster.Variable[XP_INDEX].Max += target->Variable[HP_INDEX].Value / (table.size() + 1);
			} else {
				caster.Variable[XP_INDEX].Max += target->Variable[POINTS_INDEX].Value / (table.size() + 1);
			}
			caster.Variable[XP_INDEX].Value = caster.Variable[XP_INDEX].Max;
			caster.XPChanged();

			for (size_t i = 0; i != table.size(); ++i) {
				if (UseHPForXp) {
					table[i]->Variable[XP_INDEX].Max += target->Variable[HP_INDEX].Value / (table.size() + 1);
				} else {
					table[i]->Variable[XP_INDEX].Max += target->Variable[POINTS_INDEX].Value / (table.size() + 1);
				}
				table[i]->Variable[XP_INDEX].Value = table[i]->Variable[XP_INDEX].Max;
				table[i]->XPChanged();
			}
		}
		//Wyrmgus end
		caster.Variable[KILL_INDEX].Value++;
		caster.Variable[KILL_INDEX].Max++;
		caster.Variable[KILL_INDEX].Enable = 1;
	}
	target->ChangeOwner(*caster.Player);
	UnitClearOrders(*target);
	if (this->JoinToAIForce && caster.Player->AiEnabled) {
		int force = caster.Player->Ai->Force.GetForce(caster);
		if (force != -1) {
			caster.Player->Ai->Force[force].Insert(*target);
			target->GroupId = caster.GroupId;
			CommandDefend(*target, caster, FlushCommands);
		}
	}
	if (this->SacrificeEnable) {
		// No corpse.
		caster.Remove(NULL);
		caster.Release();
	} else {
		caster.Variable[MANA_INDEX].Value -= spell.ManaCost;
	}
	return 0;
}