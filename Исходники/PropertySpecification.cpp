// Registers a shorthand property definition.
bool PropertySpecification::RegisterShorthand(const String& shorthand_name, const String& property_names, ShorthandType type)
{
	StringList properties;
	StringUtilities::ExpandString(properties, property_names.ToLower());

	if (properties.empty())
		return false;

	String lower_case_name = shorthand_name.ToLower();

	// Construct the new shorthand definition and resolve its properties.
	PropertyShorthandDefinition* property_shorthand = new PropertyShorthandDefinition();
	for (size_t i = 0; i < properties.size(); i++)
	{
		const PropertyDefinition* property = GetProperty(properties[i]);
		if (property == NULL)
		{
			Log::Message(Log::LT_ERROR, "Shorthand property '%s' was registered with invalid property '%s'.", shorthand_name.CString(), properties[i].CString());
			delete property_shorthand;

			return false;
		}

		property_shorthand->properties.push_back(PropertyShorthandDefinition::PropertyDefinitionList::value_type(properties[i], property));
	}

	if (type == AUTO)
	{
		if (properties.size() == 4 &&
			properties[0].Find("-top") != String::npos &&
			properties[1].Find("-right") != String::npos &&
			properties[2].Find("-bottom") != String::npos &&
			properties[3].Find("-left") != String::npos)
			property_shorthand->type = BOX;
		else
			property_shorthand->type = FALL_THROUGH;
	}
	else
		property_shorthand->type = type;

	shorthands[lower_case_name] = property_shorthand;
	return true;
}