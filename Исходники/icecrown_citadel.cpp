 // First effect
 void CountTargets(std::list<Unit*>& unitList)
 {
     unitList.remove(GetCaster());
     failed = unitList.empty();
 }