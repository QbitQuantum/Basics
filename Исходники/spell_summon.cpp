//Wyrmgus start
///* virtual */ int Spell_Summon::Cast(CUnit &caster, const SpellType &spell, CUnit *target, const Vec2i &goalPos)
/* virtual */ int Spell_Summon::Cast(CUnit &caster, const SpellType &spell, CUnit *target, const Vec2i &goalPos, int z)
//Wyrmgus end
{
	Vec2i pos = goalPos;
	bool cansummon;
	CUnitType &unittype = *this->UnitType;
	int ttl = this->TTL;

	if (this->RequireCorpse) {
		const Vec2i offset(1, 1);
		const Vec2i minPos = pos - offset;
		const Vec2i maxPos = pos + offset;

		//Wyrmgus start
//		CUnit *unit = FindUnit_If(minPos, maxPos, IsDyingAndNotABuilding());
		CUnit *unit = FindUnit_If(minPos, maxPos, z, IsDyingAndNotABuilding());
		//Wyrmgus end
		cansummon = false;

		if (unit != NULL) { //  Found a corpse. eliminate it and proceed to summoning.
			pos = unit->tilePos;
			//Wyrmgus start
			z = unit->MapLayer;
			//Wyrmgus end
			unit->Remove(NULL);
			unit->Release();
			cansummon = true;
		}
	} else {
		cansummon = true;
	}

	if (cansummon) {
		//Wyrmgus start
//		DebugPrint("Summoning a %s\n" _C_ unittype.Name.c_str());
		DebugPrint("Summoning a %s\n" _C_ unittype.GetDefaultName(*caster.Player).c_str());
		//Wyrmgus end

		//
		// Create units.
		// FIXME: do summoned units count on food?
		//
		target = MakeUnit(unittype, caster.Player);
		if (target != NULL) {
			target->tilePos = pos;
			//Wyrmgus start
			target->MapLayer = z;
			//Wyrmgus end
			DropOutOnSide(*target, LookingW, NULL);
			// To avoid defending summoned unit for AI
			target->Summoned = 1;
			//
			//  set life span. ttl=0 results in a permanent unit.
			//
			if (ttl) {
				target->TTL = GameCycle + ttl;
			}

			// Insert summoned unit to AI force so it will help them in battle
			if (this->JoinToAiForce && caster.Player->AiEnabled) {
				int force = caster.Player->Ai->Force.GetForce(caster);
				if (force != -1) {
					caster.Player->Ai->Force[force].Insert(*target);
					target->GroupId = caster.GroupId;
					CommandDefend(*target, caster, FlushCommands);
				}
			}

			caster.Variable[MANA_INDEX].Value -= spell.ManaCost;
		} else {
			DebugPrint("Unable to allocate Unit");
		}
		return 1;
	}
	return 0;
}