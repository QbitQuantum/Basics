bool UniPAX::GeneticInteraction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"interactionScore"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "GeneticInteraction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		interactionScore.push_back(boost::dynamic_pointer_cast<UniPAX::Score>(object));
		return true;
	}
	if (boost::iequals(attribute,"phenotype"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "GeneticInteraction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		phenotype.push_back(boost::dynamic_pointer_cast<UniPAX::PhenotypeVocabulary>(object));
		return true;
	}

	return false;

}