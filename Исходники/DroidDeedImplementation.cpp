void DroidDeedImplementation::processModule(BaseDroidModuleComponent* module, uint32 crc) {
	if (module == NULL)
		return;
	if (module->isStackable()) {
		if (modules.containsKey(module->getModuleName())) {
			// add to the stack if stackable.
			DroidComponent* comp = modules.get(module->getModuleName());
			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(comp->getDataObjectComponent()->get());
			bmodule->addToStack(module);
		} else {
			ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc,1)).castTo<DroidComponent*>();
			dcomp->setParent(NULL);
			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());
			bmodule->copy(module);
			bmodule->setSpecies(species);
			modules.put(module->getModuleName(),dcomp);
		}
	} else {
		ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc,1)).castTo<DroidComponent*>();
		dcomp->setParent(NULL);
		BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());
		bmodule->copy(module);
		bmodule->setSpecies(species);
		modules.put(module->getModuleName(),dcomp);
	}

}