void
CommandInterpreter::GetAliasHelp (const char *alias_name, const char *command_name, StreamString &help_string)
{
    help_string.Printf ("'%s", command_name);
    OptionArgVectorSP option_arg_vector_sp = GetAliasOptions (alias_name);

    if (option_arg_vector_sp != NULL)
    {
        OptionArgVector *options = option_arg_vector_sp.get();
        for (int i = 0; i < options->size(); ++i)
        {
            OptionArgPair cur_option = (*options)[i];
            std::string opt = cur_option.first;
            std::string value = cur_option.second;
            if (opt.compare("<argument>") == 0)
            {
                help_string.Printf (" %s", value.c_str());
            }
            else
            {
                help_string.Printf (" %s", opt.c_str());
                if ((value.compare ("<no-argument>") != 0)
                    && (value.compare ("<need-argument") != 0))
                {
                    help_string.Printf (" %s", value.c_str());
                }
            }
        }
    }

    help_string.Printf ("'");
}