int
assemble_ipmi_lan_pkt (fiid_obj_t obj_rmcp_hdr,
                       fiid_obj_t obj_lan_session_hdr,
                       fiid_obj_t obj_lan_msg_hdr,
                       fiid_obj_t obj_cmd,
                       const void *authentication_code_data,
                       unsigned int authentication_code_data_len,
                       void *pkt,
                       unsigned int pkt_len,
		       unsigned int flags)
{
  uint8_t authentication_type;
  uint64_t val;
  unsigned int indx = 0;
  int required_len;
  void *authentication_code_field_ptr = NULL;
  void *checksum_data_ptr = NULL;
  void *msg_data_ptr = NULL;
  void *ipmi_msg_len_ptr = NULL;
  unsigned int msg_data_count = 0;
  unsigned int checksum_data_count = 0;
  uint8_t ipmi_msg_len;
  fiid_obj_t obj_lan_msg_trlr = NULL;
  uint8_t pwbuf[IPMI_1_5_MAX_PASSWORD_LENGTH];
  uint8_t checksum;
  int len, rv = -1;
  unsigned int flags_mask = 0;

  if (!fiid_obj_valid (obj_rmcp_hdr)
      || !fiid_obj_valid (obj_lan_session_hdr)
      || !fiid_obj_valid (obj_lan_msg_hdr)
      || !fiid_obj_valid (obj_cmd)
      || (authentication_code_data && authentication_code_data_len > IPMI_1_5_MAX_PASSWORD_LENGTH)
      || !pkt
      || (flags & ~flags_mask))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_rmcp_hdr, tmpl_rmcp_hdr) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  if (FIID_OBJ_TEMPLATE_COMPARE (obj_lan_session_hdr, tmpl_lan_session_hdr) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  if (FIID_OBJ_TEMPLATE_COMPARE (obj_lan_msg_hdr, tmpl_lan_msg_hdr_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  if (FIID_OBJ_PACKET_VALID (obj_rmcp_hdr) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcp_hdr);
      return (-1);
    }

  /*
   * ipmi_msg_len is calculated in this function, so we can't use
   * fiid_obj_packet_valid() on obj_lan_session_hdr b/c ipmi_msg_len
   * is probably not set yet.
   */

  if (FIID_OBJ_PACKET_VALID (obj_lan_msg_hdr) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_hdr);
      return (-1);
    }
  if (FIID_OBJ_PACKET_VALID (obj_cmd) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  if (FIID_OBJ_GET (obj_lan_session_hdr,
                    "authentication_type",
                    &val) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }
  authentication_type = val;

  if (authentication_type != IPMI_AUTHENTICATION_TYPE_NONE
      && authentication_type != IPMI_AUTHENTICATION_TYPE_MD2
      && authentication_type != IPMI_AUTHENTICATION_TYPE_MD5
      && authentication_type != IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  /* no need for overflow checks, handled w/ _ipmi_lan_pkt_rq_min_size check */

  required_len = _ipmi_lan_pkt_rq_min_size (authentication_type, obj_cmd);
  if (pkt_len < required_len)
    {
      SET_ERRNO (EMSGSIZE);
      return (-1);
    }

  memset (pkt, 0, pkt_len);

  if ((len = fiid_obj_get_all (obj_rmcp_hdr, pkt + indx, pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcp_hdr);
      goto cleanup;
    }
  indx += len;

  if ((len = fiid_obj_get_block (obj_lan_session_hdr,
                                 "authentication_type",
                                 "session_id",
                                 pkt + indx,
                                 pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_session_hdr);
      goto cleanup;
    }

  indx += len;

  /* authentication_code generated last.  Save pointers for later calculation */
  if (authentication_type != IPMI_AUTHENTICATION_TYPE_NONE)
    {
      authentication_code_field_ptr = (pkt + indx);
      indx += IPMI_1_5_MAX_PASSWORD_LENGTH;
    }

  ipmi_msg_len_ptr = (pkt + indx);
  if ((len = fiid_template_field_len_bytes (tmpl_lan_session_hdr, "ipmi_msg_len")) < 0)
    {
      ERRNO_TRACE (errno);
      goto cleanup;
    }
  if (len != 1)
    {
      SET_ERRNO (EINVAL);
      goto cleanup;
    }
  indx += len;

  msg_data_ptr = (pkt + indx);

  if ((len = fiid_obj_get_block (obj_lan_msg_hdr,
                                 "rs_addr",
                                 "checksum1",
                                 pkt + indx,
                                 pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_hdr);
      goto cleanup;
    }
  indx += len;
  msg_data_count += len;

  checksum_data_ptr = (pkt + indx);

  if ((len = fiid_obj_get_block (obj_lan_msg_hdr,
                                 "rq_addr",
                                 "rq_seq",
                                 pkt + indx,
                                 pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_hdr);
      goto cleanup;
    }
  indx += len;
  msg_data_count += len;
  checksum_data_count += len;

  if ((len = fiid_obj_get_all (obj_cmd, pkt + indx, pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      goto cleanup;
    }
  indx += len;
  msg_data_count += len;
  checksum_data_count += len;

  if (!(obj_lan_msg_trlr = fiid_obj_create (tmpl_lan_msg_trlr)))
    {
      ERRNO_TRACE (errno);
      goto cleanup;
    }

  checksum = ipmi_checksum (checksum_data_ptr, checksum_data_count);

  if (fiid_obj_set_all (obj_lan_msg_trlr, &checksum, sizeof (checksum)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_trlr);
      goto cleanup;
    }

  if ((len = fiid_obj_get_all (obj_lan_msg_trlr, pkt + indx, pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_trlr);
      goto cleanup;
    }
  indx += len;
  msg_data_count += len;

  /* ipmi_msg_len done after message length is computed */
  ipmi_msg_len = msg_data_count;
  memcpy (ipmi_msg_len_ptr,
          &ipmi_msg_len,
          sizeof (ipmi_msg_len));

  /* Auth code must be done last, some authentication like md2 and md5
   * require all fields, including checksums, to be calculated
   * beforehand
   */
  if (authentication_type != IPMI_AUTHENTICATION_TYPE_NONE)
    {
      int authentication_len;

      memset (pwbuf, '\0', IPMI_1_5_MAX_PASSWORD_LENGTH);

      if ((authentication_len = fiid_obj_field_len_bytes (obj_lan_session_hdr,
                                                          "authentication_code")) < 0)
        {
          FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_session_hdr);
          goto cleanup;
        }

      if (authentication_len)
        {
          if (fiid_obj_get_data (obj_lan_session_hdr,
                                 "authentication_code",
                                 pwbuf,
                                 IPMI_1_5_MAX_PASSWORD_LENGTH) < 0)
            {
              FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_session_hdr);
              goto cleanup;
            }

          memcpy (authentication_code_field_ptr,
                  pwbuf,
                  IPMI_1_5_MAX_PASSWORD_LENGTH);
        }
      else
        {
          if (authentication_code_data)
            memcpy (pwbuf,
                    authentication_code_data,
                    authentication_code_data_len);

          if (authentication_type == IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY)
            {
              memcpy (authentication_code_field_ptr,
                      pwbuf,
                      IPMI_1_5_MAX_PASSWORD_LENGTH);
            }
          else /* IPMI_AUTHENTICATION_TYPE_MD2 || IPMI_AUTHENTICATION_TYPE_MD5 */
            {
              uint8_t session_id_buf[1024];
              uint8_t session_sequence_number_buf[1024];
              int session_id_len, session_sequence_number_len;

              if ((session_id_len = fiid_obj_get_data (obj_lan_session_hdr,
                                                       "session_id",
                                                       session_id_buf,
                                                       1024)) < 0)
                {
                  FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_session_hdr);
                  goto cleanup;
                }

              if ((session_sequence_number_len = fiid_obj_get_data (obj_lan_session_hdr,
                                                                    "session_sequence_number",
                                                                    session_sequence_number_buf,
                                                                    1024)) < 0)
                {
                  FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_session_hdr);
                  goto cleanup;
                }

              if (authentication_type == IPMI_AUTHENTICATION_TYPE_MD2)
                {
                  md2_t ctx;
                  uint8_t digest[MD2_DIGEST_LENGTH];

                  assert (IPMI_1_5_MAX_PASSWORD_LENGTH == MD2_DIGEST_LENGTH);

                  md2_init (&ctx);
                  md2_update_data (&ctx, pwbuf, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  md2_update_data (&ctx, session_id_buf, session_id_len);
                  md2_update_data (&ctx, msg_data_ptr, msg_data_count);
                  md2_update_data (&ctx, session_sequence_number_buf, session_sequence_number_len);
                  md2_update_data (&ctx, pwbuf, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  md2_finish (&ctx, digest, MD2_DIGEST_LENGTH);
                  md2_init (&ctx);

                  memcpy (authentication_code_field_ptr, digest, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  secure_memset (digest, '\0', MD2_DIGEST_LENGTH);
                }
              else if (authentication_type == IPMI_AUTHENTICATION_TYPE_MD5)
                {
                  md5_t ctx;
                  uint8_t digest[MD5_DIGEST_LENGTH];

                  assert (IPMI_1_5_MAX_PASSWORD_LENGTH == MD5_DIGEST_LENGTH);

                  md5_init (&ctx);
                  md5_update_data (&ctx, pwbuf, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  md5_update_data (&ctx, session_id_buf, session_id_len);
                  md5_update_data (&ctx, msg_data_ptr, msg_data_count);
                  md5_update_data (&ctx, session_sequence_number_buf, session_sequence_number_len);
                  md5_update_data (&ctx, pwbuf, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  md5_finish (&ctx, digest, MD5_DIGEST_LENGTH);
                  md5_init (&ctx);

                  memcpy (authentication_code_field_ptr, digest, IPMI_1_5_MAX_PASSWORD_LENGTH);
                  secure_memset (digest, '\0', MD5_DIGEST_LENGTH);
                }
            }
        }
    }

  if (indx > INT_MAX)
    {
      SET_ERRNO (EMSGSIZE);
      goto cleanup;
    }

  rv = indx;
 cleanup:
  if (rv < 0)
    secure_memset (pkt, '\0', pkt_len);
  fiid_obj_destroy (obj_lan_msg_trlr);
  secure_memset (pwbuf, '\0', IPMI_1_5_MAX_PASSWORD_LENGTH);
  return (rv);
}