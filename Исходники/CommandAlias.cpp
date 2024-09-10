void CommandAlias::GetAliasExpansion(StreamString &help_string) {
  const char *command_name = m_underlying_command_sp->GetCommandName();
  help_string.Printf("'%s", command_name);

  if (m_option_args_sp) {
    OptionArgVector *options = m_option_args_sp.get();
    for (size_t i = 0; i < options->size(); ++i) {
      OptionArgPair cur_option = (*options)[i];
      std::string opt = cur_option.first;
      OptionArgValue value_pair = cur_option.second;
      std::string value = value_pair.second;
      if (opt.compare("<argument>") == 0) {
        help_string.Printf(" %s", value.c_str());
      } else {
        help_string.Printf(" %s", opt.c_str());
        if ((value.compare("<no-argument>") != 0) &&
            (value.compare("<need-argument") != 0)) {
          help_string.Printf(" %s", value.c_str());
        }
      }
    }
  }

  help_string.Printf("'");
}