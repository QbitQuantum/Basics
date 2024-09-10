bool SpecialCaseList::findCategory(const GlobalVariable &G,
                                   StringRef &Category) const {
  return findCategory(*G.getParent(), Category) ||
         findCategory("global", G.getName(), Category) ||
         findCategory("type", GetGVTypeString(G), Category);
}