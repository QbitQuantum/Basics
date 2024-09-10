void CharSpells::makeSpellsList() {
	// Compute the maximum spell level.
	const Aurora::TwoDAFile &twodaClasses = TwoDAReg.get2DA("classes");
	const Aurora::TwoDARow &classRow = twodaClasses.getRow(_choices->getClass());
	const Common::UString gainTable = classRow.getString("SpellGainTable");
	const Aurora::TwoDAFile &twodaSpellGain = TwoDAReg.get2DA(gainTable);
	const Aurora::TwoDARow &spellLevelRow = twodaSpellGain.getRow(_choices->getCharacter().getHitDice());

	for (size_t lvl = 2; lvl < twodaSpellGain.getColumnCount(); ++lvl) {
		if (spellLevelRow.empty(lvl)) {
			_maxLevel = lvl - 3UL;
			break;
		}
	}

	_knownSpells.resize(_maxLevel + 1);
	_availSpells.resize(_maxLevel + 1);
	_remainingSpells.resize(_maxLevel + 1);

	computeRemainingSpells(classRow);

	// We need to know the spellCaster type. We can get it from the spellGain table.
	Common::UString casterName;
	if (gainTable == "CLS_SPGN_BARD") {
		casterName = "Bard";
	} else if (gainTable == "CLS_SPGN_CLER") {
		casterName = "Cleric";
	} else if (gainTable == "CLS_SPGN_DRUI") {
		casterName = "Druid";
	} else if (gainTable == "CLS_SPGN_PAL") {
		casterName = "Paladin";
	} else if (gainTable == "CLS_SPGN_RANG") {
		casterName = "Ranger";
	} else if (gainTable == "CLS_SPGN_WIZ" || gainTable == "CLS_SPGN_SORC") {
		casterName = "Wiz_Sorc";
	} else {
		error("Unknown caster name when building spells list: %s", gainTable.c_str());
	}

	Common::UString oppositeSchool = "";
	if (_choices->getSpellSchool() < UINT8_MAX) {
		const Aurora::TwoDAFile &twodaSpellsSchool = TwoDAReg.get2DA("spellschools");
		const Aurora::TwoDARow &rowSchool = twodaSpellsSchool.getRow(_choices->getSpellSchool());
		const Aurora::TwoDARow &rowOppSchool = twodaSpellsSchool.getRow(rowSchool.getInt("Opposition"));
		oppositeSchool = rowOppSchool.getString("Letter");
	}

	// Add spells to available and known list.
	const Aurora::TwoDAFile &twodaSpells = TwoDAReg.get2DA("spells");
	for (size_t sp = 0; sp < twodaSpells.getRowCount(); ++sp) {
		// TODO: Check if character already own the spell.
		const Aurora::TwoDARow &spellRow = twodaSpells.getRow(sp);

		if (spellRow.empty("Name"))
			continue;

		if (spellRow.empty(casterName))
			continue;

		// Check spell level.
		uint32 spellLevel = static_cast<uint32>(spellRow.getInt(casterName));
		if (spellLevel > _maxLevel)
			continue;

		// Check spell school.
		if (spellRow.getString("School") == oppositeSchool)
			continue;

		// The wizard knows all the level 0 spells.
		if (gainTable == "CLS_SPGN_WIZ" && spellLevel == 0) {
			Spell spell;
			spell.spellID = sp;
			spell.name = TalkMan.getString(spellRow.getInt("Name"));
			spell.icon = spellRow.getString("IconResRef");
			spell.desc = TalkMan.getString(spellRow.getInt("SpellDesc"));
			_knownSpells[spellLevel].push_back(spell);
			continue;
		}

		Spell spell;
		spell.spellID = sp;
		spell.name = TalkMan.getString(spellRow.getInt("Name"));
		spell.icon = spellRow.getString("IconResRef");
		spell.desc = TalkMan.getString(spellRow.getInt("SpellDesc"));
		_availSpells[spellLevel].push_back(spell);
	}

	// Add icon to spells levels.
	for (uint32 lvl = 0; lvl <= _maxLevel; ++lvl) {
		WidgetButton *spellLvlButton = getButton("SpellLevel" + Common::composeString<uint32>(lvl), true);

		Common::UString lvlStr = Common::composeString<uint32>(lvl);
		Common::UString iconName;
		if (lvl == 0) {
			iconName = "ir_cantrips";
		} else if (lvl > 0 && lvl < 7) {
			iconName = "ir_level" + lvlStr;
		} else {
			iconName = "ir_level789";
		}

		const std::vector<Common::UString> texture(1, iconName);
		spellLvlButton->getNode("Plane64")->setTextures(texture);
	}

	// Compute spell level limit due to ability.
	Common::UString abilityStr = classRow.getString("PrimaryAbil");
	const Aurora::TwoDAFile &twodaAbilities = TwoDAReg.get2DA("iprp_abilities");
	for (size_t ab = 0; ab < twodaAbilities.getRowCount(); ++ab) {
		const Aurora::TwoDARow &abilityRow = twodaAbilities.getRow(ab);
		if (abilityStr.toLower() == abilityRow.getString("Label").toLower()) {
			_abilityLimit = _choices->getTotalAbility(ab) - 10U;
			break;
		}
	}

	// Show the first spells level that has a level to choose.
	size_t lvlToShow = 0;
	for (size_t lvl = _maxLevel; lvl == 0UL; --lvl)
		if (_remainingSpells[lvl] > 0)
			lvlToShow = lvl;

	showSpellLevel(lvlToShow);
	updateRemainLabel();
}