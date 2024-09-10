 // return a hash of a calltip context (to avoid storing strings of each calltip)
 // used in m_CallTipChoiceDict and m_CallTipFuzzyChoiceDict
 static int CallTipToInt(const wxString& firstTip, int numPages)
 {
     int val = 33 * firstTip.Length() ^ numPages;
     for (wxString::const_iterator itr = firstTip.begin();
          itr != firstTip.end(); ++itr)
     {
         val = 33 * val ^ static_cast<int>(*itr);
     }
     return val;
 }