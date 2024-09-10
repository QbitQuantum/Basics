bool UniPAX::TemplateReaction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"product"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "TemplateReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		product.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"templateentity"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;
		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "TemplateReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		templateEntity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object);
		return true;
	}
	if (boost::iequals(attribute,"templatedirection"))
	{
		setTemplateDirection(value);
		return true;
	}

	return false;

}