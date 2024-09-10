CAMLprim value unix_getservbyport(value port, value proto)
{
  struct servent * entry;
  entry = getservbyport(htons(Int_val(port)), String_val(proto));
  if (entry == (struct servent *) NULL) raise_not_found();
  return alloc_service_entry(entry);
}