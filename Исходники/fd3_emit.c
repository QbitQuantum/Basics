static void
emit_constants(struct fd_ringbuffer *ring,
		enum adreno_state_block sb,
		struct fd_constbuf_stateobj *constbuf,
		struct ir3_shader_variant *shader)
{
	uint32_t enabled_mask = constbuf->enabled_mask;
	uint32_t first_immediate;
	uint32_t base = 0;
	unsigned i;

	// XXX TODO only emit dirty consts.. but we need to keep track if
	// they are clobbered by a clear, gmem2mem, or mem2gmem..
	constbuf->dirty_mask = enabled_mask;

	/* in particular, with binning shader and a unneeded consts no
	 * longer referenced, we could end up w/ constlen that is smaller
	 * than first_immediate.  In that case truncate the user consts
	 * early to avoid HLSQ lockup caused by writing too many consts
	 */
	first_immediate = MIN2(shader->first_immediate, shader->constlen);

	/* emit user constants: */
	while (enabled_mask) {
		unsigned index = ffs(enabled_mask) - 1;
		struct pipe_constant_buffer *cb = &constbuf->cb[index];
		unsigned size = align(cb->buffer_size, 4) / 4; /* size in dwords */

		// I expect that size should be a multiple of vec4's:
		assert(size == align(size, 4));

		/* gallium could leave const buffers bound above what the
		 * current shader uses.. don't let that confuse us.
		 */
		if (base >= (4 * first_immediate))
			break;

		if (constbuf->dirty_mask & (1 << index)) {
			/* and even if the start of the const buffer is before
			 * first_immediate, the end may not be:
			 */
			size = MIN2(size, (4 * first_immediate) - base);
			fd3_emit_constant(ring, sb, base,
					cb->buffer_offset, size,
					cb->user_buffer, cb->buffer);
			constbuf->dirty_mask &= ~(1 << index);
		}

		base += size;
		enabled_mask &= ~(1 << index);
	}

	/* emit shader immediates: */
	if (shader) {
		for (i = 0; i < shader->immediates_count; i++) {
			base = 4 * (shader->first_immediate + i);
			if (base >= (4 * shader->constlen))
				break;
			fd3_emit_constant(ring, sb, base,
				0, 4, shader->immediates[i].val, NULL);
		}
	}
}