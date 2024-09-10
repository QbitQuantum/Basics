void EntityRecipe::associateBindings()
{
	S_LOG_VERBOSE("Associating bindings.");
	if (mEntitySpec) {
		// Iterate over all entity spec XML nodes
		EntityRecipe::SpecIterator iter(this);
		TiXmlElement *elem = mEntitySpec->FirstChildElement("atlas");
		if (elem) {
			elem->Accept(&iter);
		}
	}
}