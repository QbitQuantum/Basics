void ConfigManager::loadFromStream(SeekableReadStream &stream) {
	String domainName;
	String comment;
	Domain domain;
	int lineno = 0;

	_appDomain.clear();
	_gameDomains.clear();
	_miscDomains.clear();
	_transientDomain.clear();
	_domainSaveOrder.clear();

#ifdef ENABLE_KEYMAPPER
	_keymapperDomain.clear();
#endif

	// TODO: Detect if a domain occurs multiple times (or likewise, if
	// a key occurs multiple times inside one domain).

	while (!stream.eos() && !stream.err()) {
		lineno++;

		// Read a line
		String line = stream.readLine();

		if (line.size() == 0) {
			// Do nothing
		} else if (line[0] == '#') {
			// Accumulate comments here. Once we encounter either the start
			// of a new domain, or a key-value-pair, we associate the value
			// of the 'comment' variable with that entity.
			comment += line;
			comment += "\n";
		} else if (line[0] == '[') {
			// It's a new domain which begins here.
			// Determine where the previously accumulated domain goes, if we accumulated anything.
			addDomain(domainName, domain);
			domain.clear();
			const char *p = line.c_str() + 1;
			// Get the domain name, and check whether it's valid (that
			// is, verify that it only consists of alphanumerics,
			// dashes and underscores).
			while (*p && (isAlnum(*p) || *p == '-' || *p == '_'))
				p++;

			if (*p == '\0')
				error("Config file buggy: missing ] in line %d", lineno);
			else if (*p != ']')
				error("Config file buggy: Invalid character '%c' occurred in section name in line %d", *p, lineno);

			domainName = String(line.c_str() + 1, p);

			domain.setDomainComment(comment);
			comment.clear();

		} else {
			// This line should be a line with a 'key=value' pair, or an empty one.

			// Skip leading whitespaces
			const char *t = line.c_str();
			while (isSpace(*t))
				t++;

			// Skip empty lines / lines with only whitespace
			if (*t == 0)
				continue;

			// If no domain has been set, this config file is invalid!
			if (domainName.empty()) {
				error("Config file buggy: Key/value pair found outside a domain in line %d", lineno);
			}

			// Split string at '=' into 'key' and 'value'. First, find the "=" delimeter.
			const char *p = strchr(t, '=');
			if (!p)
				error("Config file buggy: Junk found in line line %d: '%s'", lineno, t);

			// Extract the key/value pair
			String key(t, p);
			String value(p + 1);

			// Trim of spaces
			key.trim();
			value.trim();

			// Finally, store the key/value pair in the active domain
			domain[key] = value;

			// Store comment
			domain.setKVComment(key, comment);
			comment.clear();
		}
	}

	addDomain(domainName, domain); // Add the last domain found
}