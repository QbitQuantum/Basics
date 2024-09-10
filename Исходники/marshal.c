/** Unmarshals the next content of an MBuffer into a OmlValue
 *
 * \param mbuf MBuffer to read from
 * \param value pointer to OmlValue to unmarshall the read data into
 * \return 1 if successful, 0 otherwise
 */
int
unmarshal_value(MBuffer *mbuf, OmlValue *value)
{
  if (mbuf_rd_remaining(mbuf) == 0) {
    logerror("Tried to unmarshal a value from the buffer, but didn't receive enough data to do that\n");
    return 0;
  }

  int type = mbuf_read_byte (mbuf);
  if (type == -1) return 0;

  switch (type) {
  case LONG_T: {
    uint8_t buf [LONG_T_SIZE];

    if (mbuf_read (mbuf, buf, LENGTH (buf)) == -1)
    {
      logerror("Failed to unmarshal OML_LONG_VALUE; not enough data?\n");
      return 0;
    }

    uint32_t hv = ntohl(*((uint32_t*)buf));
    int32_t v = (int32_t)(hv);

    /*
     * The server no longer needs to know about OML_LONG_VALUE, as the
     * marshalling process now maps OML_LONG_VALUE into OML_INT32_VALUE
     * (by truncating to [INT_MIN, INT_MAX].  Therefore, unmarshall a
     * LONG_T value into an OML_INT32_VALUE object.
     */
    oml_value_set_type(value, OML_INT32_VALUE);
    omlc_set_int32(*oml_value_get_value(value), v);
    break;
  }
  case INT32_T:
  case UINT32_T:
  case INT64_T:
  case UINT64_T: {
    uint8_t buf [UINT64_T_SIZE]; // Maximum integer size
    OmlValueT oml_type = protocol_type_map[type];
    if (mbuf_read (mbuf, buf, protocol_size_map[type]) == -1) {
      logerror("Failed to unmarshall %d value; not enough data?\n", type);
      return 0;
    }
    oml_value_set_type(value, oml_type);
    switch (type) {
    case INT32_T:
      omlc_set_int32(*oml_value_get_value(value), ntohl(*((int32_t*)buf)));
      logdebug3("Unmarshalled %s %" PRId32 "\n", oml_type_to_s(oml_type), omlc_get_int32(*oml_value_get_value(value)));
      break;

    case UINT32_T:
      omlc_set_uint32(*oml_value_get_value(value), ntohl(*((uint32_t*)buf)));
      logdebug3("Unmarshalled %s %" PRIu32 "\n", oml_type_to_s(oml_type), omlc_get_uint32(*oml_value_get_value(value)));
      break;

    case INT64_T:
      omlc_set_int64(*oml_value_get_value(value), ntohll(*((int64_t*)buf)));
      logdebug3("Unmarshalled %s %" PRId64 "\n", oml_type_to_s(oml_type), omlc_get_int64(*oml_value_get_value(value)));
      break;

    case UINT64_T:
      omlc_set_uint64(*oml_value_get_value(value), ntohll(*((uint64_t*)buf)));
      logdebug3("Unmarshalled %s %" PRIu64 "\n", oml_type_to_s(oml_type), omlc_get_uint64(*oml_value_get_value(value)));
      break;

    default:
      logerror("Integer morphed, something magic has just happened\n");
      return 0;
    }
    break;
  }
  case DOUBLE_T: {
    uint8_t buf [DOUBLE_T_SIZE];
    OmlValueT oml_type = protocol_type_map[type];
    if (mbuf_read (mbuf, buf, LENGTH (buf)) == -1)
    {
      logerror("Failed to unmarshal OML_DOUBLE_VALUE; not enough data?\n");
      return 0;
    }

    int hmant = (int)ntohl(*((uint32_t*)buf));
    double mant = hmant * 1.0 / (1 << BIG_L);
    int exp = (int8_t) buf[4];
    double v = ldexp(mant, exp);
    oml_value_set_type(value, oml_type);
    omlc_set_double(*oml_value_get_value(value), v);
    logdebug3("Unmarshalled double %f\n", omlc_get_double(*oml_value_get_value(value)));
    break;
  }
  case DOUBLE_NAN: {
    OmlValueT oml_type = protocol_type_map[type];
    mbuf_read_skip(mbuf, DOUBLE_T_SIZE); /* The data is irrelevant */
    oml_value_set_type(value, oml_type);
    omlc_set_double(*oml_value_get_value(value), NAN);
    logdebug("Received NaN\n");
    break;
  }
  case STRING_T: {
    int len = 0;
    uint8_t buf [STRING_T_MAX_SIZE];

    len = mbuf_read_byte (mbuf);

    if (len == -1 || mbuf_read (mbuf, buf, len) == -1)
    {
      logerror("Failed to unmarshal OML_STRING_VALUE; not enough data?\n");
      return 0;
    }

    oml_value_set_type(value, OML_STRING_VALUE);
    omlc_set_string_copy(*oml_value_get_value(value), buf, len);
    logdebug3("Unmarshalled string '%s' of length %d\n", omlc_get_string_ptr(*oml_value_get_value(value)), len);
    break;
  }
  case BLOB_T: {
    uint32_t n_len;

    if (mbuf_read (mbuf, (uint8_t*)&n_len, 4) == -1) {
      logerror ("Failed to unmarshal OML_BLOB_VALUE length field; not enough data?\n");
      return 0;
    }

    size_t len = ntohl (n_len);
    size_t remaining = mbuf_rd_remaining (mbuf);

    if (len > remaining) {
      logerror ("Failed to unmarshal OML_BLOB_VALUE data:  not enough data available "
                "(wanted %d, but only have %d bytes\n",
                len, remaining);
      return 0;
    }

    void *ptr = mbuf_rdptr (mbuf);
    oml_value_set_type(value, OML_BLOB_VALUE);
    omlc_set_blob (*oml_value_get_value(value), ptr, len); /*XXX*/
    logdebug3("Unmarshalled blob of size %d\n", len);
    mbuf_read_skip (mbuf, len);
    break;
  }

  case GUID_T: {
    uint64_t nv64;
    uint8_t buf[GUID_T_SIZE];
    if(mbuf_read(mbuf, buf, GUID_T_SIZE) == -1) {
      logerror("Failed to unmarshall OML_GUID_VALUE data; not enough data?\n");
      return 0;
    }
    memcpy(&nv64, buf, sizeof(nv64));
    oml_value_set_type(value, OML_GUID_VALUE);
    omlc_set_guid(*oml_value_get_value(value), ntohll(nv64));
    logdebug3("Unmarshalled GUID %" PRIu64 "\n", omlc_get_guid(*oml_value_get_value(value)));
    break;
  }

  case BOOL_FALSE_T:
  case BOOL_TRUE_T:
    oml_value_set_type(value, OML_BOOL_VALUE);
    omlc_set_bool(*oml_value_get_value(value),
                  (type == BOOL_TRUE_T)?OMLC_BOOL_TRUE:OMLC_BOOL_FALSE);
    logdebug3("Unmarshalled boolean %d\n", OMLC_BOOL_TRUE == omlc_get_bool(*oml_value_get_value(value)));
    break;

  case VECTOR_T: {
    uint16_t i, nof_elts;
    int type = mbuf_read_byte(mbuf);
    if(-1 == type) {
      logerror("%s(): failed to unmarshall VECTOR_T length\n", __func__);
      return 0;
    }
    if(mbuf_read(mbuf,(uint8_t*)(&nof_elts), sizeof(nof_elts)) == -1) {
      logerror("%s(): failed to unmarshall VECTOR_T length\n", __func__);
      return 0;
    }
    nof_elts = ntohs(nof_elts);

    OmlValueT oml_type = vector_type_map[type];
    OmlValueU *v = oml_value_get_value(value);
    switch(type) {
    case INT32_T:
    case UINT32_T: {
      size_t bytes = nof_elts * sizeof(uint32_t);
      uint32_t *elts = oml_calloc(nof_elts, sizeof(uint32_t));
      if(mbuf_read(mbuf, (uint8_t*)(elts), nof_elts * sizeof(uint32_t)) == -1) {
        logerror("%s(): failed to unmarshall OML_VECTOR_(U)INT32_VALUE\n", __func__);
        return 0;
      }
      for(i = 0; i < nof_elts; i++)
        elts[i] = ntohl(elts[i]);
      oml_value_set_type(value, oml_type);
      omlc_set_vector_ptr(*v, elts);
      omlc_set_vector_length(*v, bytes);
      omlc_set_vector_size(*v, bytes);
      omlc_set_vector_nof_elts(*v, nof_elts);
      omlc_set_vector_elt_size(*v, sizeof(uint32_t));
      break;
    }
    case INT64_T:
    case UINT64_T:
    case DOUBLE64_T: {
      size_t bytes = nof_elts * sizeof(uint64_t);
      uint64_t *elts = oml_calloc(nof_elts, sizeof(uint64_t));
      if(mbuf_read(mbuf, (uint8_t*)(elts), nof_elts * sizeof(uint64_t)) == -1) {
        logerror("%s(): failed to unmarshall OML_VECTOR_(U)INT64_VALUE\n", __func__);
        return 0;
      }
      for(i = 0; i < nof_elts; i++)
        elts[i] = ntohll(elts[i]);
      oml_value_set_type(value, oml_type);
      omlc_set_vector_ptr(*v, elts);
      omlc_set_vector_length(*v, bytes);
      omlc_set_vector_size(*v, bytes);
      omlc_set_vector_nof_elts(*v, nof_elts);
      omlc_set_vector_elt_size(*v, sizeof(uint64_t));
      break;
    }
    case BOOL_T: {
      uint8_t y[nof_elts];
      size_t bytes = nof_elts * sizeof(bool);
      bool *elts = oml_calloc(nof_elts, sizeof(bool));
      if(mbuf_read(mbuf, y, nof_elts) == -1) {
        logerror("%s(): failed to unmarshall OML_VECTOR_BOOL_VALUE\n", __func__);
        return 0;
      }
      for(i = 0; i < nof_elts; i++)
        elts[i] = ((BOOL_TRUE_T == y[i]) ? true : false);
      oml_value_set_type(value, oml_type);
      omlc_set_vector_ptr(*v, elts);
      omlc_set_vector_length(*v, bytes);
      omlc_set_vector_size(*v, bytes);
      omlc_set_vector_nof_elts(*v, nof_elts);
      omlc_set_vector_elt_size(*v, sizeof(bool));
      break;
    }
    default:
      logerror("%s(): bad type for array (t=%d)\n", __func__, type);
      break;
    }
    break;
  }

  default:
    logerror("%s: Unsupported value type '%d'\n", __FUNCTION__, type);
    return 0;
  }

  return 1;
}