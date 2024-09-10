static WORD 
pdhservice_get_system_primary_lang_id(void)
{
   LANGID lang_id = GetSystemDefaultUILanguage();
   WORD prim_lang_id = PRIMARYLANGID(lang_id);

   return prim_lang_id;
}