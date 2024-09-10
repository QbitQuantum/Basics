bool UniPAX::Dna::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::PhysicalEntity::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"entityReference"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Dna::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityReference.push_back(boost::dynamic_pointer_cast<UniPAX::EntityReference>(object));
		return true;
	}

	return false;

}