/* Initialize LDAP Conn */
void
init_ldap_conn ()
{
  int result;
  conn = ldap_open (ldapsystem, LDAP_PORT);
  if (conn == NULL)
    {
      fprintf (stderr, "Error opening Ldap connection: %s\n",
	       strerror (errno));
      exit (-1);
    }

  result = ldap_simple_bind_s (conn, binddn, bindpw);
  ldap_result_check ("ldap_simple_bind_s", "LDAP Bind", result);
}