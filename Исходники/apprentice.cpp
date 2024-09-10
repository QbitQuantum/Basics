	// and at last the rarities
	FOR_EACH(c, order) {
		String code = c;
		if (code.GetChar(0) == _('-')) {
			tout << c << _("-") << expansions[c] << _("\n");
		}
	}