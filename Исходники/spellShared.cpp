Tab* spellsTab(const char* tabId, const char* tabTitle, ItrPair<Spell>& spells,
	bool haveSkillName)
{
	gNpcTrainers.load();
	gSpellIcons.load();
	gSkillLines.load();
	SkillLineAbilityIndex::load();

	tabTableChtml& t = *new tabTableChtml();
	t.id = tabId;
	t.title = tabTitle;
	t.columns.push_back(Column(ICON, "Icon/item", Column::NoEscape));
	t.columns.push_back(Column(NAME, "Name", Column::NoEscape));
	t.columns.push_back(Column(REAGENTS, "Reagents", Column::NoEscape));
	t.columns.push_back(Column(SOURCE, "Source", Column::NoEscape));
	t.columns.push_back(Column(SKILL, "Skill", Column::NoEscape));

	// it's expensive to construct this object. let's keep one instance.
	std::ostringstream stream;

	while(spells.hasNext()) {
		const Spell& s(spells.next());
		const Spell::Effect& e(s.effect[0]);
		const Quality* itemQuality = NULL;
		Row r;
		r[ENTRY] = toString(s.id);

		// ICON
		stream.str("");
		if(e.itemType) {
			itemQuality = streamMultiItem(stream, e.itemType, e.basePoints + e.dieSides);
		} else {
			const SpellIcon* si = gSpellIcons.find(s.spellIconID);
			if(si) {
				stream <<"<img src=\"";
				ESCAPE_URL(getIconRaw(si->icon));
				stream <<"\" alt=\"";
				ESCAPE(si->icon);
				stream <<"\">";
			} else if(s.spellIconID != 0) {
				stream << "Warning: invalid icon id ("<<s.spellIconID<<")";
			}
		}
		r[ICON] = stream.str();

		// NAME
		stream.str("");
		stream <<"<a href=\"spell="<<s.id<<"\">";
		if(itemQuality) {
			stream <<"<span style=\"color:#"<<itemQuality->color<<";\">";
		}
		ESCAPE(s.name);
		if(s.rank) if(s.rank[0]) {
			stream <<" ("<<s.rank<<")";
		}
		if(itemQuality) {
			stream <<"</span>";
		}
		stream <<"</a>";
		r[NAME] = stream.str();

		// REAGENTS
		stream.str("");
		for(size_t i=0; i<ARRAY_SIZE(s.reagent); i++) {
			const Spell::Reagent& re(s.reagent[i]);
			streamMultiItem(stream, re.id, re.count);
		}
		r[REAGENTS] = stream.str();

		// SOURCE
		stream.str("");
		int requiredSkillLevel = streamSource(stream, s.id);
		r[SOURCE] = stream.str();

		// SKILL
		stream.str("");
		auto slas = SkillLineAbilityIndex::findSpell(s.id);
		for(; slas.first != slas.second; ++slas.first) {
			const SkillLineAbility* sla = slas.first->second;
			stream << "<!--";
			if(haveSkillName) {
				stream << gSkillLines[sla->skill].name;
			}
			{
				char buf[32];
				sprintf(buf, "%04i", sla->minValue);
				stream <<buf<<"-->";
			}
			if(haveSkillName) {
				stream <<"<a href=\"spells="<<sla->skill<<"\">"<<gSkillLines[sla->skill].name<<"</a>\n";
			}
			if(requiredSkillLevel >= 0) {
				stream <<"<span class=\"skillRed\">"<<requiredSkillLevel<<"</span>\n";
			}
			stream <<"<span class=\"skillYellow\">"<<sla->minValue<<"</span>\n";
			stream <<"<span class=\"skillGreen\">"<<
				(sla->maxValue - (sla->maxValue - sla->minValue) / 2)<<"</span>\n";
			stream <<"<span class=\"skillGray\">"<<sla->maxValue<<"</span>\n";
		}
		r[SKILL] = stream.str();

		t.array.push_back(r);
	}
	t.count = t.array.size();
	return &t;
}