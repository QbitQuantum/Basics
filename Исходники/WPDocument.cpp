/**
Parses the input stream content. It will make callbacks to the functions provided by a
librevenge::RVNGTextInterface class implementation when needed. This is often commonly called the
'main parsing routine'.
\param input The input stream
\param textInterface A librevenge::RVNGTextInterface implementation
\param password The password used to protect the document or NULL if the document
is not protected
\return A value that indicates whether the conversion was successful and in case it
was not, it indicates the reason of the error
*/
WPDAPI WPDResult WPDocument::parse(librevenge::RVNGInputStream *input, librevenge::RVNGTextInterface *textInterface, const char *password)
{
	if (!input)
		return WPD_FILE_ACCESS_ERROR;

	if (password && verifyPassword(input, password) != WPD_PASSWORD_MATCH_OK)
		return WPD_PASSWORD_MISSMATCH_ERROR;

	input->seek(0, librevenge::RVNG_SEEK_SET);

	WPXParser *parser = 0;

	// by-pass the OLE stream (if it exists) and returns the (sub) stream with the
	// WordPerfect document.

	librevenge::RVNGInputStream *document = 0;
	bool isStructuredDocument = false;

	WPD_DEBUG_MSG(("WPDocument::parse()\n"));
	if (input->isStructured())
	{
		document = input->getSubStreamByName("PerfectOffice_MAIN");
		if (document)
			isStructuredDocument = true;
		else
			return WPD_OLE_ERROR;
	}
	else
		document = input;

	WPDResult error = WPD_OK;

	try
	{
		WPXEncryption *encryption = 0;
		WPXHeader *header = WPXHeader::constructHeader(document, 0);

		if (header)
		{
			switch (header->getFileType())
			{
			case 0x0a: // WordPerfect File
				switch (header->getMajorVersion())
				{
				case 0x00: // WP5
					WPD_DEBUG_MSG(("WordPerfect: Using the WP5 parser.\n"));
					if (password)
						encryption = new WPXEncryption(password, 16);
					parser = new WP5Parser(document, header, encryption);
					parser->parse(textInterface);
					break;
				case 0x02: // WP6
					WPD_DEBUG_MSG(("WordPerfect: Using the WP6 parser.\n"));
					if (password)
					{
						delete header;
						throw UnsupportedEncryptionException();
					}
					parser = new WP6Parser(document, header, encryption);
					parser->parse(textInterface);
					break;
				default:
					// unhandled file format
					WPD_DEBUG_MSG(("WordPerfect: Unsupported file format.\n"));
					break;
				}
				break;
			case 0x2c: // WP Mac File
				switch (header->getMajorVersion())
				{
				case 0x02: // WP Mac 2.x
				case 0x03: // WP Mac 3.0-3.5
				case 0x04: // WP Mac 3.5e
					WPD_DEBUG_MSG(("WordPerfect: Using the WP3 parser.\n"));
					if (password)
						encryption = new WPXEncryption(password, header->getDocumentOffset());
					parser = new WP3Parser(document, header, encryption);
					parser->parse(textInterface);
					break;
				default:
					// unhandled file format
					WPD_DEBUG_MSG(("WordPerfect: Unsupported file format.\n"));
					break;
				}
				break;
			default:
				// unhandled file format
				WPD_DEBUG_MSG(("WordPerfect: Unsupported file type.\n"));
				break;
			}
			DELETEP(parser);
			DELETEP(header);
		}
		else
		{
			// WP file formats prior to version 5.x do not contain a generic
			// header which can be used to determine which parser to instanciate.
			// Use heuristics to determine with some certainty if we are dealing with
			// a file in the WP4.2 format or WP Mac 1.x format.
			if (WP1Heuristics::isWP1FileFormat(document, password) == WPD_CONFIDENCE_EXCELLENT)
			{
				WPD_DEBUG_MSG(("WordPerfect: Mostly likely the file format is WP Mac 1.x.\n\n"));
				WPD_DEBUG_MSG(("WordPerfect: Using the WP Mac 1.x parser.\n\n"));
				if (password)
					encryption = new WPXEncryption(password, 6);
				parser = new WP1Parser(document, encryption);
				parser->parse(textInterface);
				DELETEP(parser);
			}
			else if (WP42Heuristics::isWP42FileFormat(document, password) == WPD_CONFIDENCE_EXCELLENT)
			{
				WPD_DEBUG_MSG(("WordPerfect: Mostly likely the file format is WP4.2.\n\n"));
				WPD_DEBUG_MSG(("WordPerfect: Using the WP4.2 parser.\n\n"));
				if (password)
				{
					encryption = new WPXEncryption(password, 6);
					input->seek(6, librevenge::RVNG_SEEK_SET);
				}
				parser = new WP42Parser(document, encryption);
				parser->parse(textInterface);
				DELETEP(parser);
			}
			else

				error = WPD_FILE_ACCESS_ERROR;
		}
	}

	catch (FileException)
	{
		WPD_DEBUG_MSG(("File Exception trapped\n"));
		error = WPD_FILE_ACCESS_ERROR;
	}
	catch (ParseException)
	{
		WPD_DEBUG_MSG(("Parse Exception trapped\n"));
		error = WPD_PARSE_ERROR;
	}
	catch (UnsupportedEncryptionException)
	{
		WPD_DEBUG_MSG(("Encrypted document exception trapped\n"));
		error = WPD_UNSUPPORTED_ENCRYPTION_ERROR;
	}
	catch (...)
	{
		WPD_DEBUG_MSG(("Unknown Exception trapped\n"));
		error = WPD_UNKNOWN_ERROR;
	}

	DELETEP(parser);
	if (document && isStructuredDocument)
		DELETEP(document);

	return error;
}