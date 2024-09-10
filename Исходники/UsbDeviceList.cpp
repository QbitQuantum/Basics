LONG UsbDeviceList::FindNextInterfaceFilterField(LPCWSTR str, DWORD offset, LPDWORD nextOffset, LPINTERFACE_FILTER_FIELD field)
{
	// Initialise field to match-all (*)
	field->match = TRUE;
	field->value = USB_NO_INFO;

	(*nextOffset) = offset;

	for (DWORD i = offset; i <= wcslen(str); i++) {
		// Field is terminated by ':', ';' or end of string
		if (str[i] == ':' || str[i] == ';' || str[i] == '\0') {
			// Represent ';' as reaching end of string (only flags occur after 
			// this seperator)
			if (str[i] == ';') {
				(*nextOffset) = wcslen(str) + 1;
			} else {
				(*nextOffset) = i + 1;
			}
			LONG result = ERROR_SUCCESS;

			// Empty fields are disallowed
			// Fields may contain '*' or a base 10 value (possibly prepended with '!'
			// to invert match).
			if (i == offset) {
				// Invalid (empty field)
				result = ERROR_INVALID_PARAMETER;
			} else if (!(i == offset + 1 && str[offset] == '*')) {
				// Field contains base 10 value
				wchar_t* endptr = NULL;
				if (str[offset] == '!') {
					field->match = FALSE;
					offset++;
				}
				field->value = wcstol(&str[offset], &endptr, 10);
				if (endptr == &str[offset] || 
					(endptr[0] != ':' && endptr[0] != ';' && endptr[0] != '\0')) {
					result = ERROR_INVALID_PARAMETER;
				}
			}
			return result;
		}
	}

	// Offset beyond end of string (this may occur if we're looking
	// for optional fields that are not present).
	return ERROR_INVALID_PARAMETER;
}