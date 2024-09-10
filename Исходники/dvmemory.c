void debug_view_memory::view_update()
{
	const debug_view_memory_source &source = downcast<const debug_view_memory_source &>(*m_source);

	// if we need to recompute, do it now
	if (needs_recompute())
		recompute();

	// get positional data
	const memory_view_pos &posdata = s_memory_pos_table[m_bytes_per_chunk];

	// loop over visible rows
	for (UINT32 row = 0; row < m_visible.y; row++)
	{
		debug_view_char *destmin = m_viewdata + row * m_visible.x;
		debug_view_char *destmax = destmin + m_visible.x;
		debug_view_char *destrow = destmin - m_topleft.x;
		UINT32 effrow = m_topleft.y + row;

		// reset the line of data; section 1 is normal, others are ancillary, cursor is selected
		debug_view_char *dest = destmin;
		for (int ch = 0; ch < m_visible.x; ch++, dest++)
		{
			UINT32 effcol = m_topleft.x + ch;
			dest->byte = ' ';
			dest->attrib = DCA_ANCILLARY;
			if (m_section[1].contains(effcol))
			{
				dest->attrib = DCA_NORMAL;
				if (m_cursor_visible && effrow == m_cursor.y && effcol == m_cursor.x)
					dest->attrib |= DCA_SELECTED;
			}
		}

		// if this visible row is valid, add it to the buffer
		if (effrow < m_total.y)
		{
			offs_t addrbyte = m_byte_offset + effrow * m_bytes_per_row;
			offs_t address = (source.m_space != NULL) ? source.m_space->byte_to_address(addrbyte) : addrbyte;
			char addrtext[20];

			// generate the address
			sprintf(addrtext, m_addrformat, address);
			dest = destrow + m_section[0].m_pos + 1;
			for (int ch = 0; addrtext[ch] != 0 && ch < m_section[0].m_width - 1; ch++, dest++)
				if (dest >= destmin && dest < destmax)
					dest->byte = addrtext[ch];

			// generate the data
			for (int chunknum = 0; chunknum < m_chunks_per_row; chunknum++)
			{
				int chunkindex = m_reverse_view ? (m_chunks_per_row - 1 - chunknum) : chunknum;

				UINT64 chunkdata;
				bool ismapped = read(m_bytes_per_chunk, addrbyte + chunknum * m_bytes_per_chunk, chunkdata);
				dest = destrow + m_section[1].m_pos + 1 + chunkindex * posdata.m_spacing;
				for (int ch = 0; ch < posdata.m_spacing; ch++, dest++)
					if (dest >= destmin && dest < destmax)
					{
						UINT8 shift = posdata.m_shift[ch];
						if (shift < 64)
							dest->byte = ismapped ? "0123456789ABCDEF"[(chunkdata >> shift) & 0x0f] : '*';
					}
			}

			// generate the ASCII data
			if (m_section[2].m_width > 0)
			{
				dest = destrow + m_section[2].m_pos + 1;
				for (int ch = 0; ch < m_bytes_per_row; ch++, dest++)
					if (dest >= destmin && dest < destmax)
					{
						UINT64 chval;
						bool ismapped = read(1, addrbyte + ch, chval);
						dest->byte = (ismapped && isprint(chval)) ? chval : '.';
					}
			}
		}