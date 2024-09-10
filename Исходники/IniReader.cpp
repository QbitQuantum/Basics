bool IniReader::read(std::istream & is) {
	
	// The current section
	IniSection * section = NULL;
	
	bool ok = true;
	
	bool readline = true;
	
	std::string str;
	
	// While lines remain to be extracted
	for(size_t line = 1; is.good(); line++) {
		
		// Get a line to process
		if(readline) {
			str.clear();
			getline(is, str);
		} else {
			readline = true;
		}
		
		size_t start = str.find_first_not_of(WHITESPACE);
		if(start == std::string::npos) {
			// Empty line (only whitespace)
			continue;
		}
		
		if(str[start] == '#'
		   || (start + 1 < str.length() && str[start] == '/' && str[start+1] == '/')) {
			// Whole line was commented, no need to do anything with it. Continue getting the next line
			continue;
		}
		
		// Section header
		if(str[start] == '[') {
			
			size_t end = str.find(']', start + 1);
			if(end == std::string::npos) {
				LogDebug("invalid header @ line " << line << ": " << str);
				end = str.find_first_not_of(ALPHANUM, start + 1);
				if(end == std::string::npos) {
					end = str.length();
				}
			}
			
			std::string sectionName = str.substr(start + 1, end - start - 1);
			transform(sectionName.begin(), sectionName.end(), sectionName.begin(), ::tolower);
			
			LogDebug("found section: \"" << sectionName << "\"");
			section = &sections[sectionName];
			
			// Ignoring rest of the line, not verifying that it's only whitespace / comment
			
			continue;
		}
		
		if(!section) {
			LogWarning << "Ignoring non-empty line " << line << " outside a section: " << str;
			ok = false;
			continue;
		}
		
		size_t nameEnd = str.find_first_not_of(ALPHANUM, start);
		if(nameEnd == std::string::npos) {
			ok = false;
			LogWarning << "Missing '=' separator @ line " << line << ": " << str;
			continue;
		} else if(nameEnd == start) {
			ok = false;
			LogWarning << "Empty key name @ line " << line << ": " << str;
			continue;
		}
		
		bool quoted = false;
		
		size_t separator = str.find_first_not_of(WHITESPACE, nameEnd);
		if(separator == std::string::npos || str[separator] != '=') {
			if(separator != std::string::npos && separator + 1 < str.length()
			   && str[separator] == '"' && str[separator + 1] == '=') {
				LogDebug("found '\"=' instead of '=\"' @ line " << line << ": " << str);
				quoted = true;
			} else {
				ok = false;
				LogWarning << "Missing '=' separator @ line " << line << ": " << str;
				continue;
			}
		}
		
		size_t valueStart = str.find_first_not_of(WHITESPACE, separator + 1);
		if(valueStart == std::string::npos) {
			// Empty value.
			section->addKey(str.substr(start, nameEnd - start), std::string());
			continue;
		}
		
		std::string key = str.substr(start, nameEnd - start);
		std::string value;
		
		if(quoted || str[valueStart] == '"') {
			valueStart++;
			size_t valueEnd = str.find_last_of('"');
			arx_assert(valueEnd != std::string::npos);
			
			if(valueEnd < valueStart) {
				
				// The localisation files are broken (missing ending quote)
				// But the spanish localisation files hae erroneous newlines in some values
				LogDebug("invalid quoted value @ line " << line << ": " << str);
				
				valueEnd = str.find_last_not_of(WHITESPACE) + 1;
				arx_assert(valueEnd >= valueStart);
				value = str.substr(valueStart, valueEnd - valueStart);
				
				// Add following lines until we find either a terminating quote,
				// an empty or commented line, a new section or a new key
				for(; is.good(); line++) {
					
					str.clear();
					getline(is, str);
					
					size_t start = str.find_first_not_of(WHITESPACE);
					if(start == std::string::npos) {
						// Empty line (only whitespace)
						break;
					}
					
					if(str[start] == '#'
					   || (start + 1 < str.length() && str[start] == '/' && str[start+1] == '/')) {
						// Whole line was commented
						break;
					}
					
					if(str[start] == '[') {
						// New section
						line--, readline = false;
						break;
					}
					
					size_t nameEnd = str.find_first_not_of(ALPHANUM, start);
					if(nameEnd != std::string::npos && nameEnd != start) {
						size_t separator = str.find_first_not_of(WHITESPACE, nameEnd);
						if(separator != std::string::npos && str[separator] == '=') {
							// New key
							line--, readline = false;
							break;
						}
					}
					
					// Replace newlines with spaces!
					value += ' ';
					
					size_t valueEnd = str.find_last_of('"');
					if(valueEnd != std::string::npos) {
						// End of multi-line value
						value += str.substr(start, valueEnd - start);
						break;
					}
					
					valueEnd = str.find_last_not_of(WHITESPACE) + 1;
					arx_assert(valueEnd > start);
					value += str.substr(start, valueEnd - start);
				}
				
			} else {
				value = str.substr(valueStart, valueEnd - valueStart);
			}
			
		} else {
			size_t valueEnd = str.find_last_not_of(WHITESPACE) + 1;
			arx_assert(valueEnd != std::string::npos);
			arx_assert(valueEnd >= valueStart);
			value = str.substr(valueStart, valueEnd - valueStart);
		}
		
		section->addKey(key, value);
		
		// Ignoring rest of the line, not verifying that it's only whitespace / comment
		
	}
	
	return ok;
}