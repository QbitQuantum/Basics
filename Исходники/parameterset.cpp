// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool ParameterSet::detachFrom(PublicObject* object) {
	if ( object == NULL ) return false;

	// check all possible parents
	Config* config = Config::Cast(object);
	if ( config != NULL ) {
		// If the object has been added already to the parent locally
		// just remove it by pointer
		if ( object == parent() )
			return config->remove(this);
		// The object has not been added locally so it must be looked up
		else {
			ParameterSet* child = config->findParameterSet(publicID());
			if ( child != NULL )
				return config->remove(child);
			else {
				SEISCOMP_DEBUG("ParameterSet::detachFrom(Config): parameterSet has not been found");
				return false;
			}
		}
	}

	SEISCOMP_ERROR("ParameterSet::detachFrom(%s) -> wrong class type", object->className());
	return false;
}