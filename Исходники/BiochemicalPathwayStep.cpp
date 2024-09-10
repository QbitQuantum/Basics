bool UniPAX::BiochemicalPathwayStep::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::PathwayStep::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"stepConversion"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BiochemicalPathwayStep::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		stepConversion = boost::dynamic_pointer_cast<UniPAX::Conversion>(object);
		return true;
	}
	if (boost::iequals(attribute,"stepDirection"))
	{
		setStepDirection(value);
		return true;
	}

	return false;

}