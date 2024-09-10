int
unassemble_rmcp_pkt (const void *pkt,
                     unsigned int pkt_len,
                     fiid_obj_t obj_rmcp_hdr,
                     fiid_obj_t obj_cmd,
		     unsigned int flags)
{
  unsigned int indx = 0;
  int len;
  unsigned int flags_mask = (IPMI_INTERFACE_FLAGS_NO_LEGAL_CHECK);

  if (!pkt
      || !fiid_obj_valid (obj_rmcp_hdr)
      || !fiid_obj_valid (obj_cmd)
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

  if (fiid_obj_clear (obj_rmcp_hdr) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcp_hdr);
      return (-1);
    }

  if (fiid_obj_clear (obj_cmd) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }

  if ((len = fiid_obj_set_all (obj_rmcp_hdr, pkt + indx, pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_rmcp_hdr);
      return (-1);
    }
  indx += len;

  if (pkt_len <= indx)
    {
      /* trace, but don't error out, cannot parse packet */
      ERR_TRACE ("malformed packet", EINVAL);
      return (0);
    }

  if ((len = fiid_obj_set_all (obj_cmd, pkt + indx, pkt_len - indx)) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }
  indx += len;

  if (FIID_OBJ_PACKET_VALID (obj_rmcp_hdr) == 1
      && ((flags & IPMI_INTERFACE_FLAGS_NO_LEGAL_CHECK) || FIID_OBJ_PACKET_SUFFICIENT (obj_cmd) == 1))
    return (1);

  return (0);
}