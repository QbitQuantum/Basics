bool scenario_get_source_desc(const utf8 *name, source_desc *outDesc)
{
	assert(outDesc != NULL);

	sint32 currentIndex = 0;
	for (int i = 0; i < countof(ScenarioTitlesBySource); i++) {
		for (int j = 0; j < ScenarioTitlesBySource[i].count; j++) {
			const scenario_title_desc *desc = &ScenarioTitlesBySource[i].titles[j];
			if (_strcmpi(name, desc->title) == 0) {
				outDesc->title = desc->title;
				outDesc->id = desc->id;
				outDesc->source = i;
				outDesc->index = currentIndex;
				outDesc->category = desc->category;
				return true;
			}
			currentIndex++;
		}
	}

	outDesc->title = NULL;
	outDesc->id = SC_UNIDENTIFIED;
	outDesc->source = SCENARIO_SOURCE_OTHER;
	outDesc->index = -1;
	outDesc->category = SCENARIO_CATEGORY_OTHER;
	return false;
}