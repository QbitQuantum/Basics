xml_token_type_t
xml_get_token_tag(xml_reader_t *xr, string_t *res)
{
	int cc, oc;

	xml_skip_space(xr, NULL);

	cc = xml_getc(xr);
	if (cc == EOF) {
		xml_parse_error(xr, "Unexpected EOF while parsing tag");
		return None;
	}

	string_putc(res, cc);

	switch (cc) {
	case '<':
		goto error;

	case '?':
		if ((cc = xml_getc(xr)) != '>')
			goto error;
		string_putc(res, cc);
		xr->state = Initial;
		return RightAngleQ;

	case '>':
		xr->state = Initial;
		return RightAngle;

	case '/':
		if ((cc = xml_getc(xr)) != '>')
			goto error;
		string_putc(res, cc);
		xr->state = Initial;
		return RightAngleSlash;

	case '=':
		return Equals;

	case 'a' ... 'z':
	case 'A' ... 'Z':
	case '_':
	case '!':
		while ((cc = xml_getc(xr)) != EOF) {
			if (!isalnum(cc) && cc != '_' && cc != '!' && cc != ':' && cc != '-') {
				xml_ungetc(xr, cc);
				break;
			}
			string_putc(res, cc);
		}
		return Identifier;

	case '\'':
	case '"':
		string_destroy(res);
		oc = cc;
		while (1) {
			cc = xml_getc(xr);
			if (cc == EOF)
				goto unexpected_eof;
			if (cc == '\\' && oc == '"') {
				cc = xml_getc(xr);
				if (cc == EOF)
					goto unexpected_eof;
			} else
			if (cc == oc)
				break;
			string_putc(res, cc);
		}
		return QuotedString;

	default:
		break;
	}

error:
	xml_parse_error(xr, "Unexpected character %c in XML document", cc);
	return None;

unexpected_eof:
	xml_parse_error(xr, "Unexpected EOF while parsing quoted string");
	return None;
}