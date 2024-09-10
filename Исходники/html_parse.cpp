std::vector<std::wstring> html_extract(const std::wstring& filename, const std::wstring& path_str) {
	if (!path_str.length()) return std::vector<std::wstring>();
	std::vector<std::wstring> re;
	boost::property_tree::wptree pt;
	std::wstringstream ss;
	std::wifstream file(filename);
	if (!file) throw std::runtime_error("cannot open file");
	static_assert(sizeof(wchar_t) == 2, "In function html_extract, wchar_t is not UTF16.");
	file.imbue(std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>()));//UTF-8 -> UTF16(wchar_t in Windows.)
	convert_html_to_xml(file, ss);
	read_xml(ss, pt, boost::property_tree::xml_parser::no_comments);
	const auto path = detail::parse_path(path_str);
	auto& body = pt.get_child(L"html.body");//HTML has body tag. if not exist, exception will be thrown.
	detail::html_extract_impl(re, body, path);//analyse
	return re;
}