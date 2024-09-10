int ldap_parse_passwordpolicy_control(LDAP UNUSED(*ld), LDAPControl *ctrl,
                                      ber_int_t *expirep, ber_int_t *gracep,
                                      LDAPPasswordPolicyError UNUSED(*errorp))
{
  BerElement *ber;
  ber_tag_t tag;
  ber_len_t berLen;
  char *last;
#ifdef HAVE_BER_GET_ENUM
  int err = PP_noError;
#endif /* HAVE_BER_GET_ENUM */
  /* get a BerElement from the control */
  ber = ber_init(&ctrl->ldctl_value);
  if (ber == NULL)
    return LDAP_LOCAL_ERROR;
  /* go over tags */
  for(tag = ber_first_element(ber, &berLen, &last); tag != LBER_DEFAULT; tag = ber_next_element(ber, &berLen, last))
  {
    switch (tag)
    {
      case PPOLICY_WARNING:
        ber_skip_tag(ber, &berLen);
        tag = ber_peek_tag(ber, &berLen);
        switch (tag)
        {
          case PPOLICY_EXPIRE:
            if (ber_get_int(ber, expirep) == LBER_DEFAULT)
            {
              ber_free(ber, 1);
              return LDAP_DECODING_ERROR;
            }
            break;
          case PPOLICY_GRACE:
            if (ber_get_int(ber, gracep) == LBER_DEFAULT)
            {
              ber_free(ber, 1);
              return LDAP_DECODING_ERROR;
            }
            break;
          default:
            ber_free(ber, 1);
            return LDAP_DECODING_ERROR;
        }
        break;
#ifdef HAVE_BER_GET_ENUM
      case PPOLICY_ERROR:
        if (ber_get_enum(ber, &err) == LBER_DEFAULT)
        {
          ber_free(ber, 1);
          return LDAP_DECODING_ERROR;
        }
        break;
#endif /* HAVE_BER_GET_ENUM */
      default:
        ber_free(ber, 1);
        return LDAP_DECODING_ERROR;
    }
  }
  ber_free(ber, 1);
  return LDAP_SUCCESS;
}