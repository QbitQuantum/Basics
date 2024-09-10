void ExportMultiple::MakeNameUnique(wxArrayString &otherNames, wxString &newName)
{
   if (otherNames.Index(newName, false) >= 0) {
      int i=2;
      wxString orig = newName;
      do {
         newName.Printf(wxT("%s-%d"), orig.c_str(), i);
         i++;
      } while (otherNames.Index(newName, false) >= 0);
   }
   otherNames.Add(newName);
}