bool XMLValueChecker::IsGoodFileString(wxString str)
{
   return (IsGoodString(str) && 
            !str.IsEmpty() && 

            // FILENAME_MAX is 260 in MSVC, but inconsistent across platforms, 
            // sometimes huge, but we use 260 for all platforms.
            (str.Length() <= 260) && 

            (str.Find(wxFileName::GetPathSeparator()) == -1)); // No path separator characters. 
}