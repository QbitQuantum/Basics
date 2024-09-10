static snmp_err_t 
system_set_value(const struct snmp_scalar_array_node_def *node, u16_t len, void *value)
{
  u8_t*  var_wr = NULL;
  u16_t* var_wr_len;

  switch (node->oid) {
  case 4: /* sysContact */
    var_wr     = syscontact_wr;
    var_wr_len = syscontact_wr_len;
    break;
  case 5: /* sysName */
    var_wr     = sysname_wr;
    var_wr_len = sysname_wr_len;
    break;
  case 6: /* sysLocation */
    var_wr     = syslocation_wr;
    var_wr_len = syslocation_wr_len;
    break;
  default:
    LWIP_DEBUGF(SNMP_MIB_DEBUG,("system_set_value(): unknown id: %"S32_F"\n", node->oid));
    return SNMP_ERR_GENERROR;
  }

  /* no need to check size of target buffer, this was already done in set_test method */
  LWIP_ASSERT("", var_wr != NULL);
  MEMCPY(var_wr, value, len);
  
  if (var_wr_len == NULL) {
    /* add terminating 0 */
    var_wr[len] = 0;
  } else {
    *var_wr_len = len;
  }

  return SNMP_ERR_NOERROR;
}