	void text_entry::refresh_render_text_part(render_text_part& part, const render_text_part* previous_part, int begin_pos, int end_pos, const rectf& all_parts_area) {
		int visible_begin_pos = std::max(_visible_pos, begin_pos);
		int unclipped_char_count = std::max(0, end_pos - visible_begin_pos);
		part._unclipped_text.assign(_text.c_str(), visible_begin_pos, unclipped_char_count);
		raw_text_to_visible_text(part._unclipped_text);
		
		part._clipped_text.assign(L"");
		float clipped_text_width = 0.f;

		pointf clipped_top_left = all_parts_area.get_top_left();
		if (previous_part != nullptr) {
			clipped_top_left = previous_part->_area.get_top_right();
		}
		const float available_width = all_parts_area.get_right() - clipped_top_left._x;

		size_t clipped_char_count = part._unclipped_text.length();
		while (clipped_char_count >= 0) {
			part._clipped_text.assign(part._unclipped_text.c_str(), 0, clipped_char_count);
			
			clipped_text_width = get_text_width(part._clipped_text);
			if (previous_part != nullptr && !previous_part->_clipped_text.empty()) {
				clipped_text_width += get_kerning_pair_offset(
					previous_part->_clipped_text[previous_part->_clipped_text.length() - 1],
					part._clipped_text[0]);
			}
			
			if (clipped_text_width <= available_width) {
				break;
			}
		}

		part._area = rectf(clipped_top_left, sizef(clipped_text_width, all_parts_area.get_height()));
	}