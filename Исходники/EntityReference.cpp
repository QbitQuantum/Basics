bool UniPAX::EntityReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"memberEntityReference"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		memberEntityReferences.push_back(boost::dynamic_pointer_cast<UniPAX::EntityReference>(object));
		return true;
	}

	if (boost::iequals(attribute,"evidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidence.push_back(boost::dynamic_pointer_cast<UniPAX::Evidence>(object));
		return true;
	}

	if (boost::iequals(attribute,"entityReferenceType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityReferenceType = boost::dynamic_pointer_cast<UniPAX::EntityReferenceTypeVocabulary>(object);
		return true;
	}

	if (boost::iequals(attribute,"entityFeature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityFeature = boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object);
		return true;
	}

	if (boost::iequals(attribute,"Xref"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}
	if (boost::iequals(attribute,"name"))
	{
		addName(value);
		if (getDisplayName().empty())
			setDisplayName(value);
		if (getStandardName().empty())
			setStandardName(value);
		return true;
	}
	if (boost::iequals(attribute,"standardName"))
	{
		setStandardName(value);
		if (getDisplayName().empty())
			setDisplayName(value);
		return true;
	}
	if (boost::iequals(attribute,"displayName"))
	{
		setDisplayName(value);
		if (getStandardName().empty())
			setStandardName(value);
		return true;
	}
	return false;

}