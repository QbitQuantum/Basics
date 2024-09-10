/*===========================================================================
FUNCTION DSMBIT_PACK32_TAIL

DESCRIPTION
  Packs a given value (up to thirty-two bits) into a given dsm item at a
  specified offset.  

DEPENDENCIES
  Data must be packed into the last used byte or the byte immediately
  following it.

  item_ptr can not be NULL.
  
PARAMETERS
  item_ptr  - Pointer to dsm item where packed data should be placed.
  pack_data - Data to be packed
  offset    - Number of bits to skip before placing this data
  len       - Number of bits of pack_data to pack (LSB of the variable)

RETURN VALUE
  Number of bits successfully packed

SIDE_EFFECTS
  A new dsm item may be acquired and linked.

===========================================================================*/
uint16 dsmbiti_pack32_tail
(
  dsm_item_type * item_ptr,
  uint32 pack_data,
  uint16 offset,
  uint16 len,
  dsm_mempool_id_type pool_id,
  const char * file,
  uint32 line
)
{
  uint32 bit_pack_data;          /* data to bit_pack into last byte */

  uint16 byte_offset;            /* Position in terms of bytes of reqd field */

  uint16 num_pushed_bits = 0;    /* stores number of bits pushed */

  uint16 length_packet;          /* stores the length of the passed packet */

  uint16 pushdown_bytes;          /* number of bytes to push down */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  byte_offset = (uint16) offset / 8;
  offset = offset % 8;

  /* have to be writing bits into the last used byte, or to the byte
     immediately following.
     dsm_length_packet starts counting at 1, byte_offset starts counting at 0,
     thus the apparent off-by-1 discrepancy. */

  DSM_ASSERT (NULL != item_ptr);

  length_packet = (uint16)dsm_length_packet(item_ptr);

  if (offset == 0)
  {
    DSM_ASSERT( length_packet == byte_offset);
  }
  else //offset != 0
  {
    DSM_ASSERT (length_packet == (byte_offset + 1));
  }

  /* if we are packing some bits into the last used byte, go to it directly
     and pack those bits in */
  if (offset != 0)
  {
    while (item_ptr->pkt_ptr != NULL)
    {
      byte_offset -= item_ptr->used;
      item_ptr = item_ptr->pkt_ptr;
    }

    /* move the bits to be packed into the LSB of the temporary variable */
    bit_pack_data = pack_data >> MAX((len + offset - 8), 0);

    /* pack the bits into the last used byte */
    b_packd (bit_pack_data, (item_ptr->data_ptr + byte_offset),
             offset, (word) MIN(8-offset, len));

    /* count the number of pushed bits */
    num_pushed_bits += MIN(8 - offset, len);

    /* decrease the remaining length by the number of bits pushed */
    len = MAX((len + offset - 8), 0);
  }

  /* len is number of bits to pushdown_tail.  It may have changed from
     the top of the function, as a result of packing some bits directly */
  if (len != 0)
  {
    /* shift out the bits that have already been packed */
    pack_data = pack_data << (32 - len);

    /* swap big-endian to little-endian in 16-bit and 32-bit values
       before pushing down */
    pack_data = NTOHL(pack_data);

    pushdown_bytes = 1 + ((len - 1) / 8);

    /* if the pushdown was successful */
    if (dsmi_pushdown_tail(&item_ptr, &pack_data, pushdown_bytes, pool_id, file, line) ==
        pushdown_bytes)
    {
      /* assume all bits were pushed and increment the counter */
      num_pushed_bits += len;
    }
  }

  return num_pushed_bits;
} /* dsmbit_pack32_tail() */