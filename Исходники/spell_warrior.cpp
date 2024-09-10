 void FilterTargets(std::list<WorldObject*>& unitList)
 {
     unitList.remove(GetExplTargetWorldObject());
 }