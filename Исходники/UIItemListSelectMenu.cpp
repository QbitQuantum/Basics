// Return index of next level starting with specified string; if none exists, returns current index.
// If startingWith is only one character, the entry we're looking for could be behind us.  See tests
// for examples of this.
S32 ItemListSelectUserInterface::getIndexOfNext(const string &startingWithLc) const
{
   TNLAssert(startingWithLc.length() > 0, "Did not expect an empty string here!");
   TNLAssert(startingWithLc == lcase(startingWithLc), "Expected a lowercased string here");

   bool first = true;
   bool multiChar = startingWithLc.length() > 1;
   S32 offset = multiChar ? 0 : 1;

   // Loop until we hit the end of the list, or we hit an item that sorts > our startingString (meaning we overshot).
   // But we only care about overshoots in multiChar mode because there could well be single-char hits behind us in the list.
   while(true)
   {
      if(mSelectedIndex + offset >= getMenuItemCount())    // Hit end of list -- loop to beginning
         offset = -mSelectedIndex;

      string prospectiveItem = lcase(getMenuItem(mSelectedIndex + offset)->getValue());

      if(prospectiveItem.substr(0, startingWithLc.size()) == startingWithLc)
         return mSelectedIndex + offset;

      if(offset == 0 && !first)
         break;

      offset++;
      first = false;
   }

   // Found no match; return current index
   return mSelectedIndex;
}