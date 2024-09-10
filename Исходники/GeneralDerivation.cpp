int check_is_valid_for_one_INF_code(const unichar* t, const unichar* s)
{
  unichar temp[MAX_DICT_LINE_LENGTH];
  u_strcpy(temp,"x,");
  u_strcat(temp,s);
  struct dela_entry* d = tokenize_DELAF_line(temp,0);
  int res = check_is_valid(t, d);
  free_dela_entry(d);
  return res;
}