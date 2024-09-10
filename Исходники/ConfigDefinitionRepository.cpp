 void ConfigDefinitionRepository::remove(ConfigDefinitionPtr def)
 {
    mDefs.erase(def->getToken());
 }