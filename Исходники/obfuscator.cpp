/*
 * Scaning all text
 * Skip the "string"
 * Why do finds the function name:
 *   function call:
 *     foo(arg1, arg2, ...)
 *     a = foo(arg1, arg2, ...)
 *   when function send to other function
 *     trycall(foo)
 * ---------------------
 * therefore function name is near '(' and ')'
 */
ptrdiff_t replaceGlobalFunctions(const char *szFileName, FakeFunctions &globalFunctions,
	const StringList &excludeFunctions)
{
	if (!szFileName || !szFileName[0])
		return 0;

	FILE *file = fopen(szFileName, "rt");
	if (!file)
		return 0;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	char *pDataInSource = new char[size + 20]; // + 20 for additional 10_"data"_10
	memset(pDataInSource, 0, 10);
	char *pDataIn = pDataInSource + 10; // for delete/clear data

	size_t realSize = fread(pDataIn, 1, size, file);
	memset(pDataIn + realSize, 0, 10);

	fclose(file);

	StringStream stream;
	char *p = pDataIn;

	while (*p) {
		if (isStringStart(p)) {
			size_t size = skipStringAndMove(&p, NULL);
			stream.write(p - size, size);
			continue;
		}

		if (!strncmp(p, "tostring", sizeof("tostring") - 1))
			*p = *p;

		char *pStart = p;
		while (isAlphaFun(*p)) {
			++p;
		}

		size_t wordSize = p - pStart;
		if (wordSize) {
			if (isFunctionNameInCode(pStart, p)) {
				std::string str(pStart, wordSize);
				StringMapConstIter iter = globalFunctions.find(str);
				if (iter != globalFunctions.end()) {
					StringListConstIter IterFunExclude = std::find(excludeFunctions.begin(), excludeFunctions.end(), str);
					if (IterFunExclude == excludeFunctions.end()) {
						// replace
						stream.write(iter->second.c_str(), FAKE_FUNCTION_LEN);
						continue;
					}
				}
			}
			stream.write(pStart, wordSize);
			if (!p[0]) {
				break;
			}
		}
		stream << *p;

		++p;
	}

	file = fopen(szFileName, "wt");
	const std::string& str = stream.str();
	size_t obfuscateSize = str.length();
	if (file) {
		fwrite(str.c_str(), 1, obfuscateSize, file);
		fclose(file);
	}

	delete[] pDataInSource;

	print("%8d %s\n", obfuscateSize - realSize, szFileName);

	return obfuscateSize - realSize;
}