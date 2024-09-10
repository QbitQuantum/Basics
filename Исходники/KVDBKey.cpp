void KVDBKey::Unlink(KVDBRecord* rec, Bool_t linkback)
{
   //This function removes a record from the list of cross-references
   //if linkback is kTRUE then the reference in record "rec" is also removed.

   RemoveLink(rec);

   if (linkback) {

      //check parent is set
      if (!GetParent()) {
         Error("Unlink", "Parent not set for key %s", GetName());
         return;
      }
      const Char_t* table_name = GetParent()->GetTable()->GetName();

      KVDBKey* key = rec->GetKey(table_name);
      if (key) key->Unlink(GetParent(), kFALSE); //linkback=kFALSE otherwise infinite circular linkage results !!!
   }
}