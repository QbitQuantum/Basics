 FOR_EACH (STD_VECTOR<Label*>::iterator, it, mLabels)
 {
     remove(*it);
     delete *it;
 }