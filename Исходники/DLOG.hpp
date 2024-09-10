	void llvm_print(const char *userfile, int lineno, T &obj, const char* tag,
			ADDON addon = ADDON())
	{

		std::string unformatted = llvm_to_str(obj);
		std::string formatted = dlog_format_string_to_html(unformatted);

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_FILE)

		{
			tag_handler(tag);
			fdata << DIV(
					tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << br << CALLINFO
			<< BROWN(addon.getString()) << NBSP << NBSP
			<< BOLD(" Data : <br>") << formatted << EDIV;
		}
		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_STDOUT)
		{
			std::cout << "Tag : " << tag << "\t";
			if (addon.getString().length() != 0)
			std::cout << "\t Addon: " << addon.getString() << "\n";
			std::cout << unformatted << "\n";
		}

		fdata.flush();
	}