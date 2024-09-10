  //------------------------------------------------------------------------------
  node_alignment_analyzer::node_alignment_analyzer(const osm_diff_analyzer_if::module_configuration * p_conf,
                                                   node_alignment_common_api & p_api):
    osm_diff_analyzer_cpp_if::cpp_analyzer_base("node_alignment_analyser",p_conf->get_name(),""),
    m_api(p_api),
    m_report()
  {
     // Register module to be able to use User Interface
    m_api.ui_register_module(*this,get_name());

   const std::map<std::string,std::string> & l_conf_parameters = p_conf->get_parameters();

    std::map<std::string,std::string>::const_iterator l_iter = l_conf_parameters.find("min_way_node_nb");
    if(l_iter == l_conf_parameters.end())
    {
      {
	std::stringstream l_stream;
	l_stream << this->get_name() << " : Using default value for parameter \"min_way_node_nb\" : " << changeset::get_min_way_node_nb() ;
	m_api.ui_append_log_text(*this,l_stream.str());
      }
    }
    else
      {
	float l_min_way_node_nb = strtof(l_iter->second.c_str(),NULL);

	{
	  std::stringstream l_stream;
	  l_stream << this->get_name() << " : Using value " << l_min_way_node_nb << " for parameter \"min_way_node_nb\"" ;
	  m_api.ui_append_log_text(*this,l_stream.str());
	}
	changeset::set_min_way_node_nb(l_min_way_node_nb);
      }
    l_iter = l_conf_parameters.find("modif_rate_min_level");
    if(l_iter == l_conf_parameters.end())
    {
      std::stringstream l_stream;
      l_stream << this->get_name() << " : Using default value for parameter \"modif_rate_min_level\" : " << changeset::get_modif_rate_min_level();
      m_api.ui_append_log_text(*this,l_stream.str());
    }
    else
      {
	float l_modif_rate_min_level = strtof(l_iter->second.c_str(),NULL);
	std::stringstream l_stream;
	l_stream << this->get_name() << " : Using value " << l_modif_rate_min_level << " for parameter \"modif_rate_min_level\"" ;
	m_api.ui_append_log_text(*this,l_stream.str());
	changeset::set_modif_rate_min_level(l_modif_rate_min_level);
      }

    l_iter = l_conf_parameters.find("min_alignment_modification_rate");
    if(l_iter == l_conf_parameters.end())
    {
	std::stringstream l_stream;
	l_stream << this->get_name() << " : Using default value for parameter \"min_alignment_modification_rate\" : " << changeset::get_min_alignment_modification_rate();
	m_api.ui_append_log_text(*this,l_stream.str());	
    }
    else
      {
	float l_min_alignment_modification_rate = strtof(l_iter->second.c_str(),NULL);
	std::stringstream l_stream;
	l_stream << this->get_name() << " : Using value " << l_min_alignment_modification_rate << " for parameter \"min_alignment_modification_rate\"" ;
	m_api.ui_append_log_text(*this,l_stream.str());
	changeset::set_min_alignment_modification_rate(l_min_alignment_modification_rate);
      }

    changeset::set_api(m_api);

  }