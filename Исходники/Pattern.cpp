/**
 * Returns 1 if the given DELAF entry is compatible with the given pattern;
 * 0 otherwise.
 */
int is_entry_compatible_with_pattern(const struct dela_entry* entry,const struct pattern* pattern) {
switch(pattern->type) {
   case LEMMA_PATTERN: return (!u_strcmp(entry->lemma,pattern->lemma));
   case CODE_PATTERN: return is_compatible_code_pattern(entry,pattern);
   case LEMMA_AND_CODE_PATTERN: return (!u_strcmp(entry->lemma,pattern->lemma)) && is_compatible_code_pattern(entry,pattern);
   case FULL_PATTERN: return (!u_strcmp(entry->inflected,pattern->inflected)) && (!u_strcmp(entry->lemma,pattern->lemma)) && is_compatible_code_pattern(entry,pattern);
   case AMBIGUOUS_PATTERN: return !u_strcmp(entry->lemma,pattern->lemma) || dic_entry_contain_gram_code(entry,pattern->lemma);
   case INFLECTED_AND_LEMMA_PATTERN: return (!u_strcmp(entry->inflected,pattern->inflected)) && (!u_strcmp(entry->lemma,pattern->lemma));
      default: fatal_error("Unexpected case in is_entry_compatible_with_pattern\n");
}
return 0;
}