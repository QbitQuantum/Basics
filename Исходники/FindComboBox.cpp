   /// <summary>Check whether listBox contains a specified string</summary>
   /// <param name="str">The string.</param>
   /// <param name="matchCase">match case.</param>
   /// <returns></returns>
   bool  FindComboBox::Contains(const wstring& str, bool matchCase) const
   {
      auto list = GetAllStrings();

      // Query strings in listBox
      return any_of(list.begin(), list.end(), [&str,matchCase](const wstring& s) {
         return matchCase ? s == str : StrCmpI(s.c_str(), str.c_str()) == 0;
      });
   }