KVElementDensity* KVElementDensityTable::FindElementBySymbol(const Char_t* X) const
{
   // Search table for an element with the given symbol. Case-insensitive.
   TString x = X;
   x.ToUpper();
   TIter next(tobj);
   KVElementDensity* elem;
   while ((elem = (KVElementDensity*)next())) {
      TString el = elem->GetElementSymbol();
      el.ToUpper();
      if (x == el) return elem;
   }
   return 0x0;
}