 void FilterTargets(std::list<WorldObject*>& targets)
 {
     targets.remove(GetExplTargetUnit()); // The target of this spell should _not_ be in this list
 }