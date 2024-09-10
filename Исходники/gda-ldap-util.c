static GdaLdapClass *
worker_gdaprov_ldap_get_class_info (WorkerLdapClassInfoData *data, GError **error)
{
	GdaLdapClass *retval = NULL;

	/* initialize known classes */
	data->cdata->classes_hash = g_hash_table_new_full (g_str_hash, g_str_equal,
							   NULL,
							   (GDestroyNotify) ldap_class_free);

	LDAPMessage *msg, *entry;
	int res;
	gchar *subschema = NULL;

	char *subschemasubentry[] = {"subschemaSubentry", NULL};
	char *schema_attrs[] = {"objectClasses", NULL};
	
	/* look for subschema */
	if (! gda_ldap_ensure_bound (data->cnc, NULL))
		return NULL;

	gda_ldap_execution_slowdown (data->cnc);
	res = ldap_search_ext_s (data->cdata->handle, "", LDAP_SCOPE_BASE,
				 "(objectclass=*)",
				 subschemasubentry, 0,
				 NULL, NULL, NULL, 0,
				 &msg);
	if (res != LDAP_SUCCESS) {
		gda_ldap_may_unbind (data->cnc);
		return NULL;
	}

	if ((entry = ldap_first_entry (data->cdata->handle, msg))) {
		char *attr;
		BerElement *ber;
		if ((attr = ldap_first_attribute (data->cdata->handle, entry, &ber))) {
			BerValue **bvals;
			if ((bvals = ldap_get_values_len (data->cdata->handle, entry, attr))) {
				subschema = g_strdup (bvals[0]->bv_val);
				ldap_value_free_len (bvals);
			}
			ldap_memfree (attr);
		}
		if (ber)
			ber_free (ber, 0);
	}
	ldap_msgfree (msg);

	if (! subschema) {
		gda_ldap_may_unbind (data->cnc);
		return NULL;
	}

	/* look for attributeTypes */
	gda_ldap_execution_slowdown (data->cnc);
	res = ldap_search_ext_s (data->cdata->handle, subschema, LDAP_SCOPE_BASE,
				 "(objectclass=*)",
				 schema_attrs, 0,
				 NULL, NULL, NULL, 0,
				 &msg);
	g_free (subschema);
	if (res != LDAP_SUCCESS) {
		gda_ldap_may_unbind (data->cnc);
		return NULL;
	}

	GHashTable *h_refs;
	h_refs = g_hash_table_new_full (NULL, NULL, NULL, (GDestroyNotify) g_strfreev);
	for (entry = ldap_first_entry (data->cdata->handle, msg);
	     entry;
	     entry = ldap_next_entry (data->cdata->handle, msg)) {
		char *attr;
		BerElement *ber;
		for (attr = ldap_first_attribute (data->cdata->handle, msg, &ber);
		     attr;
		     attr = ldap_next_attribute (data->cdata->handle, msg, ber)) {
			if (strcasecmp(attr, "objectClasses")) {
				ldap_memfree (attr);
				continue;
			}

			BerValue **bvals;
			bvals = ldap_get_values_len (data->cdata->handle, entry, attr);
			if (bvals) {
				gint i;
				for (i = 0; bvals[i]; i++) {
					LDAPObjectClass *oc;
					const char *errp;
					int retcode;
					oc = ldap_str2objectclass (bvals[i]->bv_val, &retcode,
								   &errp,
								   LDAP_SCHEMA_ALLOW_ALL);
					if (oc && oc->oc_oid && oc->oc_names && oc->oc_names[0]) {
						GdaLdapClass *lcl;
						guint k;
						lcl = g_new0 (GdaLdapClass, 1);
						lcl->oid = g_strdup (oc->oc_oid);
//#define CLASS_DEBUG
#ifdef CLASS_DEBUG
						g_print ("FOUND CLASS\n");
#endif
						lcl->names = make_array_from_strv (oc->oc_names,
										   &(lcl->nb_names));
						for (k = 0; lcl->names[k]; k++) {
#ifdef CLASS_DEBUG
							g_print ("  oc_names[%d] = %s\n",
								 k, lcl->names[k]);
#endif
							g_hash_table_insert (data->cdata->classes_hash,
									     lcl->names[k],
									     lcl);
						}
						if (oc->oc_desc) {
#ifdef CLASS_DEBUG
							g_print ("  oc_desc = %s\n", oc->oc_desc);
#endif
							lcl->description = g_strdup (oc->oc_desc);
						}
#ifdef CLASS_DEBUG
						g_print ("  oc_kind = %d\n", oc->oc_kind);
#endif
						switch (oc->oc_kind) {
						case 0:
							lcl->kind = GDA_LDAP_CLASS_KIND_ABSTRACT;
							break;
						case 1:
							lcl->kind = GDA_LDAP_CLASS_KIND_STRUTURAL;
							break;
						case 2:
							lcl->kind = GDA_LDAP_CLASS_KIND_AUXILIARY;
							break;
						default:
							lcl->kind = GDA_LDAP_CLASS_KIND_UNKNOWN;
							break;
						}
						lcl->obsolete = oc->oc_obsolete;
#ifdef CLASS_DEBUG
						g_print ("  oc_obsolete = %d\n", oc->oc_obsolete);

#endif
						gchar **refs;
						refs = make_array_from_strv (oc->oc_sup_oids, NULL);
						if (refs)
							g_hash_table_insert (h_refs, lcl, refs);
						else
							data->cdata->top_classes = g_slist_insert_sorted (data->cdata->top_classes,
									     lcl, (GCompareFunc) classes_sort);
#ifdef CLASS_DEBUG
						for (k = 0; oc->oc_sup_oids && oc->oc_sup_oids[k]; k++)
							g_print ("  oc_sup_oids[0] = %s\n",
								 oc->oc_sup_oids[k]);
#endif

						lcl->req_attributes =
							make_array_from_strv (oc->oc_at_oids_must,
									      &(lcl->nb_req_attributes));
#ifdef CLASS_DEBUG
						for (k = 0; oc->oc_at_oids_must && oc->oc_at_oids_must[k]; k++)
							g_print ("  oc_at_oids_must[0] = %s\n",
								 oc->oc_at_oids_must[k]);
#endif
						lcl->opt_attributes =
							make_array_from_strv (oc->oc_at_oids_may,
									      &(lcl->nb_opt_attributes));
#ifdef CLASS_DEBUG
						for (k = 0; oc->oc_at_oids_may && oc->oc_at_oids_may[k]; k++)
							g_print ("  oc_at_oids_may[0] = %s\n",
								 oc->oc_at_oids_may[k]);
#endif
						  
					}
					if (oc)
						ldap_memfree (oc);
				}
				ldap_value_free_len (bvals);
			}
			  
			ldap_memfree (attr);
		}
		if (ber)
			ber_free (ber, 0);
	}
	ldap_msgfree (msg);

	/* create hierarchy */
	g_hash_table_foreach (h_refs, (GHFunc) classes_h_func, data->cdata);
	g_hash_table_destroy (h_refs);

	retval = g_hash_table_lookup (data->cdata->classes_hash, data->classname);
	gda_ldap_may_unbind (data->cnc);
	return retval;
}