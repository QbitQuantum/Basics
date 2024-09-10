int
assemble_ipmi_kcs_pkt (fiid_obj_t obj_kcs_hdr,
                       fiid_obj_t obj_cmd,
                       void *pkt,
                       unsigned int pkt_len,
		       unsigned int flags)
{
  int obj_cmd_len, obj_kcs_hdr_len;
  unsigned int utmp;
  unsigned int flags_mask = 0;

  if (!fiid_obj_valid (obj_kcs_hdr)
      || !fiid_obj_valid (obj_cmd)
      || !pkt
      || (flags & ~flags_mask))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_kcs_hdr, tmpl_hdr_kcs) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  if (FIID_OBJ_PACKET_VALID (obj_kcs_hdr) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_kcs_hdr);
      return (-1);
    }
  if (FIID_OBJ_PACKET_VALID (obj_cmd) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  if ((obj_kcs_hdr_len = fiid_obj_len_bytes (obj_kcs_hdr)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_kcs_hdr);
      return (-1);
    }
  if ((obj_cmd_len = fiid_obj_len_bytes (obj_cmd)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  /* int overflow not possible here */
  if (pkt_len < (obj_kcs_hdr_len + obj_cmd_len))
    {
      SET_ERRNO (EMSGSIZE);
      return (-1);
    }

  memset (pkt, 0, pkt_len);
  if ((obj_kcs_hdr_len = fiid_obj_get_all (obj_kcs_hdr,
                                           pkt,
                                           pkt_len)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_kcs_hdr);
      return (-1);
    }
  if ((obj_cmd_len = fiid_obj_get_all (obj_cmd,
                                       pkt + obj_kcs_hdr_len,
                                       pkt_len - obj_kcs_hdr_len)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  utmp = obj_kcs_hdr_len + obj_cmd_len;
  if (utmp > INT_MAX)
    {
      SET_ERRNO (EMSGSIZE);
      return (-1);
    }

  return (obj_kcs_hdr_len + obj_cmd_len);
}