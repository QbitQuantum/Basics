	bool Settings::parserModulesOptions(String::List& options, bool displayError)
	{
		// Cleanup if needed
		moduleSettings.clear();
		// End of the list
		const String::List::const_iterator end = options.end();
		// Key
		String key;
		// Value
		String value;
		// Module name
		String modName;
		// Group
		String group;
		// normalized path
		String norm;

		// The default compiler is gcc
		CompilerCompliant compliant = gcc;
		// Checking for Visual Studio
		if (not compiler.empty() && compiler.at(0) == 'v' && compiler.at(1) == 's')
			compliant = visualstudio;

		// For each entry in the ini file
		for (String::List::const_iterator i = options.begin(); i != end; ++i)
		{
			i->extractKeyValue(key, value);
			if (key.empty() || key.first() == '[')
				continue;
			value.trim();
			if (!value)
				continue;

			// Reset
			modName.clear();
			group.clear();

			// Splitting
			const String::Size p = key.find(':');
			if (p == String::npos)
				continue;
			group.assign(key, p);
			modName.assign(key, key.size() - p - 1, p + 1);
			if (not group or not modName)
				continue;

			SettingsPerModule& s = moduleSettings[modName];

			if (group == "path.include")
			{
				IO::Normalize(norm, value);
				switch (compliant)
				{
					case gcc          :
						s.includes[String() << "-I" << QuotePath(norm)] = true;
						break;

					case visualstudio :
						s.includes[String() << "/I" << QuotePath(norm)] = true;
						break;
				}
				continue;
			}

			if (group == "lib,rawcommand")
			{
				s.libs[value] = true;
				continue;
			}

			if (group == "path.lib")
			{
				IO::Normalize(norm, value);
				switch (compliant)
				{
					case gcc          :
						s.libIncludes[String() << "-L" << QuotePath(norm)] = true;
						break;
					case visualstudio :
						s.libIncludes[String() << "/LIBPATH:" << QuotePath(norm)] = true;
						break;
				}
				continue;
			}

			if (group == "lib")
			{
				IO::Normalize(norm, value);
				# ifdef YUNI_OS_MAC
				// it may happen that cmake provides a framework for linking, which is wrong obvioulsy
				CString<32,false> ext;
				IO::ExtractExtension(ext, norm);
				ext.toLower();
				if (ext != ".framework")
					s.libs[String() << "-l" << QuotePath(norm)] = true;
				else
				{
					// adding the parent directory
					String frameworkpath;
					norm += "/../";
					IO::Normalize(frameworkpath, norm);
					s.libIncludes[String() << "-F" << QuotePath(frameworkpath)] = true;
				}
				# else
				switch (compliant)
				{
					case gcc          : s.libs[String() << "-l" << QuotePath(norm)] = true; break;
					case visualstudio : s.libs[String() << QuotePath(norm)] = true; break;
				}
				# endif
				continue;
			}

			if (group == "cxxflag")
			{
				s.cxxFlags[value] = true;
				continue;
			}

			if (group == "define")
			{
				switch (compliant)
				{
					case gcc          : s.defines[String() << "-D" << value] = true; break;
					case visualstudio : s.defines[String() << "/D" << value] = true; break;
				}
				continue;
			}
			if (group == "dependency")
			{
				s.dependencies.push_back(value);
				continue;
			}

			if (group == "framework")
			{
				s.frameworks[String() << "-framework " << QuotePath(value)] = true;
				continue;
			}

			if (displayError)
				std::cout << "Error: unknown key in the config file: '" << key << "'\n";
			return false;
		}
		return true;
	}