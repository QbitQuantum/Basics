/* store the contents of this packet to its place in its file */
void store_packet(flow_t flow, const u_char *data, u_int32_t length,
		  u_int32_t seq)
{
  flow_state_t *state;
  tcp_seq offset;
  long fpos;

  /* see if we have state about this flow; if not, create it */
  if ((state = find_flow_state(flow)) == NULL) {
    state = create_flow_state(flow, seq);
  }

  /* if we're done collecting for this flow, return now */
  if (IS_SET(state->flags, FLOW_FINISHED))
    return;

  /* calculate the offset into this flow -- should handle seq num
   * wrapping correctly because tcp_seq is the right size */
  offset = seq - state->isn;

  /* I want to guard against receiving a packet with a sequence number
   * slightly less than what we consider the ISN to be; the max
   * (though admittedly non-scaled) window of 64K should be enough */
  if (offset >= 0xffff0000) {
    DEBUG(2) ("dropped packet with seq < isn on %s", flow_filename(flow));
    return;
  }

  /* reject this packet if it falls entirely outside of the range of
   * bytes we want to receive for the flow */
  if (bytes_per_flow && (offset > bytes_per_flow))
    return;

  /* if we don't have a file open for this flow, try to open it.
   * return if the open fails.  Note that we don't have to explicitly
   * save the return value because open_file() puts the file pointer
   * into the structure for us. */
  if (state->fp == NULL) {
    if (open_file(state) == NULL) {
      return;
    }
  }

  /* We are go for launch!  Everything's ready for us to do a write. */

  /* reduce length if it goes beyond the number of bytes per flow */
  if (bytes_per_flow && (offset + length > bytes_per_flow)) {
    SET_BIT(state->flags, FLOW_FINISHED);
    length = bytes_per_flow - offset;
  }

  /* if we're not at the correct point in the file, seek there */
  if (offset != state->pos) {
    fpos = offset;
    FSETPOS(state->fp, &fpos);
  }

  /* write the data into the file */
  DEBUG(25) ("%s: writing %ld bytes @%ld", flow_filename(state->flow),
	  (long) length, (long) offset);

  if (fwrite(data, length, 1, state->fp) != 1) {
    /* sigh... this should be a nice, plain DEBUG statement that
     * passes strerrror() as an argument, but SunOS 4.1.3 doesn't seem
     * to have strerror. */
    if (debug_level >= 1) {
      DEBUG(1) ("write to %s failed: ", flow_filename(state->flow));
      perror("");
    }
  }
  fflush(state->fp);

  /* remember the position for next time */
  state->pos = offset + length;

  if (IS_SET(state->flags, FLOW_FINISHED)) {
    DEBUG(5) ("%s: stopping capture", flow_filename(state->flow));
    close_file(state);
  }
}