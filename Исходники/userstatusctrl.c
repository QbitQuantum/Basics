int LDAP_CALL ldap_parse_userstatus_control(LDAP *ld, LDAPControl **ctrlp,
                                            LDAPuserstatus *us) {
  BerElement *ber = NULL;
  int i, foundUSControl;
  LDAPControl *USCtrlp = NULL;
  ber_tag_t tag;

  if (!NSLDAPI_VALID_LDAP_POINTER(ld) || us == NULL) {
    return (LDAP_PARAM_ERROR);
  }

  /* find the control in the list of controls if it exists */
  if (ctrlp == NULL) {
    LDAP_SET_LDERRNO(ld, LDAP_CONTROL_NOT_FOUND, NULL, NULL);
    return (LDAP_CONTROL_NOT_FOUND);
  }
  foundUSControl = 0;
  for (i = 0; ((ctrlp[i] != NULL) && (!foundUSControl)); i++) {
    foundUSControl = !strcmp(ctrlp[i]->ldctl_oid, LDAP_CONTROL_ACCOUNT_USABLE);
  }
  if (!foundUSControl) {
    LDAP_SET_LDERRNO(ld, LDAP_CONTROL_NOT_FOUND, NULL, NULL);
    return (LDAP_CONTROL_NOT_FOUND);
  } else {
    /* let local var point to the control */
    USCtrlp = ctrlp[i - 1];
  }

  /*  allocate a Ber element with the contents of the control's struct berval */
  if ((ber = ber_init(&USCtrlp->ldctl_value)) == NULL) {
    LDAP_SET_LDERRNO(ld, LDAP_NO_MEMORY, NULL, NULL);
    return (LDAP_NO_MEMORY);
  }

  memset(us, 0, sizeof(struct LDAPuserstatus));

  /*
   * The control value should look like this:
   *
   *  ACCOUNT_USABLE_RESPONSE::= CHOICE {
   *    is_available      [0] INTEGER, ** seconds before expiration **
   *    is_not_available  [1] More_info
   *  }
   *  More_info::= SEQUENCE {
   *    inactive               [0] BOOLEAN DEFAULT FALSE,
   *    reset                  [1] BOOLEAN DEFAULT FALSE,
   *    expired                [2] BOOLEAN DEFAULT FALSE,
   *    remaining_grace        [3] INTEGER OPTIONAL,
   *    seconds_before_unlock  [4] INTEGER OPTIONAL
   *  }
   */

  if ((ber_scanf(ber, "t", &tag)) == LBER_ERROR) {
    LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
    ber_free(ber, 1);
    return (LDAP_DECODING_ERROR);
  }

  tag = ((tag & LBER_CONSTRUCTED) == LBER_CONSTRUCTED) ? 1 : 0;

  if (!tag) {
    us->us_available = 1;
    if (ber_scanf(ber, "i", &us->us_expire) == LBER_ERROR) {
      LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
      ber_free(ber, 1);
      return (LDAP_DECODING_ERROR);
    }
  } else {
    us->us_available = 0;
    tag = 0;
    if ((ber_scanf(ber, "{t", &tag)) == LBER_ERROR) {
      LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
      ber_free(ber, 1);
      return (LDAP_DECODING_ERROR);
    }
    while (tag != LBER_ERROR && tag != LBER_END_OF_SEQORSET) {
      tag = tag & (~LBER_CLASS_CONTEXT);
      switch (tag) {
        case 0:
          if (ber_scanf(ber, "b", &us->us_inactive) == LBER_ERROR) {
            LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
            ber_free(ber, 1);
            return (LDAP_DECODING_ERROR);
          }
          us->us_inactive = (us->us_inactive != 0) ? 1 : 0;
          break;
        case 1:
          if (ber_scanf(ber, "b", &us->us_reset) == LBER_ERROR) {
            LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
            ber_free(ber, 1);
            return (LDAP_DECODING_ERROR);
          }
          us->us_reset = (us->us_reset != 0) ? 1 : 0;
          break;
        case 2:
          if (ber_scanf(ber, "b", &us->us_expired) == LBER_ERROR) {
            LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
            ber_free(ber, 1);
            return (LDAP_DECODING_ERROR);
          }
          us->us_expired = (us->us_expired != 0) ? 1 : 0;
          break;
        case 3:
          if (ber_scanf(ber, "i", &us->us_remaining) == LBER_ERROR) {
            LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
            ber_free(ber, 1);
            return (LDAP_DECODING_ERROR);
          }
          break;
        case 4:
          if (ber_scanf(ber, "i", &us->us_seconds) == LBER_ERROR) {
            LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
            ber_free(ber, 1);
            return (LDAP_DECODING_ERROR);
          }
          break;
        default:
          LDAP_SET_LDERRNO(ld, LDAP_DECODING_ERROR, NULL, NULL);
          ber_free(ber, 1);
          return (LDAP_DECODING_ERROR);
      }
      ber_scanf(ber, "t", &tag);
    }
  }

  /* the ber encoding is no longer needed */
  ber_free(ber, 1);
  return (LDAP_SUCCESS);
}