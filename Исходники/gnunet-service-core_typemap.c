/**
 * Compute a type map message for this peer.
 *
 * @return this peers current type map message.
 */
struct GNUNET_MessageHeader *
GSC_TYPEMAP_compute_type_map_message ()
{
  char *tmp;
  uLongf dlen;
  struct GNUNET_MessageHeader *hdr;

#ifdef compressBound
  dlen = compressBound (sizeof (my_type_map));
#else
  dlen = sizeof (my_type_map) + (sizeof (my_type_map) / 100) + 20;
  /* documentation says 100.1% oldSize + 12 bytes, but we
   * should be able to overshoot by more to be safe */
#endif
  hdr = GNUNET_malloc (dlen + sizeof (struct GNUNET_MessageHeader));
  tmp = (char *) &hdr[1];
  if ((Z_OK !=
       compress2 ((Bytef *) tmp, &dlen, (const Bytef *) &my_type_map,
                  sizeof (my_type_map), 9)) || (dlen >= sizeof (my_type_map)))
  {
    dlen = sizeof (my_type_map);
    memcpy (tmp, &my_type_map, sizeof (my_type_map));
    hdr->type = htons (GNUNET_MESSAGE_TYPE_CORE_BINARY_TYPE_MAP);
  }
  else
  {
    hdr->type = htons (GNUNET_MESSAGE_TYPE_CORE_COMPRESSED_TYPE_MAP);
  }
  hdr->size = htons ((uint16_t) dlen + sizeof (struct GNUNET_MessageHeader));
  return hdr;
}