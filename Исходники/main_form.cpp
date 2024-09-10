	void initialize_widgets()
	{
		static internationalization i18n{};
		auto bg_color = 0xefefef;

		fm.icon(main_icon());
		fm.caption(i18n("form_title"));
		fm.background(bg_color);

		auto width = fm.size().width;
		lst_songs.append_header(i18n("Artist"), width / 6);
		lst_songs.append_header(i18n("Title"), width / 3);
		lst_songs.append_header(i18n("File"), width / 2);

		lbl_songs.caption(i18n("Songs") + L":");
		lbl_songs.background(bg_color);
		lbl_songs.text_align(align::left, align_v::center);

		chk_matched.caption(i18n("Matched only"));
		chk_matched.background(bg_color);

		txt_search.multi_lines(false);

		btn_search.background(bg_color);

		pl.div("margin=10 vertical"
			"<weight=22 <search arrange=[variable, 120, 100, 22]> >"
			"<weight=10>"
			"<lst>"
			);
		pl["lst"] << lst_songs;
		pl["search"] << lbl_songs << chk_matched << txt_search << btn_search;
		pl.collocate();
	}