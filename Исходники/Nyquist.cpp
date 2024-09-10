wxString EffectNyquist::UnQuote(wxString s)
{
   wxString out;
   int len = s.Length();
   
   if (len >= 2 && s[0] == wxT('\"') && s[len - 1] == wxT('\"')) {
      return s.Mid(1, len - 2);
   }

   return s;
}