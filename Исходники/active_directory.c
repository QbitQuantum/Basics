/* 
convert a distinguished name into the domain controller
dns domain, eg: "ou=users,dc=example,dc=com" returns
"example.com".
memory allocated should be returned with free()
*/
char *dn2domain(char *dn) {
	char **exp_dn;
	int i;
	char *dc;

	dc=malloc(1024);
	dc[0]='\0';
	exp_dn=ldap_explode_dn(dn, 0);
	for(i=0; exp_dn[i]!=NULL; i++) {
		if(!strncasecmp("dc=", exp_dn[i], 3)) {
			strncat(dc, exp_dn[i]+3, 1024);
			strncat(dc, ".", 1024);
		}
	}
	ldap_value_free(exp_dn);
	i=strlen(dc);
	if(i>0) dc[i-1]='\0';
	for(i=0; dc[i]!='\0'; i++) dc[i]=tolower(dc[i]);
	return dc;
}