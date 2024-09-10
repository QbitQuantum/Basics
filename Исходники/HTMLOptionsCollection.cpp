void
HTMLOptionsCollection::GetSupportedNames(nsTArray<nsString>& aNames)
{
  AutoTArray<nsIAtom*, 8> atoms;
  for (uint32_t i = 0; i < mElements.Length(); ++i) {
    HTMLOptionElement* content = mElements.ElementAt(i);
    if (content) {
      // Note: HasName means the names is exposed on the document,
      // which is false for options, so we don't check it here.
      const nsAttrValue* val = content->GetParsedAttr(nsGkAtoms::name);
      if (val && val->Type() == nsAttrValue::eAtom) {
        nsIAtom* name = val->GetAtomValue();
        if (!atoms.Contains(name)) {
          atoms.AppendElement(name);
        }
      }
      if (content->HasID()) {
        nsIAtom* id = content->GetID();
        if (!atoms.Contains(id)) {
          atoms.AppendElement(id);
        }
      }
    }
  }

  uint32_t atomsLen = atoms.Length();
  nsString* names = aNames.AppendElements(atomsLen);
  for (uint32_t i = 0; i < atomsLen; ++i) {
    atoms[i]->ToString(names[i]);
  }
}