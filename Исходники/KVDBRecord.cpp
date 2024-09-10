void KVDBRecord::RemoveLink(const Char_t* key_name, KVDBRecord* rec,
                            Bool_t linkback)
{
   //Remove the link between this record and the record "rec" in the DB table"key_name"

   KVDBKey* key = GetKey(key_name);
   if (key)
      key->Unlink(rec, linkback);
   else {
      TObject::Warning("RemoveLink(const Char_t*,KVDBRecord*)",
                       "No key named %s found.", key_name);
   }

}