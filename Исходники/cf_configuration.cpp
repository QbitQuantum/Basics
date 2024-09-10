  void cf_configuration::handle_config_cmd(char *cmd, const uint32_t &cmd_hash, char *arg,
      char *buf, const unsigned long &linenum)
  {
    char tmp[BUFFER_SIZE];
    int vec_count;
    char *vec[4];
    int port;
    std::vector<std::string> elts;
    std::string host, path, address, port_str;

    switch (cmd_hash)
      {
      case hash_domain_name_weight:
        _domain_name_weight = atof(arg);
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Weight given to the domain names in the simple filter");
        break;

      case hash_record_cache_timeout:
        _record_cache_timeout = atoi(arg);
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Timeout on cached remote records, in seconds");
        break;

      case hash_cf_peer:
        strlcpy(tmp,arg,sizeof(tmp));
        vec_count = miscutil::ssplit(tmp," \t",vec,SZ(vec),1,1);
        div_t divresult;
        divresult = div(vec_count,2);
        if (divresult.rem != 0)
          {
            errlog::log_error(LOG_LEVEL_ERROR,"Wrong number of parameter when specifying static collaborative filtering peer");
            break;
          }
        address = vec[0];
        urlmatch::parse_url_host_and_path(address,host,path);
        miscutil::tokenize(host,elts,":");
        port = -1;
        if (elts.size()>1)
          {
            host = elts.at(0);
            port = atoi(elts.at(1).c_str());
          }
        port_str = (port != -1) ? ":" + miscutil::to_string(port) : "";
        errlog::log_error(LOG_LEVEL_DEBUG,"adding peer %s%s%s with resource %s",
                          host.c_str(),port_str.c_str(),path.c_str(),vec[1]);
        _pl->add(host,port,path,std::string(vec[1]));
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Remote peer address for collaborative filtering");
        break;

      case hash_dead_peer_check:
        _dead_peer_check = atoi(arg);
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Interval of time between two dead peer checks");
        break;

      case hash_dead_peer_retries:
        _dead_peer_retries = atoi(arg);
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Number of retries before marking a peer as dead");
        break;

      case hash_post_url_check:
        _post_url_check = static_cast<bool>(atoi(arg));
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Whether to ping and check on posted URLs");
        break;

      case hash_post_radius:
        _post_radius = static_cast<bool>(atoi(arg));
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Query similarity impact radius of posted URLs");
        break;

      case hash_post_ua:
        _post_url_ua = std::string(arg);
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "default 'user-agent' header used to retrieve posted URLs");
        break;

      case hash_stop_words_filtering:
        _stop_words_filtering = static_cast<bool>(atoi(arg));
        configuration_spec::html_table_row(_config_args,cmd,arg,
                                           "Whether to filter similar queries with stop words");
        break;

      default:
        break;
      }
  }