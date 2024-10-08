   /* Creates new LDAP Account */
   int db_create(char *bid, char *username, char *first, char *last, char *pass) {

      /* declares local vars */
         LDAP *ld;
         LDAPMessage *res;
         LDAPMod **mods;
         char filter[1024];
         int i;
         int bid_len;
         char *dn;
         char *uid;

      /* checks for connection */
         if (db_pointer) {
            ld = db_pointer;
           } else {
            return(1);
         };

      /* Gets size of bid */
         bid_len = strlen(bid);

      /* Creates filter */
         strcpy(filter, "(blipsid=");
         strcpy(filter+9, bid);
         strcpy(filter+9+bid_len, ")");
         if (ldap_search_s(ld, "o=acsalaska.net", LDAP_SCOPE_SUBTREE, filter, NULL, 0, &res)) {
            ldap_perror(ld, "ldap_search_s");
            return(1);
         };


      /* Checks for results */
         if (ldap_count_entries(ld, res)) {
            ldap_msgfree(res);
            return(2);
         };
         ldap_msgfree(res);
         res = NULL;


      /* Generates DN */
         dn = (char *) db_dn(username);
         if (!dn) {
            return(1);
         };

      /* Searches for existing username */
         if (ldap_search_s(ld, dn, LDAP_SCOPE_SUBTREE, "(uid=*)", NULL, 0, &res) != LDAP_NO_SUCH_OBJECT) {
            ldap_perror(ld, "ldap_search_s");
            free(dn);
            return(1);
         };

      /* Checks for results */
         if (ldap_count_entries(ld, res)) {
            ldap_msgfree(res);
            return(3);
         };
         ldap_msgfree(res);

      /* gets UID of account */
         uid = strtok(username, "@");

      /* Creates mod pointers */
         mods = (LDAPMod **) malloc (9*sizeof(LDAPMod *));
         if (!mods) {
            return(1);
         };
         memset(mods, 0, (8*sizeof(LDAPMod *)));
         for(i = 0; i < 8; i++) {
            mods[i] = (LDAPMod *) malloc(sizeof(LDAPMod));
            if (!mods[i]) {
               for(i = i; i >= 0; i--)
                  free(mods[i]);
               free(mods);
               return(1);
            };
         };

      /* Creates mod entries */
         mods[0]->mod_op = 0;
         mods[0]->mod_type = (char *) strdup("objectclass");
         mods[0]->mod_values = (char **) malloc(sizeof(char *)*8);
         mods[0]->mod_values[0] = (char *) strdup("top");
         mods[0]->mod_values[1] = (char *) strdup("person");
         mods[0]->mod_values[2] = (char *) strdup("organizationalperson");
         mods[0]->mod_values[3] = (char *) strdup("inetorgperson");
         mods[0]->mod_values[4] = (char *) strdup("inetuser");
         mods[0]->mod_values[5] = (char *) strdup("acsaccount");
         mods[0]->mod_values[6] = (char *) strdup("acsblipsaccount");
         mods[0]->mod_values[7] = NULL;

         mods[1]->mod_op = 0;
         mods[1]->mod_type = (char *) strdup("uid");
         mods[1]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[1]->mod_values[0] = uid;
         mods[1]->mod_values[1] = NULL;

         mods[2]->mod_op = 0;
         mods[2]->mod_type = (char *) strdup("datasource");
         mods[2]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[2]->mod_values[0] = (char *) strdup("Backend LDAP Internet Provisioning System Daemon");
         mods[2]->mod_values[1] = NULL;

         mods[3]->mod_op = 0;
         mods[3]->mod_type = (char *) strdup("givenname");
         mods[3]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[3]->mod_values[0] = first;
         mods[3]->mod_values[1] = NULL;

         mods[4]->mod_op = 0;
         mods[4]->mod_type = (char *) strdup("sn");
         mods[4]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[4]->mod_values[0] = last;
         mods[4]->mod_values[1] = NULL;

         mods[5]->mod_op = 0;
         mods[5]->mod_type = (char *) strdup("cn");
         mods[5]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[5]->mod_values[0] = (char *) strdup("First Last");
         mods[5]->mod_values[1] = NULL;

         mods[6]->mod_op = 0;
         mods[6]->mod_type = (char *) strdup("clearpassword");
         mods[6]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[6]->mod_values[0] = pass;
         mods[6]->mod_values[1] = NULL;

         mods[7]->mod_op = 0;
         mods[7]->mod_type = (char *) strdup("userpassword");
         mods[7]->mod_values = (char **) malloc(sizeof(char *)*2);
         mods[7]->mod_values[0] = pass;
         mods[7]->mod_values[1] = NULL;

         mods[8] = NULL;


      /* Creates the account in LDAP */
         if (ldap_add_s(ld, dn, mods)) {
            ldap_perror(ld, "ldap_add_s");
            free(dn);
            ldap_mods_free(mods, 9);
            return(1);
         };
         ldap_perror(ld, "ldap_add_s");

      /* ends function */
fprintf(stderr, "got here 98\n");
         free(dn);
fprintf(stderr, "got here 99\n");
         //ldap_mods_free(mods, 9);
fprintf(stderr, "got here 100\n");
         return(0);

   }