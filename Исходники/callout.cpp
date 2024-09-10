static bool ParseCalloutFile(std::map<uint16_t, net_call_out_rec>* node_config_map, const string network_dir) {
  TextFile node_config_file(network_dir, CALLOUT_NET, "rt");
  if (!node_config_file.IsOpen()) {
    return false;
  }
  // A line will be of the format @node host:port [password].
  string line;
  while (node_config_file.ReadLine(&line)) {
    StringTrim(&line);
    net_call_out_rec node_config{};
    if (ParseCalloutNetLine(line, &node_config)) {
      // Parsed a line correctly.
      node_config.ftn_address = StrCat("20000:20000/", node_config.sysnum);
      node_config_map->emplace(node_config.sysnum, node_config);
    }
  }
  return true;
}