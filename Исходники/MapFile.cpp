void
MapFile::PerformSubstitution(ExtArray<MyString> & groups,
							 const MyString pattern,
							 MyString & output)
{
	for (int index = 0; index < pattern.Length(); index++) {
		if ('\\' == pattern[index]) {
			index++;
			if (index < pattern.Length()) {
				if ('1' <= pattern[index] &&
					'9' >= pattern[index]) {
					int match = pattern[index] - '0';
					if (groups.getlast() >= match) {
						output += groups[match];
						continue;
					}
				}

				output += '\\';
			}
		}

		output += pattern[index];
	}
}