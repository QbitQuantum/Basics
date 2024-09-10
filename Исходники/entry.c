VALUE
rb_ldap_entry_new (LDAP * ldap, LDAPMessage * msg)
{
  VALUE val;
  RB_LDAPENTRY_DATA *edata;
  char *c_dn;

  val = Data_Make_Struct (rb_cLDAP_Entry, RB_LDAPENTRY_DATA,
			  rb_ldap_entry_mark, rb_ldap_entry_free, edata);
  edata->ldap = ldap;
  edata->msg = msg;

  /* get dn */
  c_dn = ldap_get_dn(ldap, msg);
  if (c_dn) {
    edata->dn = rb_tainted_str_new2(c_dn);
    ldap_memfree(c_dn);
  }
  else {
    edata->dn = Qnil;
  }

  /* get attributes */
  edata->attr = rb_ldap_entry_load_attr(ldap, msg);
  return val;
}