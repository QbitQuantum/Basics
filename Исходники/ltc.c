int ltc_encoder_dec_timecode(LTCEncoder *e) {
	return ltc_frame_decrement (&e->f, rint(e->fps), e->standard, e->flags);
}