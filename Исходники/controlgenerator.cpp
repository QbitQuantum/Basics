sp<Control> ControlGenerator::createAgentAssignmentControl(GameState &state, sp<Agent> agent)
{
	const int controlLength = 200, controlHeight = 24, iconLenght = 36;

	if (!singleton.initialised)
	{
		singleton.init(state);
	}

	auto control = mksp<Control>();
	control->setData(agent);
	control->Size = control->SelectionSize = {controlLength, controlHeight};
	control->Name = "AGENT_PORTRAIT";

	auto icon = createAgentIcon(state, agent, UnitSelectionState::Unselected, false);
	icon->Size = {iconLenght, controlHeight};
	icon->setParent(control);

	auto nameLabel = control->createChild<Label>(agent->name, singleton.labelFont);
	nameLabel->Size = {controlLength - iconLenght, singleton.labelFont->getFontHeight()};
	nameLabel->Location = {iconLenght, (control->Size.y - nameLabel->Size.y) / 2};

	return control;
}