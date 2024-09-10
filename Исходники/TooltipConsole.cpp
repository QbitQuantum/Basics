std::string CTooltipConsole::MakeUnitString(const CUnit* unit)
{
    string custom = eventHandler.WorldTooltip(unit, NULL, NULL);
    if (!custom.empty()) {
        return custom;
    }

    std::string s;

    const bool enemyUnit = (teamHandler->AllyTeam(unit->team) != gu->myAllyTeam) &&
                           !gu->spectatingFullView;

    const UnitDef* unitDef = unit->unitDef;
    const UnitDef* decoyDef = enemyUnit ? unitDef->decoyDef : NULL;
    const UnitDef* effectiveDef =
        !enemyUnit ? unitDef : (decoyDef ? decoyDef : unitDef);
    const CTeam* team = NULL;

    // don't show the unit type if it is not known
    const unsigned short losStatus = unit->losStatus[gu->myAllyTeam];
    const unsigned short prevMask = (LOS_PREVLOS | LOS_CONTRADAR);
    if (enemyUnit &&
            !(losStatus & LOS_INLOS) &&
            ((losStatus & prevMask) != prevMask)) {
        return "Enemy unit";
    }


    // show the player name instead of unit name if it has FBI tag showPlayerName
    if (effectiveDef->showPlayerName) {
        team = teamHandler->Team(unit->team);
        s = team->GetControllerName();
    } else {
        if (!decoyDef) {
            s = unit->tooltip;
        } else {
            s = decoyDef->humanName + " - " + decoyDef->tooltip;
        }
    }


    // don't show the unit health and other info if it has
    // the FBI tag hideDamage and is not on our ally team or
    // is not in LOS
    if (!enemyUnit || (!effectiveDef->hideDamage && (losStatus & LOS_INLOS))) {
        if (!decoyDef) {
            const float cost = unit->metalCost + (unit->energyCost / 60.0f);
            s += MakeUnitStatsString(
                     unit->health, unit->maxHealth,
                     unit->currentFuel, unitDef->maxFuel,
                     unit->experience, cost, unit->maxRange,
                     unit->metalMake,  unit->metalUse,
                     unit->energyMake, unit->energyUse);
        } else {
            // display adjusted decoy stats
            const float cost = decoyDef->metalCost + (decoyDef->energyCost / 60.0f);
            const float healthScale = (decoyDef->health / unitDef->health);
            float fuelScale;
            if (unitDef->maxFuel > 0.0f) {
                fuelScale = (decoyDef->maxFuel / unitDef->maxFuel);
            } else {
                fuelScale = 0.0f;
            }

            // get the adjusted resource stats
            float metalMake, energyMake, metalUse, energyUse;
            GetDecoyResources(unit, metalMake, metalUse, energyMake, energyUse);

            s += MakeUnitStatsString(
                     unit->health * healthScale, unit->maxHealth * healthScale,
                     unit->currentFuel * fuelScale, decoyDef->maxFuel,
                     unit->experience, cost, decoyDef->maxWeaponRange,
                     metalMake,  metalUse,
                     energyMake, energyUse);
        }
    }

    if (gs->cheatEnabled) {
        char buf[32];
        SNPRINTF(buf, 32, DARKBLUE "  [TechLevel %i]", unit->unitDef->techLevel);
        s += buf;
    }

    return s;
}