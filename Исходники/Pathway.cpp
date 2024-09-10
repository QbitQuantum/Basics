bool UniPAX::Pathway::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Entity::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"modelExtensions"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		modelExtensions.push_back(boost::dynamic_pointer_cast<UniPAX::Model>(object));
		return true;
	}

	if (boost::iequals(attribute,"pathwayComponent") || boost::iequals(attribute,"component"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		pathwayComponent.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}
	if (boost::iequals(attribute,"pathwayOrder"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		pathwayOrder.push_back(boost::dynamic_pointer_cast<UniPAX::PathwayStep>(object));
		return true;
	}
	if (boost::iequals(attribute,"organism"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}

	return false;

}