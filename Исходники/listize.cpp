 Expression* Listize::operator()(Selector_List* sel)
 {
   List* l = SASS_MEMORY_NEW(mem, List, sel->pstate(), sel->length(), SASS_COMMA);
   for (size_t i = 0, L = sel->length(); i < L; ++i) {
     if (!(*sel)[i]) continue;
     *l << (*sel)[i]->perform(this);
   }
   if (l->length()) return l;
   return SASS_MEMORY_NEW(mem, Null, l->pstate());
 }