int
ipmi_cipher_suite_id_to_algorithms (uint8_t cipher_suite_id,
                                    uint8_t *authentication_algorithm,
                                    uint8_t *integrity_algorithm,
                                    uint8_t *confidentiality_algorithm)
{
  uint8_t a, i, c;

  /* To avoid gcc warnings, add +1 to comparison */
  if (!((cipher_suite_id + 1) >= 1
	&& cipher_suite_id <= 19))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (cipher_suite_id == 0)
    a = IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE;
  else if (cipher_suite_id >= 1 && cipher_suite_id <= 5)
    a = IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1;
  else if (cipher_suite_id >= 6 && cipher_suite_id <= 14)
    a = IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5;
  else /* cipher_suite_id >= 15 && cipher_suite_id <= 19 */
    a = IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256;

  if (cipher_suite_id == 0
      || cipher_suite_id == 1
      || cipher_suite_id == 6
      || cipher_suite_id == 15)
    i = IPMI_INTEGRITY_ALGORITHM_NONE;
  else if (cipher_suite_id >= 2 && cipher_suite_id <= 5)
    i = IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96;
  else if (cipher_suite_id >= 7 && cipher_suite_id <= 10)
    i = IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128;
  else if (cipher_suite_id >= 11 && cipher_suite_id <= 14)
    i = IPMI_INTEGRITY_ALGORITHM_MD5_128;
  else /* cipher_suite_id >= 16 && cipher_suite_id <= 19 */
    i = IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128;

  if (cipher_suite_id == 0
      || cipher_suite_id == 1
      || cipher_suite_id == 2
      || cipher_suite_id == 6
      || cipher_suite_id == 7
      || cipher_suite_id == 11
      || cipher_suite_id == 15
      || cipher_suite_id == 16)
    c = IPMI_CONFIDENTIALITY_ALGORITHM_NONE;
  else if (cipher_suite_id == 3
           || cipher_suite_id == 8
           || cipher_suite_id == 12
           || cipher_suite_id == 17)
    c = IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128;
  else if (cipher_suite_id == 4
           || cipher_suite_id == 9
           || cipher_suite_id == 13
           || cipher_suite_id == 18)
    c = IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128;
  else /* cipher_suite_id == 5
          || cipher_suite_id == 10
          || cipher_suite_id == 14
          || cipher_suite_id == 19 */
    c = IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40;

  if (authentication_algorithm)
    *authentication_algorithm = a;
  if (integrity_algorithm)
    *integrity_algorithm = i;
  if (confidentiality_algorithm)
    *confidentiality_algorithm = c;

  return (0);
}