static int php_ini_displayer(zend_ini_entry *ini_entry, int module_number)
{
	if (ini_entry->module_number != module_number) {
		return 0;
	}

	PUTS("<TR VALIGN=\"baseline\" BGCOLOR=\"" PHP_CONTENTS_COLOR "\">");
	PUTS("<TD BGCOLOR=\"" PHP_ENTRY_NAME_COLOR "\"><B>");
	PHPWRITE(ini_entry->name, ini_entry->name_length-1);
	PUTS("</B><BR></TD><TD ALIGN=\"center\">");
	php_ini_displayer_cb(ini_entry, ZEND_INI_DISPLAY_ACTIVE);
	PUTS("</TD><TD ALIGN=\"center\">");
	php_ini_displayer_cb(ini_entry, ZEND_INI_DISPLAY_ORIG);
	PUTS("</TD></TR>\n");
	return 0;
}