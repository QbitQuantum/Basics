static void
get_unique_type_string (char *string, gfc_symbol *derived)
{
  char dt_name[GFC_MAX_SYMBOL_LEN+1];
  sprintf (dt_name, "%s", derived->name);
  dt_name[0] = TOUPPER (dt_name[0]);
  if (derived->module)
    sprintf (string, "%s_%s", derived->module, dt_name);
  else if (derived->ns->proc_name)
    sprintf (string, "%s_%s", derived->ns->proc_name->name, dt_name);
  else
    sprintf (string, "_%s", dt_name);
}