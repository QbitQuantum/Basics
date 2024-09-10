static u_char
show_vty_subtlv_max_rsv_bw (struct vty *vty, struct te_subtlv_max_rsv_bw *tlv)
{
  float fval;

  fval = ntohf (tlv->value);

  if (vty != NULL)
    vty_out (vty, "    Maximum Reservable Bandwidth: %g (Bytes/sec)%s", fval,
             VTY_NEWLINE);
  else
    zlog_debug ("      Maximum Reservable Bandwidth: %g (Bytes/sec)", fval);

  return (SUBTLV_HDR_SIZE + SUBTLV_DEF_SIZE);
}