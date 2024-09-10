void FindAny(bool found, const TString& fsname, TClass* cl, TString baseexpected, const char* ext, const char* tag) {

   if (baseexpected == "") {
      baseexpected = cl->GetName();
      Ssiz_t posCol = baseexpected.First('<');
      if (posCol != -1) {
         baseexpected.Remove(posCol, baseexpected.Length());
      }
      posCol = baseexpected.Last(':');
      if (posCol != -1) {
         baseexpected.Remove(0, posCol + 1);
      }
      baseexpected += ext;
   }

   if (!found) {
      if (baseexpected != "FAIL") {
         printf("FAIL: %s file for class %s not found\n", tag, cl->GetName());
      }
      return;
   } else {
      if (baseexpected == "FAIL") {
         printf("FAIL: expected to not find %s file for class %s but got %s\n",
                tag, cl->GetName(), fsname.Data());
         return;
      }
   }
   if (!fsname.EndsWith(baseexpected)) {
      printf("FAIL: class %s expected %s file %s, got %s\n",
             cl->GetName(), tag, baseexpected.Data(), fsname.Data());
      return;
   }
}