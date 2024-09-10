Reference<FactoryCrate*> TangibleObjectImplementation::createFactoryCrate(bool insertSelf) {
	String file;
	uint32 type = getGameObjectType();

	if(type & SceneObjectType::ARMOR)
		file = "object/factory/factory_crate_armor.iff";
	else if(type == SceneObjectType::CHEMICAL || type == SceneObjectType::PHARMACEUTICAL || type == SceneObjectType::PETMEDECINE)
		file = "object/factory/factory_crate_chemicals.iff";
	else if(type & SceneObjectType::CLOTHING)
		file = "object/factory/factory_crate_clothing.iff";
	else if(type == SceneObjectType::ELECTRONICS)
		file = "object/factory/factory_crate_electronics.iff";
	else if(type == SceneObjectType::FOOD || type == SceneObjectType::DRINK)
		file = "object/factory/factory_crate_food.iff";
	else if(type == SceneObjectType::FURNITURE)
		file = "object/factory/factory_crate_furniture.iff";
	else if(type & SceneObjectType::INSTALLATION)
		file = "object/factory/factory_crate_installation.iff";
	else if(type & SceneObjectType::WEAPON)
		file = "object/factory/factory_crate_weapon.iff";
	else
		file = "object/factory/factory_crate_generic_items.iff";

	ObjectManager* objectManager = ObjectManager::instance();

	Reference<FactoryCrate*> crate = (getZoneServer()->createObject(file.hashCode(), 2)).castTo<FactoryCrate*>();

	if (crate == NULL)
		return NULL;

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tanoData == NULL)
		return NULL;

	crate->setMaxCapacity(tanoData->getFactoryCrateSize());

	if (insertSelf) {
		crate->transferObject(_this.get(), -1, false);
	} else {

		ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(_this.get()));

		if (protoclone == NULL)
			return NULL;

		protoclone->setParent(NULL);
		crate->transferObject(protoclone, -1, false);
	}

	crate->setCustomObjectName(getCustomObjectName(), false);

	crate->setUseCount(1);

	return crate;
}