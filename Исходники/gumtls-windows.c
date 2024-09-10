void
gum_tls_key_set_value (GumTlsKey key,
                       gpointer value)
{
  if (key < 64)
  {
    __writegsqword (0x1480 + key * sizeof (gpointer), (unsigned __int64) value);
  }
  else if (key < 1088)
  {
    gpointer * tls_expansion_slots = (gpointer) __readgsqword (0x1780);
    if (tls_expansion_slots != NULL)
      tls_expansion_slots[key - 64] = value;
    else
    {
      _gum_tls_key_set_tmp_value (key, value);
      TlsSetValue (key, value);
      _gum_tls_key_del_tmp_value (key);
    }
  }
}