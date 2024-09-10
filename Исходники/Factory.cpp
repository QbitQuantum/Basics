	ob_instance::Instance* Factory::create(std::string className){
		if(lokupTable[className]){
			ClassMaker* maker = lokupTable[className];
			if(maker->isInstantiatable()){
				return maker->getInstance();
			}
		}

		return NULL;
	}