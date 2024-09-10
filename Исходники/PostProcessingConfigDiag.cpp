PostProcessingConfigDiag::PostProcessingConfigDiag(wxWindow* parent, const std::string& shader)
	: wxDialog(parent, wxID_ANY, _("Post Processing Shader Configuration")),
	  m_shader(shader)
{
	// Depending on if we are running already, either use the one from the videobackend
	// or generate our own.
	if (g_renderer && g_renderer->GetPostProcessor())
	{
		m_post_processor = g_renderer->GetPostProcessor()->GetConfig();
	}
	else
	{
		m_post_processor = new PostProcessingShaderConfiguration();
		m_post_processor->LoadShader(m_shader);
	}

	// Create our UI classes
	const PostProcessingShaderConfiguration::ConfigMap& config_map = m_post_processor->GetOptions();
	for (const auto& it : config_map)
	{
		if (it.second.m_type == PostProcessingShaderConfiguration::ConfigurationOption::OptionType::OPTION_BOOL)
		{
			ConfigGrouping* group = new ConfigGrouping(ConfigGrouping::WidgetType::TYPE_TOGGLE,
				it.second.m_gui_name, it.first, it.second.m_dependent_option,
				&it.second);
			m_config_map[it.first] = group;
		}
		else
		{
			ConfigGrouping* group = new ConfigGrouping(ConfigGrouping::WidgetType::TYPE_SLIDER,
				it.second.m_gui_name, it.first, it.second.m_dependent_option,
				&it.second);
			m_config_map[it.first] = group;
		}
	}

	// Arrange our vectors based on dependency
	for (const auto& it : m_config_map)
	{
		const std::string parent_name = it.second->GetParent();
		if (parent_name.size())
		{
			// Since it depends on a different object, push it to a parent's object
			m_config_map[parent_name]->AddChild(m_config_map[it.first]);
		}
		else
		{
			// It doesn't have a child, just push it to the vector
			m_config_groups.push_back(m_config_map[it.first]);
		}
	}

	// Generate our UI
	wxNotebook* const notebook = new wxNotebook(this, wxID_ANY);
	wxPanel* const page_general = new wxPanel(notebook);
	wxFlexGridSizer* const szr_general = new wxFlexGridSizer(2, 5, 5);

	// Now let's actually populate our window with our information
	bool add_general_page = false;
	for (const auto& it : m_config_groups)
	{
		if (it->HasChildren())
		{
			// Options with children get their own tab
			wxPanel* const page_option = new wxPanel(notebook);
			wxFlexGridSizer* const szr_option = new wxFlexGridSizer(2, 10, 5);
			it->GenerateUI(this, page_option, szr_option);

			// Add all the children
			for (const auto& child : it->GetChildren())
			{
				child->GenerateUI(this, page_option, szr_option);
			}
			page_option->SetSizerAndFit(szr_option);
			notebook->AddPage(page_option, _(it->GetGUIName()));
		}
		else
		{
			// Options with no children go in to the general tab
			if (!add_general_page)
			{
				// Make it so it doesn't show up if there aren't any options without children.
				add_general_page = true;
			}
			it->GenerateUI(this, page_general, szr_general);
		}
	}

	if (add_general_page)
	{
		page_general->SetSizerAndFit(szr_general);
		notebook->InsertPage(0, page_general, _("General"));
	}

	// Close Button
	wxButton* const btn_close = new wxButton(this, wxID_OK, _("Close"));
	btn_close->Bind(wxEVT_BUTTON, &PostProcessingConfigDiag::Event_ClickClose, this);

	Bind(wxEVT_CLOSE_WINDOW, &PostProcessingConfigDiag::Event_Close, this);

	wxBoxSizer* const szr_main = new wxBoxSizer(wxVERTICAL);
	szr_main->Add(notebook, 1, wxEXPAND | wxALL, 5);
	szr_main->Add(btn_close, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

	SetSizerAndFit(szr_main);
	Center();
	SetFocus();

	UpdateWindowUI();
}