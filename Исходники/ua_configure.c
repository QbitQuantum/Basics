static inline bool config_add_directive(UAContext *ua, RES_TABLE *res_table, const char *key,
                                        const char *value, POOL_MEM &resource, int indent = 2)
{
   POOL_MEM temp(PM_MESSAGE);
   RES_ITEM *item = NULL;

   item = config_get_res_item(ua, res_table, key, value);
   if (res_table && (!item)) {
      return false;
   }

   /*
    * Use item->name instead of key for uniform formatting.
    */
   if (item) {
      key = item->name;
   }

   /* TODO: check type, to see if quotes should be used */
   temp.bsprintf("%-*s%s = %s\n", indent, "", key, value);
   resource.strcat(temp);

   return true;
}