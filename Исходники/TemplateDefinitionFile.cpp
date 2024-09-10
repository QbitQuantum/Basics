/**
 * Main parser for a tdf file. Parses initialization data, creates the header and
 * source files, and passes parameter definitions to the appropriate function.
 *
 * @param fp				file to parse
 *
 * @return 0 on success, -1 on fail
 */
int TemplateDefinitionFile::parse(File &fp)
{
static const int BUFFER_SIZE = 1024;
int lineLen;
char buffer[BUFFER_SIZE];
char token[BUFFER_SIZE];
TemplateData *currentTemplate = NULL;

	cleanup();

	setTemplateFilename(fp.getFilename().getName());

	for (;;)
	{
		lineLen = fp.readLine(buffer, BUFFER_SIZE);
		if (lineLen == -1)
			break;
		else if (lineLen == -2)
			return -1;

		const char *line = buffer;
		line = getNextWhitespaceToken(line, token);
		if (*token == '\0')
			break;

		if (strcmp(token, "version") == 0)
		{
			if (m_templateName.size() == 0)
			{
				fp.printError("no template name defined");
				return -1;
			}
			else if (m_templateId.tag == NO_TAG)
			{
				fp.printError("no template id defined");
				return -1;
			}
			else if (m_path.getPath().size() == 0)
			{
				fp.printError("no path defined");
				return -1;
			}
			else if (m_compilerPath.getPath().size() == 0)
			{
				fp.printError("no compiler path defined");
				return -1;
			}
//			if (m_baseName.size() == 0 && m_templateName != ROOT_TEMPLATE_NAME)
//				m_baseName = ROOT_TEMPLATE_NAME;
			line = getNextWhitespaceToken(line, token);
			int version = atoi(token);
			if (version < 0 || version > 9999)
			{
				fp.printError("version out of range");
				return -1;
			}
			if (m_templateMap.find(version) != m_templateMap.end())
			{
				fp.printError("version already defined");
				return -1;
			}
			if (version > m_highestVersion)
				m_highestVersion = version;
			
			currentTemplate = new TemplateData(version, *this);
			m_templateMap[version] = currentTemplate;
		}
		else if (currentTemplate != NULL)
		{
			line = currentTemplate->parseLine(fp, buffer, token);
			if (line == CHAR_ERROR)
				return -1;
		}
		else if (*token == '/' && *(token + 1) == '/')
		{
			if (m_baseName.size() == 0 && m_templateId.tag == NO_TAG)
				m_fileComments.push_back(buffer);
		}
		else if (strcmp(token, "base") == 0)
		{
			if (m_baseName.size() != 0)
			{
				fp.printError("base name already defined");
				return -1;
			}
			line = getNextWhitespaceToken(line, token);
			setBaseFilename(token);
			
			// load and parse the base template
			Filename baseFileName = fp.getFilename();
			baseFileName.setName(token);
			File baseFp(baseFileName, "rt");
			if (!baseFp.isOpened())
			{
				fp.printError("unable to open base template definition");
				return -1;
			}
			if (m_baseDefinitionFile == NULL)
				m_baseDefinitionFile = new TemplateDefinitionFile;
			else
				m_baseDefinitionFile->cleanup();
			int result = m_baseDefinitionFile->parse(baseFp);
			if (result != 0)
				return result;
		}
		else if (strcmp(token, "id") == 0)
		{
			if (m_templateId.tag != NO_TAG)
			{
				fp.printError("template id already defined");
				return -1;
			}
			line = getNextWhitespaceToken(line, token);
			if (strlen(token) != 4)
			{
				fp.printError("id not 4 characters");
				return -1;
			}
			m_templateId.tag = ConvertStringToTag(token);
			m_templateId.tagString = ConvertStringToTagString(token);
		}
		else if (strcmp(token, "templatename") == 0)
		{
			line = getNextWhitespaceToken(line, token);
			m_templateNameFilter = token;

			//-- Attempt to compile the regex.
			if (m_filterCompiledRegex != NULL)
			{
				// First free the existing compiled regex.
				RegexServices::freeMemory(m_filterCompiledRegex);
				m_filterCompiledRegex = NULL;
			}

			//-- Compile the new regex.
			char const *errorString = NULL;
			int         errorOffset = 0;

			m_filterCompiledRegex = pcre_compile(m_templateNameFilter.c_str(), 0, &errorString, &errorOffset, NULL);
			WARNING(m_filterCompiledRegex == NULL, ("TemplateDefinitionFile::parse(): pcre_compile() failed, error=[%s], errorOffset=[%d], regex text=[%s].", errorString, errorOffset, m_templateNameFilter.c_str()));
		}
		else if (strcmp(token, "clientpath") == 0 ||
		         strcmp(token, "serverpath") == 0 ||
		         strcmp(token, "sharedpath") == 0)
		{
			if (m_path.getPath().size() != 0)
			{
				fp.printError("path already defined");
				return -1;
			}
			if (strcmp(token, "clientpath") == 0)
				m_templateLocation = LOC_CLIENT;
		    else if (strcmp(token, "serverpath") == 0)
				m_templateLocation = LOC_SERVER;
		    else
				m_templateLocation = LOC_SHARED;
			line = getNextWhitespaceToken(line, token);
			m_path.setPath(token);
			m_path.prependPath(fp.getFilename());
			// reset the template name to add the corrent prefix to the template 
			// name
			setTemplateFilename(m_templateFilename);
			if (!m_baseFilename.empty())
				setBaseFilename(m_baseFilename);
		}
		else if (strcmp(token, "compilerpath") == 0)
		{
			if (m_compilerPath.getPath().size() != 0)
			{
				fp.printError("compiler path already defined");
				return -1;
			}
			line = getNextWhitespaceToken(line, token);
			m_compilerPath.setPath(token);
			m_compilerPath.prependPath(fp.getFilename());
		}
		else
		{
			char errbuf[2048];
			sprintf(errbuf, "I don't know how to handle this line!: <%s>. "
				"Barfed on token <%s>.", buffer, token);
			fp.printError(errbuf);
			return -1;
		}
	}
	return 0;
}	// TemplateDefinitionFile::parse