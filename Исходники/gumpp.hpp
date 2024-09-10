 static std::vector<void *> find_matching_functions (const char * str)
 {
   RefPtr<PtrArray> functions = RefPtr<PtrArray> (find_matching_functions_array (str));
   std::vector<void *> result;
   for (int i = functions->length () - 1; i >= 0; i--)
     result.push_back (functions->nth (i));
   return result;
 }