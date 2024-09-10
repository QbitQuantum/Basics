/**
 * Writes the source file for a template.
 *
 * @param tdfFile		parsed template definition file
 * @param filename		file to write to
 *
 * @resurn 0 on success, -1 on error
 */
int writeTemplateSource(const TemplateDefinitionFile &tdfFile, const Filename &filename)
{
static const int BUFFER_SIZE = 1024;
File fp;
int result;

	const TemplateData *currentTemplate = tdfFile.getTemplateData(tdfFile.getHighestVersion());
	NOT_NULL(currentTemplate);

	Filename sourcename = filename;
	sourcename.setExtension(".cpp");

#ifndef ALWAYS_OVERWRITE
	char buffer[BUFFER_SIZE];

	// see if the template source already exists
	if (!fp.exists(sourcename))
	{
#endif
		// this is a new template source
		if (!fp.open(sourcename, "wt"))
		{
			fprintf(stderr, "error opening file [%s]\n", fp.getFilename().getFullFilename().c_str());
			return -1;
		}
		tdfFile.writeClassSourceBegin(fp, *currentTemplate);
		result = currentTemplate->writeSourceMethods(fp);
		fp.close();
		if (result != 0)
			return result;
#ifndef ALWAYS_OVERWRITE
	}
	else
	{
		// the template source exists, make a copy and replace the auto-generated
		// code
		if (!fp.open(sourcename, "rt"))
		{
			fprintf(stderr, "error opening template source file %s\n", sourcename.getFullFilename().c_str());
			return -1;
		}

		File temp_fp;
		if (!temp_fp.open(tmpnam(NULL), "wt"))
		{
			fprintf(stderr, "error opening temp file for template source "
				"replacement [%s]\n", temp_fp.getFilename().getFullFilename().c_str());
			return -1;
		}

		for (;;)
		{
			int result = fp.readRawLine(buffer, BUFFER_SIZE);
			if (result < 0)
			{
				if (result == -1)
					break;
				else
				{
					fp.printError("error reading old template source file");
					return -1;
				}
			}
			if (strncmp(buffer, TDF_TEMPLATE_REFS_BEGIN, strlen(TDF_TEMPLATE_REFS_BEGIN)) == 0)
			{
				// write out the new tdf data
				currentTemplate->writeSourceTemplateIncludes(temp_fp);
				// skip the old tdf data
				if (!skipOldCode(fp, TDF_TEMPLATE_REFS_END, buffer, BUFFER_SIZE))
					return -1;
			}
			else if (strncmp(buffer, TDF_INIT_BEGIN, strlen(TDF_INIT_BEGIN)) == 0)
			{
				// write out the new tdf data
				currentTemplate->writeSourceLoadedFlagInit(temp_fp);
				// skip the old tdf data
				if (!skipOldCode(fp, TDF_INIT_END, buffer, BUFFER_SIZE))
					return -1;
			}
			else if (strncmp(buffer, TDF_CLEANUP_BEGIN, strlen(TDF_CLEANUP_BEGIN)) == 0)
			{
				// write out the new tdf data
				currentTemplate->writeSourceCleanup(temp_fp);
				// skip the old tdf data
				if (!skipOldCode(fp, TDF_CLEANUP_END, buffer, BUFFER_SIZE))
					return -1;
			}
			else if (strncmp(buffer, TDF_BEGIN, strlen(TDF_BEGIN)) == 0)
			{
				// write out the new tdf data
				result = currentTemplate->writeSourceMethods(temp_fp);
				if (result != 0)
					return -1;
				// skip the old tdf data
				if (!skipOldCode(fp, TDF_END, buffer, BUFFER_SIZE))
					return -1;
			}
			else if (temp_fp.puts(buffer) < 0)
			{
				fprintf(stderr, "error writing to temp source file [%s]\n", temp_fp.getFilename().getFullFilename().c_str());
				return -1;
			}
		}

		fp.close();
		temp_fp.close();
		if (remove(fp.getFilename()) != 0)
		{
			fprintf(stderr, "error removing old template source [%s]\n", fp.getFilename().getFullFilename().c_str());
			return -1;
		}
		if (rename(temp_fp.getFilename(), fp.getFilename()) != 0)
		{
			fprintf(stderr, "error updating template source\n[%s]\nto\n[%s]\n", temp_fp.getFilename().getFullFilename().c_str(), fp.getFilename().getFullFilename().c_str());
			return -1;
		}
	}
#endif	// ALWAYS_OVERWRITE
	return 0;
}	// writeTemplateSource