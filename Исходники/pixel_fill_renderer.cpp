void CL_PixelFillRenderer::clear(const CL_Colorf &color)
{
	int dest_buffer_width = colorbuffer0.size.width;
	int dest_buffer_height = colorbuffer0.size.height;
	unsigned char *dest_data = (unsigned char *) colorbuffer0.data;

	CL_Color c = color;
	unsigned int color8888 = (c.get_alpha() << 24) + (c.get_red() << 16) + (c.get_green() << 8) + c.get_blue();
	unsigned char *ptr_color8888 = (unsigned char *) &color8888;

	for (int y = find_first_line_for_core(clip_rect.top, core, num_cores); y < clip_rect.bottom; y += num_cores)
	{
		unsigned char *line = dest_data + y * dest_buffer_width * 4 + clip_rect.left * 4;
		unsigned int line_align = ((line) - ((unsigned char *) 0)) & 0xf; // A gcc safe way of obtaining an address
		int pos = 0;
		int length = clip_rect.get_width()*4;

		// Write single bytes until we are byte aligned:
		if (line_align)
		{
			int prefix_length = cl_min(length, (int) (16 - line_align));
			for (; pos < prefix_length; pos++)
				line[pos] = ptr_color8888[pos&0x3];
		}

		// Figure out how our 16 bytes should look like after we applied the alignment:
		unsigned int b0 = ptr_color8888[(pos+0)&0x3];
		unsigned int b1 = ptr_color8888[(pos+1)&0x3];
		unsigned int b2 = ptr_color8888[(pos+2)&0x3];
		unsigned int b3 = ptr_color8888[(pos+3)&0x3];
		__m128i c_sse = _mm_set1_epi32((b3<<24)+(b2<<16)+(b1<<8)+b0);

		// Fill 16 byte aligned:
		int align_length = length-pos-15;
		for (; pos < align_length; pos+=16)
			_mm_stream_si128((__m128i*)(line+pos), c_sse);

		// Fill remaining bytes:
		for (; pos < length; pos++)
			line[pos] = ptr_color8888[pos&0x3];
	}
}