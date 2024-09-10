void StorageManager::restorePropertiesRecursively(LocatedEntity * ent)
{
    Database * db = Database::instance();
    PropertyManager * pm = PropertyManager::instance();
    DatabaseResult res = db->selectProperties(ent->getId());

    //Keep track of those properties that have been set on the instance, so we'll know what
    //type properties we should ignore.
    std::unordered_set<std::string> instanceProperties;

    DatabaseResult::const_iterator I = res.begin();
    DatabaseResult::const_iterator Iend = res.end();
    for (; I != Iend; ++I) {
        const std::string name = I.column("name");
        if (name.empty()) {
            log(ERROR, compose("No name column in property row for %1",
                               ent->getId()));
            continue;
        }
        const std::string val_string = I.column("value");
        if (name.empty()) {
            log(ERROR, compose("No value column in property row for %1,%2",
                               ent->getId(), name));
            continue;
        }
        MapType prop_data;
        db->decodeMessage(val_string, prop_data);
        MapType::const_iterator J = prop_data.find("val");
        if (J == prop_data.end()) {
            log(ERROR, compose("No property value data for %1:%2",
                               ent->getId(), name));
            continue;
        }
        assert(ent->getType() != 0);
        const Element & val = J->second;

        Element existingVal;
        if (ent->getAttr(name, existingVal) == 0) {
            if (existingVal == val) {
                //If the existing property, either on the instance or the type, is equal to the persisted one just skip it.
                continue;
            }
        }


        PropertyBase * prop = ent->modProperty(name);
        if (prop == nullptr) {
            prop = pm->addProperty(name, val.getType());
            prop->install(ent, name);
            //This transfers ownership of the property to the entity.
            ent->setProperty(name, prop);
        }

        //If we get to here the property either doesn't exists, or have a different value than the default or existing property.
        prop->set(val);
        prop->setFlags(per_clean | per_seen);
        prop->apply(ent);
        instanceProperties.insert(name);
    }

    if (ent->getType()) {
        for (auto& propIter : ent->getType()->defaults()) {
            if (!instanceProperties.count(propIter.first)) {
                PropertyBase * prop = propIter.second;
                // If a property is in the class it won't have been installed
                // as setAttr() checks
                prop->install(ent, propIter.first);
                // The property will have been applied if it has an overriden
                // value, so we only apply it the value is still default.
                prop->apply(ent);
            }
        }
    }


    //Now restore all properties of the child entities.
    if (ent->m_contains) {
        for (auto& childEntity : *ent->m_contains) {
            restorePropertiesRecursively(childEntity);
        }
    }

    //We must send a sight op to the entity informing it of itself before we send any thoughts.
    //Else the mind won't have any information about itself.
    {
        Atlas::Objects::Operation::Sight sight;
        sight->setTo(ent->getId());
        Atlas::Objects::Entity::Anonymous args;
        ent->addToEntity(args);
        sight->setArgs1(args);
        ent->sendWorld(sight);
    }
    //We should also send a sight op to the parent entity which owns the entity.
    //TODO: should this really be necessary or should we rely on other Sight functionality?
    if (ent->m_location.m_loc) {
        Atlas::Objects::Operation::Sight sight;
        sight->setTo(ent->m_location.m_loc->getId());
        Atlas::Objects::Entity::Anonymous args;
        ent->addToEntity(args);
        sight->setArgs1(args);
        ent->m_location.m_loc->sendWorld(sight);
    }

    restoreThoughts(ent);

}