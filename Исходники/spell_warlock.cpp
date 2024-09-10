 void FilterTargets(std::list<WorldObject*>& targets)
 {
     if (GetExplTargetUnit())
         targets.remove(GetExplTargetUnit());
 }