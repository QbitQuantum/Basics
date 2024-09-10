void BedShapePanel::build_panel(ConfigOptionPoints* default_pt)
{
//  on_change(nullptr);

	auto box = new wxStaticBox(this, wxID_ANY, _(L("Shape")));
	auto sbsizer = new wxStaticBoxSizer(box, wxVERTICAL);

	// shape options
    m_shape_options_book = new wxChoicebook(this, wxID_ANY, wxDefaultPosition, 
                           wxSize(25*wxGetApp().em_unit(), -1), wxCHB_TOP);
	sbsizer->Add(m_shape_options_book);

	auto optgroup = init_shape_options_page(_(L("Rectangular")));
		ConfigOptionDef def;
		def.type = coPoints;
		def.default_value = new ConfigOptionPoints{ Vec2d(200, 200) };
		def.label = L("Size");
		def.tooltip = L("Size in X and Y of the rectangular plate.");
		Option option(def, "rect_size");
		optgroup->append_single_option_line(option);

		def.type = coPoints;
		def.default_value = new ConfigOptionPoints{ Vec2d(0, 0) };
		def.label = L("Origin");
		def.tooltip = L("Distance of the 0,0 G-code coordinate from the front left corner of the rectangle.");
		option = Option(def, "rect_origin");
		optgroup->append_single_option_line(option);

		optgroup = init_shape_options_page(_(L("Circular")));
		def.type = coFloat;
		def.default_value = new ConfigOptionFloat(200);
		def.sidetext = L("mm");
		def.label = L("Diameter");
		def.tooltip = L("Diameter of the print bed. It is assumed that origin (0,0) is located in the center.");
		option = Option(def, "diameter");
		optgroup->append_single_option_line(option);

		optgroup = init_shape_options_page(_(L("Custom")));
		Line line{ "", "" };
		line.full_width = 1;
		line.widget = [this](wxWindow* parent) {
			auto btn = new wxButton(parent, wxID_ANY, _(L("Load shape from STL...")), wxDefaultPosition, wxDefaultSize);
			
			auto sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(btn);

			btn->Bind(wxEVT_BUTTON, ([this](wxCommandEvent e)
			{
				load_stl();
			}));

			return sizer;
		};
		optgroup->append_line(line);

	Bind(wxEVT_CHOICEBOOK_PAGE_CHANGED, ([this](wxCommandEvent e)
	{
		update_shape();
	}));

	// right pane with preview canvas
	m_canvas = new Bed_2D(this);
	m_canvas->m_bed_shape = default_pt->values;

	// main sizer
	auto top_sizer = new wxBoxSizer(wxHORIZONTAL);
	top_sizer->Add(sbsizer, 0, wxEXPAND | wxLeft | wxTOP | wxBOTTOM, 10);
	if (m_canvas)
		top_sizer->Add(m_canvas, 1, wxEXPAND | wxALL, 10) ;

	SetSizerAndFit(top_sizer);

	set_shape(default_pt);
	update_preview();
}