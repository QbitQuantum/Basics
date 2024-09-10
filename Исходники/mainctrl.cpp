void MainCtrl::redraw ()
{
	choose_palette (ui::PALETTE_ID_ENTRY);
	clear ();

	if (w().entries.empty ()) {
		put(ui::Size{}, L"No entry yet.");
		put(ui::Size{0, 1}, L"Press \"a\" to create one; press Esc for the menu.");
#ifdef TIARY_USE_MOUSE
		put(ui::Size{0, 2}, L"You can also use your mouse.");
#endif
		return;
	}

	if (w().filtered_entries_ && w().filtered_entries_->empty ()) {
		put(ui::Size{}, L"This is in filtered mode.");
		put(ui::Size{0, 1}, L"But no entry satisfies your requirement.");
		put(ui::Size{0, 2}, L"Press Ctrl-G to modify your filter; or LEFT to see all entries.");
		return;
	}

	unsigned expand_lines = w().global_options.get_num (GLOBAL_OPTION_EXPAND_LINES);
	scroll_.modify_height(get_size().y - expand_lines + 1);

	ui::Scroll::Info info = scroll_.get_info();

	ui::Size pos{};

	std::wstring date_format = w().global_options.get_wstring (GLOBAL_OPTION_DATETIME_FORMAT);

	// Build a map to get entry ID from pointer
	std::map <const DiaryEntry *, unsigned> id_map;
	for (size_t i=0; i<w().entries.size (); ++i) {
		id_map.insert (std::make_pair (w().entries[i], i+1));
	}
	// Is there a filter?
	const DiaryEntryList &ent_lst = w().get_current_list ();

	wchar_t *disp_buffer = new wchar_t [get_size ().x];

	for (unsigned i=0; i<info.len; ++i) {

		choose_palette (i == info.focus_pos ? ui::PALETTE_ID_ENTRY_SELECT : ui::PALETTE_ID_ENTRY);

		if (i == info.focus_pos) {
			move_cursor (pos);
			clear(pos, ui::Size{get_size().x, expand_lines});
		}
		const DiaryEntry &entry = *ent_lst[i+info.first];

		// Entry ID
		pos = put(pos, format(L"%04a  "sv, id_map[&entry]));

		// Date
		choose_palette (i == info.focus_pos ? ui::PALETTE_ID_ENTRY_DATE_SELECT : ui::PALETTE_ID_ENTRY_DATE);
		pos = put(pos, entry.local_time.format(date_format));
		pos.x++;

		// Title
		SplitStringLine split_info;
		const std::wstring &title = entry.title;
		choose_palette (i == info.focus_pos ? ui::PALETTE_ID_ENTRY_TITLE_SELECT : ui::PALETTE_ID_ENTRY_TITLE);
		split_line(&split_info, maxS (0, get_size().x-pos.x), title, 0, SPLIT_NEWLINE_AS_SPACE|SPLIT_CUT_WORD);
		pos = put (pos, disp_buffer,
				std::replace_copy_if (
						&title[split_info.begin], &title[split_info.begin+split_info.len],
						disp_buffer, [](auto x) { return !iswprint(x); }, L' ') - disp_buffer);
		pos.x++;

		// Labels
		const DiaryEntry::LabelList &labels = entry.labels;
		choose_palette (i == info.focus_pos ? ui::PALETTE_ID_ENTRY_LABELS_SELECT : ui::PALETTE_ID_ENTRY_LABELS);
		int left_wid = get_size().x - pos.x;
		for (DiaryEntry::LabelList::const_iterator it=labels.begin(); it!=labels.end(); ) {
			if (left_wid < 3) {
				break;
			}
			unsigned labelwid = ucs_width (*it);
			if (labelwid + 2 > unsigned (left_wid)) {
				pos = put (pos, L"...", 3);
				break;
			}
			pos = put (pos, *it);
			if (++it != labels.end ()) {
				pos = put (pos, L',');
			}
		}
		pos.x++;

		choose_palette (i == info.focus_pos ? ui::PALETTE_ID_ENTRY_TEXT_SELECT : ui::PALETTE_ID_ENTRY_TEXT);
		const std::wstring &text = entry.text;
		size_t offset = 0;
		if (i == info.focus_pos && expand_lines >= 2) {
			// Current entry
			// [Date] [Title] [Labels]
			// [...]
			for (unsigned j=1; j<expand_lines; ++j) {
				pos = ui::Size{0, pos.y + 1};
				offset = split_line(&split_info, get_size().x, text, offset,
						SPLIT_NEWLINE_AS_SPACE);
				wchar_t *bufend = std::replace_copy_if (
						&text[split_info.begin], &text[split_info.begin+split_info.len],
						disp_buffer, [](auto x) { return !iswprint(x); }, L' ');
				pos = put (pos, disp_buffer, bufend-disp_buffer);
			}
		} else {
			// Other entry
			// [Date] [Title] [Labels] [...]
			offset = split_line(&split_info, maxS (0, get_size().x - pos.x), text, offset,
					SPLIT_NEWLINE_AS_SPACE|SPLIT_CUT_WORD);
			wchar_t *bufend = std::replace_copy_if (
					&text[split_info.begin], &text[split_info.begin+split_info.len],
					disp_buffer, [](auto x) { return !iswprint(x); }, L' ');
			pos = put (pos, disp_buffer, bufend-disp_buffer);
		}
		pos = ui::Size{0, pos.y + 1};
	}
	delete [] disp_buffer;
}