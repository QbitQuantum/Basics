/*
 * controlType = LDAP_CONTROL_PAGEDRESULTS;
 * criticality = n/a;
 * controlValue:
 *   realSearchControlValue ::= SEQUENCE {
 *   size INTEGER (0..maxInt),
 *   -- requested page size from client
 *   -- result set size estimate from server
 *   cookie OCTET STRING
 *   }
 */
void
pagedresults_set_response_control( Slapi_PBlock *pb, int iscritical,
                                   ber_int_t estimate, int current_search_count,
                                   int index )
{
    LDAPControl **resultctrls = NULL;
    LDAPControl pr_respctrl;
    BerElement *ber = NULL;
    struct berval *berval = NULL;
    char *cookie_str = NULL;
    int found = 0;
    int i;

    LDAPDebug1Arg(LDAP_DEBUG_TRACE,
                  "--> pagedresults_set_response_control: idx=%d\n", index);

    if ( (ber = der_alloc()) == NULL )
    {
        goto bailout;
    }

    /* begin sequence, payload, end sequence */
    if (current_search_count < 0) {
        cookie_str = slapi_ch_strdup("");
    } else {
        cookie_str = slapi_ch_smprintf("%d", index);
    }
    ber_printf ( ber, "{io}", estimate, cookie_str, strlen(cookie_str) );
    if ( ber_flatten ( ber, &berval ) != LDAP_SUCCESS )
    {
        goto bailout;
    }
    pr_respctrl.ldctl_oid = LDAP_CONTROL_PAGEDRESULTS;
    pr_respctrl.ldctl_iscritical = iscritical;
    pr_respctrl.ldctl_value.bv_val = berval->bv_val;
    pr_respctrl.ldctl_value.bv_len = berval->bv_len;

    slapi_pblock_get ( pb, SLAPI_RESCONTROLS, &resultctrls );
    for (i = 0; resultctrls && resultctrls[i]; i++)
    {
        if (strcmp(resultctrls[i]->ldctl_oid, LDAP_CONTROL_PAGEDRESULTS) == 0)
        {
            /*
             * We get here if search returns more than one entry
             * and this is not the first entry.
             */
            ldap_control_free ( resultctrls[i] );
            resultctrls[i] = slapi_dup_control (&pr_respctrl);
            found = 1;
            break;
        }
    }

    if ( !found )
    {
        /* slapi_pblock_set() will dup the control */
        slapi_pblock_set ( pb, SLAPI_ADD_RESCONTROL, &pr_respctrl );
    }

bailout:
    slapi_ch_free_string(&cookie_str);
    ber_free ( ber, 1 );      /* ber_free() checks for NULL param */
    ber_bvfree ( berval );    /* ber_bvfree() checks for NULL param */

    LDAPDebug1Arg(LDAP_DEBUG_TRACE,
                  "<-- pagedresults_set_response_control: idx=%d\n", index);
}