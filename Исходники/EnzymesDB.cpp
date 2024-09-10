 void EnzymesDB::addEnzyme_(const Enzyme* r)
 {
   // add to internal storage
   const_enzymes_.insert(r);
   // add to internal indices (by name and its synonyms)
   String name = r->getName();
   enzyme_names_[name] = r;
   enzyme_names_[name.toLower()] = r;
   for (set<String>::const_iterator it = r->getSynonyms().begin(); it != r->getSynonyms().end(); ++it)
   {
     enzyme_names_[*it] = r;
   }
   // ... and by regex
   if (r->getRegEx() != "")
   {
     enzyme_regex_[r->getRegEx()] = r;
   }    
   return;
 }