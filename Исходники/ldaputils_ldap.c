/// frees list of entries
/// @param[in] entries   list of entries to free
void ldaputils_free_entries(LDAPUtilsEntry ** entries)
{
   int  x;
   int  y;
   
   if (!(entries))
      return;
   
   for(x = 0; entries[x]; x++)
   {
      if (entries[x]->dn)
         ldap_memfree(entries[x]->dn);
      if (entries[x]->sortval)
         free(entries[x]->sortval);
      if (entries[x]->attributes)
      {
         for(y = 0; entries[x]->attributes[y]; y++)
         {
            if (entries[x]->attributes[y]->name)
               ldap_memfree(entries[x]->attributes[y]->name);
            if (entries[x]->attributes[y]->vals)
               ldap_value_free_len(entries[x]->attributes[y]->vals);
            free(entries[x]->attributes[y]);
         };
         free(entries[x]->attributes);
      };
      free(entries[x]);
   };
   free(entries);
   
   return;
}