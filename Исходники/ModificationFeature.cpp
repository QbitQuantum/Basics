bool UniPAX::ModificationFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityFeature::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"modificationType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ModificationFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		modificationType = boost::dynamic_pointer_cast<UniPAX::SequenceModificationVocabulary>(object);
		return true;
	}

	return false;

}